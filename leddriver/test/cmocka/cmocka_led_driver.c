#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <setjmp.h>
#include <cmocka.h>

#include <stdlib.h>
#include "led/driver.h"
#include "runtime_error_stub.h"

static int setup(void** state) {
  uint16_t* virtualleds = (uint16_t*)malloc(sizeof(uint16_t));
  LedDriver_Create(virtualleds);
  *state = virtualleds;
  return 0;
}

static int teardown(void** state) {
  if (*state) {
    free(*state);
  }
  return 0;
}

static void LedDriver_LedsOffAfterCreate(void** state) {
  uint16_t virtualleds = 0xffff;
  LedDriver_Create(&virtualleds);
  assert_uint_equal(0, virtualleds);
}

static void LedDriver_TrunOnLedOne(void** state) {
  LedDriver_TurnOn(1);
  assert_uint_equal(0x1, *(uint16_t*)*state);
}

static void LedDriver_TrunOffLedOne(void** state) {
  LedDriver_TurnOn(1);
  LedDriver_TurnOff(1);
  assert_uint_equal(0x0, *(uint16_t*)*state);
}

static void LedDriver_TrunOnMultipleLeds(void** state) {
  LedDriver_TurnOn(9);
  LedDriver_TurnOn(8);
  assert_uint_equal(0x180, *(uint16_t*)*state);
}

static void LedDriver_AllOn(void** state) {
  LedDriver_TurnAllOn();
  assert_uint_equal(0xffff, *(uint16_t*)*state);
}

static void LedDriver_TrunOffAnyLed(void** state) {
  LedDriver_TurnAllOn();
  LedDriver_TurnOff(8);
  assert_uint_equal(0xff7f, *(uint16_t*)*state);
}

static void LedDriver_TurnOffMultipleLeds(void** state) {
  LedDriver_TurnAllOn();
  LedDriver_TurnOff(9);
  LedDriver_TurnOff(8);
  assert_uint_equal(0xfe7f, *(uint16_t*)*state);
}

static void LedDriver_AllOff(void** state) {
  LedDriver_TurnAllOn();
  LedDriver_TurnAllOff();
  assert_uint_equal(0x0, *(uint16_t*)*state);
}

static void LedDriver_LedMemoryIsNotReadable(void** state) {
  uint16_t virtualleds;
  LedDriver_Create(&virtualleds);
  virtualleds = 0xffff;
  LedDriver_TurnOn(8);
  assert_uint_equal(0x80, virtualleds);
}

static void LedDriver_UpperAndLowerBounds(void** state) {
  LedDriver_TurnOn(1);
  LedDriver_TurnOn(16);
  assert_uint_equal(0x8001, *(uint16_t*)*state);
}

static void LedDriver_OutOfBoundsChangesNothing(void** state) {
  LedDriver_TurnOn(-1);
  LedDriver_TurnOn(0);
  LedDriver_TurnOn(17);
  LedDriver_TurnOn(3141);
  assert_uint_equal(0x0, *(uint16_t*)*state);
}

static void LedDriver_OutOfBoundsTurnOffDoesNoHarm(void** state) {
  LedDriver_TurnAllOn();
  LedDriver_TurnOff(-1);
  LedDriver_TurnOff(0);
  LedDriver_TurnOff(17);
  LedDriver_TurnOff(3141);
  assert_uint_equal(0xffff, *(uint16_t*)*state);
}

static void LedDriver_OutOfBoundsProducesRuntimeError(void** state) {
  LedDriver_TurnOn(-1);
  assert_string_equal("LED Driver: out-of-bounds LED",
                      RuntimeErrorStub_GetLastError());
  assert_int_equal(-1, RuntimeErrorStub_GetLastParameter());
}

static void LedDriver_OutOfBoundsToDo(void** state) {
  skip();  // TODO: What should we do during execution?
}

static void LedDriver_CheckIsOn(void** state) {
  assert_false(LedDriver_IsOn(11));
  LedDriver_TurnOn(11);
  assert_true(LedDriver_IsOn(11));
}

static void LedDriver_CheckIsOff(void** state) {
  assert_true(LedDriver_IsOff(12));
  LedDriver_TurnOn(12);
  assert_false(LedDriver_IsOff(12));
}

static void LedDriver_OutOfBoundsLedsAreAlwaysOff(void** state) {
  assert_true(LedDriver_IsOff(0));
  assert_true(LedDriver_IsOff(17));
  assert_false(LedDriver_IsOn(0));
  assert_false(LedDriver_IsOn(17));
}

int main(void) {
  const struct CMUnitTest tests[] = {
    cmocka_unit_test_setup_teardown(LedDriver_LedsOffAfterCreate, NULL, NULL),
    cmocka_unit_test_setup_teardown(LedDriver_TrunOnLedOne, setup, teardown),
    cmocka_unit_test_setup_teardown(LedDriver_TrunOffLedOne, setup, teardown),
    cmocka_unit_test_setup_teardown(LedDriver_TrunOnMultipleLeds, setup, teardown),
    cmocka_unit_test_setup_teardown(LedDriver_AllOn, setup, teardown),
    cmocka_unit_test_setup_teardown(LedDriver_TrunOffAnyLed, setup, teardown),
    cmocka_unit_test_setup_teardown(LedDriver_TurnOffMultipleLeds, setup, teardown),
    cmocka_unit_test_setup_teardown(LedDriver_AllOff, setup, teardown),
    cmocka_unit_test_setup_teardown(LedDriver_LedMemoryIsNotReadable, NULL, NULL),
    cmocka_unit_test_setup_teardown(LedDriver_UpperAndLowerBounds, setup, teardown),
    cmocka_unit_test_setup_teardown(LedDriver_OutOfBoundsChangesNothing, setup, teardown),
    cmocka_unit_test_setup_teardown(LedDriver_OutOfBoundsTurnOffDoesNoHarm, setup, teardown),
    cmocka_unit_test_setup_teardown(LedDriver_OutOfBoundsProducesRuntimeError, setup, teardown),
    cmocka_unit_test_setup_teardown(LedDriver_OutOfBoundsToDo, NULL, NULL),
    cmocka_unit_test_setup_teardown(LedDriver_CheckIsOn, setup, teardown),
    cmocka_unit_test_setup_teardown(LedDriver_CheckIsOff, setup, teardown),
    cmocka_unit_test_setup_teardown(LedDriver_OutOfBoundsLedsAreAlwaysOff, setup, teardown),
  };
  return cmocka_run_group_tests(tests, NULL, NULL);
}

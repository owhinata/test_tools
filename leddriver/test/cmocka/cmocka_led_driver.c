#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <setjmp.h>
#include <cmocka.h>

#include <stdlib.h>
#include "led/driver.h"

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

int main(void) {
  const struct CMUnitTest tests[] = {
    cmocka_unit_test_setup_teardown(LedDriver_LedsOffAfterCreate, setup, teardown),
    cmocka_unit_test_setup_teardown(LedDriver_TrunOnLedOne, setup, teardown),
    cmocka_unit_test_setup_teardown(LedDriver_TrunOffLedOne, setup, teardown),
  };
  return cmocka_run_group_tests(tests, NULL, NULL);
}

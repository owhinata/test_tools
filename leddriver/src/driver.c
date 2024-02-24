
#include "led/driver.h"

#include "util/runtime_error.h"

enum {
  ALL_LEDS_ON = ~0,
  ALL_LEDS_OFF = ~ALL_LEDS_ON
};

enum {
  FIRST_LED = 1,
  LAST_LED = 16,
};

static uint16_t* led_address_;
static uint16_t led_image_;

static bool is_led_out_of_bounds(int ledno) {
  return (ledno < FIRST_LED) || (ledno > LAST_LED);
}

static uint16_t convert_ledno_to_bit(int ledno) {
  return 1 << (ledno - 1);
}

static void set_led_image_bit(int ledno) {
  led_image_ |= convert_ledno_to_bit(ledno);
}

static void clear_led_image_bit(int ledno) {
  led_image_ &= ~convert_ledno_to_bit(ledno);
}

static void update_hardware(void) {
  *led_address_ = led_image_;
}

void LedDriver_Create(uint16_t* address) {
  led_address_ = address;
  led_image_ = ALL_LEDS_OFF;
  update_hardware();
}

void LedDriver_Destroy(void) {
}

void LedDriver_TurnOn(int ledno) {
  if (is_led_out_of_bounds(ledno)) {
    RUNTIME_ERROR("LED Driver: out-of-bounds LED", -1);
    return;
  }
  set_led_image_bit(ledno);
  update_hardware();
}

void LedDriver_TurnOff(int ledno) {
  if (is_led_out_of_bounds(ledno)) {
    return;
  }
  clear_led_image_bit(ledno);
  update_hardware();
}

void LedDriver_TurnAllOn(void) {
  led_image_ = ALL_LEDS_ON;
  update_hardware();
}

void LedDriver_TurnAllOff(void) {
  led_image_ = ALL_LEDS_OFF;
  update_hardware();
}

bool LedDriver_IsOn(int ledno) {
  if (is_led_out_of_bounds(ledno)) {
    return false;
  }
  return (led_image_ & convert_ledno_to_bit(ledno));
}

bool LedDriver_IsOff(int ledno) {
  return !LedDriver_IsOn(ledno);
}

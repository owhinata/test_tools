
#include "led/driver.h"

static uint16_t* led_address_;

void LedDriver_Create(uint16_t* address) {
  led_address_ = address;
  *led_address_ = 0;
}

void LedDriver_Destroy(void) {
}

void LedDriver_TurnOn(int ledno) {
  *led_address_ = 1;
}

void LedDriver_TurnOff(int ledno) {
  *led_address_ = 0;
}

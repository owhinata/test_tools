
#ifndef LED_DRIVER_H_
#define LED_DRIVER_H_

#include <stdbool.h>
#include <stdint.h>

#if defined(__cplusplus)
extern "C" {
#endif

void LedDriver_Create(uint16_t* address);
void LedDriver_Destroy(void);
void LedDriver_TurnOn(int ledno);
void LedDriver_TurnOff(int ledno);
void LedDriver_TurnAllOn(void);
void LedDriver_TurnAllOff(void);
bool LedDriver_IsOn(int ledno);
bool LedDriver_IsOff(int ledno);

#ifdef __cplusplus
}
#endif

#endif  // LED_DRIVER_H_

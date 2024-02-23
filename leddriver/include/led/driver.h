
#ifndef LED_DRIVER_H_
#define LED_DRIVER_H_

#include <stdint.h>

#if defined(__cplusplus)
extern "C" {
#endif

void LedDriver_Create(uint16_t* address);
void LedDriver_Destroy(void);
void LedDriver_TurnOn(int ledno);
void LedDriver_TurnOff(int ledno);

#ifdef __cplusplus
}
#endif

#endif  // LED_DRIVER_H_

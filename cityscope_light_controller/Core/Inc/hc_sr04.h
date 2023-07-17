/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HC_SR04_H__
#define __HC_SR04_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"

void HCSR04_Read (void);
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim);

#ifdef __cplusplus
}
#endif
#endif /*__ GPIO_H__ */
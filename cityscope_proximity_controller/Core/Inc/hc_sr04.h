/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HC_SR04_H__
#define __HC_SR04_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"

void HCSR04_Init(TIM_HandleTypeDef *htim);
void HCSR04_Read (void);
void HCSR04_Read_GPIO(void);
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim);
int16_t HCSR04_Get_Distance(void);
#ifdef __cplusplus
}
#endif
#endif /*__ GPIO_H__ */
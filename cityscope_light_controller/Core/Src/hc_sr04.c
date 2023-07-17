#include "tim.h"
#include "hc_sr04.h"

uint32_t IC_Val1 = 0;
uint32_t IC_Val2 = 0;
uint32_t Difference = 0;
uint8_t Echo_Raised = 0;
uint32_t Distance = 0;

void HCSR04_Read(void)
{
    HAL_GPIO_WritePin(HC_TRIG_GPIO_Port, HC_TRIG_Pin, GPIO_PIN_SET); // pull the TRIG pin HIGH
    delay_us(10);                                                    // wait for 10 us
    // osDelay(1);
    HAL_GPIO_WritePin(HC_TRIG_GPIO_Port, HC_TRIG_Pin, GPIO_PIN_RESET); // pull the TRIG pin low
    HAL_TIM_IC_Start_IT(&htim17, TIM_CHANNEL_1);
}


void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1) // if the interrupt source is channel1
    {
        if (!Echo_Raised) // if the first value is not captured
        {
            HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
            IC_Val1 = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1); // read the first value
            Echo_Raised = 1;                                          // set the first captured as true
        }
        else
        {
            IC_Val2 = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1); // read second value
            __HAL_TIM_SET_COUNTER(htim, 0);                           // reset the counter

            if (IC_Val2 > IC_Val1)
            {
                Difference = IC_Val2 - IC_Val1;
            }

            else if (IC_Val1 > IC_Val2)
            {
                Difference = (0xffff - IC_Val1) + IC_Val2;
            }

            Distance = Difference * .034 / 2;
            Echo_Raised = 0; // set it back to false
        }
    }
}
/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file    ws2812.h
 * @brief   This file contains all the function prototypes for
 *          the ws2812.c file
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2023 CSL Taipei Tech.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
/* USER CODE END Header */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __WS2812_H__
#define __WS2812_H__

#define WS2821_MAX_LED 1000
#define Node_ID_mini 19
#define Node_ID_max 30
#define T0H 400   // ns
#define T1H 900   // ns
#define T0L 900   // ns
#define T1L 900   // ns
#define RES 6000 // ns
#define cycle 450 // someone anyone pls told me why this thing work?
#ifdef __cplusplus
extern "C"
{
#endif

#include "main.h"
#include <stdint.h>
#include <stdbool.h>
    inline void delay_ns(uint16_t ns);
    void sendByte(uint8_t byte);
    void sendPixel(uint8_t r, uint8_t g, uint8_t b);
    void ws2812_reset(void);
    void clear(void);
#ifdef __cplusplus
}
#endif

#endif /* __WS2812_H__ */

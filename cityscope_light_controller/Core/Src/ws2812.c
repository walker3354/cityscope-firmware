#include "tim.h"
#include "ws2812.h"

inline void delay_ns(uint16_t ns)
{
  uint16_t iterations = ns / cycle;
  for (volatile uint16_t i = 0; i < iterations; i++)
  {
    __NOP();
  }
}

void sendByte(uint8_t byte)
{
  for (uint8_t bit = 0x80; bit; bit >>= 1)
  {
    if (byte & bit) // 1 bit
    {
      HAL_GPIO_WritePin(WS2812_GPIO_Port, WS2812_Pin, 1);
      delay_ns(T1H);
      HAL_GPIO_WritePin(WS2812_GPIO_Port, WS2812_Pin, 0);
      delay_ns(T1L);
    }
    else // 0 bit
    {
      HAL_GPIO_WritePin(WS2812_GPIO_Port, WS2812_Pin, 1);
      delay_ns(T0H);
      HAL_GPIO_WritePin(WS2812_GPIO_Port, WS2812_Pin, 0);
      delay_ns(T0L);
    }
  }
}
void sendPixel(uint8_t r, uint8_t g, uint8_t b)
{
  sendByte(g);
  sendByte(r);
  sendByte(b);
}

void ws2812_reset(void)
{
  HAL_GPIO_WritePin(WS2812_GPIO_Port, WS2812_Pin, 0);
  delay_ns(RES);
}

void clear(void)
{
  for (int i = 0; i < WS2821_MAX_LED; i++)
  {
    sendPixel(0, 0, 0);
  }
  ws2812_reset();
}
/*
 * hx711.c
 *
 *  Created on: May 10, 2023
 *      Author: JH_LAB
 */
#include "hx711.h"
#include "usart.h"
#include "stdio.h"



float loadcell_slope = -1/1600.00f; // Convert the raw data to weight (replace the calibration factor with your own)
float loadcell_bias = 10002.0;
float Hx711Data = 0.0;
float initialLoadCellValue = 0.0; // 초기 로드셀 값을 저장할 변수



void HX711_Init(void)
{
  // Set the SCK pin to low
  HAL_GPIO_WritePin(HX711_SCK_GPIO_Port, HX711_SCK_Pin, GPIO_PIN_RESET);
}

int32_t Read_HX711(void)
{
  int32_t data = 0;

  // Wait until the DT pin goes low
  while (HAL_GPIO_ReadPin(HX711_DT_GPIO_Port, HX711_DT_Pin) == GPIO_PIN_SET);

  // Read the 24-bit data
  for (int i = 0; i < 24; i++)
  {
    // Generate a clock pulse on SCK pin
    HAL_GPIO_WritePin(HX711_SCK_GPIO_Port, HX711_SCK_Pin, GPIO_PIN_SET);
    DelayMicroseconds(1);
    data = (data << 1);
    if (HAL_GPIO_ReadPin(HX711_DT_GPIO_Port, HX711_DT_Pin) == GPIO_PIN_SET)
    {
      data++;
    }
    HAL_GPIO_WritePin(HX711_SCK_GPIO_Port, HX711_SCK_Pin, GPIO_PIN_RESET);
    DelayMicroseconds(1);
  }

  // Generate an additional 25th pulse to set the HX711 back to idle mode
  HAL_GPIO_WritePin(HX711_SCK_GPIO_Port, HX711_SCK_Pin, GPIO_PIN_SET);
  DelayMicroseconds(1);
  HAL_GPIO_WritePin(HX711_SCK_GPIO_Port, HX711_SCK_Pin, GPIO_PIN_RESET);
  DelayMicroseconds(1);


  // Return the 24-bit data
  return data;
}

void UART_SendWeight_g(float rawData,float loadcell_slope,float loadcell_bias)
{
  float weight = loadcell_slope * rawData  + loadcell_bias;
  char buffer[32];
  int data = sprintf(buffer, "%.2f", weight);

  // Send the buffer content via UART
#if 0
  int len = sprintf(buffer, "Weight(g):");
  HAL_UART_Transmit(&huart1, (uint8_t *)buffer, len, 1000);
#endif
  HAL_UART_Transmit(&huart1, (uint8_t *)buffer, data, 1000);
}

void UART_SendWeight_N(float rawData,float loadcell_slope,float loadcell_bias)
{
  float weight = loadcell_slope * rawData  + loadcell_bias;
  weight *=9.8;
  weight /=1000;
  char buffer[32];
  int len = sprintf(buffer, "%.4f", weight);

  // Send the buffer content via UART
  HAL_UART_Transmit(&huart1, (uint8_t *)buffer, len, 1000);
}

float UART_returnWeight_N(float rawData,float loadcell_slope,float loadcell_bias)
{
  float weight = loadcell_slope * rawData  + loadcell_bias;
  weight *=9.8;
  weight /=1000;
  return weight;
}
void DelayMicroseconds(uint32_t microseconds)
{
  uint32_t ticks = microseconds;
  while (ticks--)
  {
    __NOP();
  }
}

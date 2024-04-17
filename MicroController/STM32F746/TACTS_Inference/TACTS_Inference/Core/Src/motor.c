/*
 * motor.c
 *
 *  Created on: Apr 28, 2023
 *      Author: JH_LAB
 */
#include "stm32f7xx_hal.h"
#include "motor.h"
#include "usart.h"

#define PULSE 200
#define GEAR 139

void stepRev(int ANG) {

	// ENA D2 PG7 GPIOG GPIO_PIN_6
	// CLK D3 PB4 GPIOB GPIO_PIN_4
	// DIR D4 PG7 GPIOG GPIO_PIN_7


  HAL_GPIO_WritePin(GPIOG, GPIO_PIN_6, GPIO_PIN_RESET);  // ENA

  if (ANG != 0) {
    int direction = (ANG > 0) ? 1 : -1;
    ANG *= direction;
    HAL_GPIO_WritePin(GPIOG, GPIO_PIN_7, direction == 1 ? GPIO_PIN_SET : GPIO_PIN_RESET); // DIR
    HAL_GPIO_WritePin(GPIOG, GPIO_PIN_6, GPIO_PIN_RESET); // ENA
    uint32_t steps = PULSE * GEAR * ANG / 360.0;

    for (int i = 0; i < steps; i++) {
      HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_SET); //CLK
      HAL_Delay(1); // 변경된 지연 함수 사용
      HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_RESET); //CLK
      HAL_Delay(1); // 변경된 지연 함수 사용
    }

  }
  else {
    HAL_GPIO_WritePin(GPIOG, GPIO_PIN_6, GPIO_PIN_RESET); // ENA
  }

}

void stepLin(int DIST) {

	// ENA D5 PI0 GPIOI GPIO_PIN_0
	// CLK D8 PI2 GPIOI GPIO_PIN_2
	// DIR D7 PI3 GPIOI GPIO_PIN_3

  HAL_GPIO_WritePin(GPIOI, GPIO_PIN_0, GPIO_PIN_SET);  // ENA

  if (DIST != 0) {
    int direction = (DIST > 0) ? 1 : -1;
    DIST *= direction;
    HAL_GPIO_WritePin(GPIOI, GPIO_PIN_3, direction == 1 ? GPIO_PIN_SET : GPIO_PIN_RESET); // DIR
    HAL_GPIO_WritePin(GPIOI, GPIO_PIN_0, GPIO_PIN_RESET);  // ENA
    uint32_t steps = 25*DIST;
	//HAL_UART_Transmit(&huart1, (uint8_t*)txMsg, sprintf((char*)txMsg, "%d\n ", steps), 1000);


    for (int i = 0; i < steps; i++) {
      HAL_GPIO_WritePin(GPIOI, GPIO_PIN_2, GPIO_PIN_SET); // CLK
      HAL_Delay(1);
      HAL_GPIO_WritePin(GPIOI, GPIO_PIN_2, GPIO_PIN_RESET); // CLK
      HAL_Delay(1);
    }
  }
  else {
    HAL_GPIO_WritePin(GPIOI, GPIO_PIN_0, GPIO_PIN_RESET);  // ENA
  }

  HAL_GPIO_WritePin(GPIOI, GPIO_PIN_0, GPIO_PIN_SET);  // ENA

}

void servo_angle(TIM_HandleTypeDef *htim, uint32_t channel, int step) {

	// 1 step is 0.8 mm
    if (step > 17)
    	step = 17; // 최대 각도 제한

    int pulse_width = 21-step; // 듀티 사이클 계산 (0도에서 180도까지)
    __HAL_TIM_SET_COMPARE(htim, channel, pulse_width); // 듀티 사이클 변경
}




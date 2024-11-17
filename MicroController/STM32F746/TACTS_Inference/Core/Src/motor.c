/*
 * motor.c
 *
 *  Created on: Apr 28, 2023
 *      Author: JH_LAB
 */
#include "stm32f7xx_hal.h"
#include "motor.h"
#include "usart.h"
#include "stdio.h"

#define PULSE 200
#define GEAR 139

#define MIN_PULSE 50   // 1ms 펄스에 해당
#define MAX_PULSE 100  // 2ms 펄스에 해당

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

    int pulse_width = step; // 듀티 사이클 계산 (0도에서 180도까지)
    __HAL_TIM_SET_COMPARE(htim, channel, pulse_width); // 듀티 사이클 변경
    HAL_UART_Transmit(&huart1, (uint8_t*)txMsg, sprintf((char*)txMsg, "pulse_width : %d \n\r", pulse_width), 100);

}

void setServoAngle(TIM_HandleTypeDef *htim, uint32_t channel, uint8_t value) {
    uint16_t pulse_length;
    // 각도에 따른 펄스 길이 계산
    if(value<0){value = 0;}
    if(value>100){value = 100;}
    pulse_length = value+22;
	__HAL_TIM_SET_COMPARE(htim, channel, pulse_length); // 듀티 사이클 변경
    //HAL_UART_Transmit(&huart1, (uint8_t*)txMsg, sprintf((char*)txMsg, "pulse_length : %2f \n\r", value*0.47), 100);

}
void sayServoAngle(TIM_HandleTypeDef *htim, uint32_t channel, uint8_t value) {
    uint16_t pulse_length;
    // 각도에 따른 펄스 길이 계산
    if(value<0){value = 0;}
    if(value>100){value = 100;}
    pulse_length = value+22;
	__HAL_TIM_SET_COMPARE(htim, channel, pulse_length); // 듀티 사이클 변경
    HAL_UART_Transmit(&huart1, (uint8_t*)txMsg, sprintf((char*)txMsg, "pulse_length : %2f \n\r", value*0.47), 100);

}




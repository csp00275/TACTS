/*
 * avgstd.c
 *
 *  Created on: 2023. 11. 9.
 *      Author: JH_LAB
 */


#include "avgstd.h"
#include "math.h"
#include "usart.h"

float sensorValues[NUM_SENSOR][NUM_READINGS-throwSomenumber] = {0};
float sensorAverages[NUM_SENSOR] = {0};
float sensorStdDevs[NUM_SENSOR] = {0};
int readingCount[NUM_SENSOR] = {0};

void CalculateStats(int sensorIndex) {
    float sum = 0;
    float mean = 0;
    float stdDevSum = 0;
    int count = readingCount[sensorIndex];

    // 평균 계산
    for (int i = 0; i < count; i++) { sum += sensorValues[sensorIndex][i];}
    mean = sum / count;
    sensorAverages[sensorIndex] = mean;
    // 표준편차 계산
    for (int i = 0; i < count; i++) { stdDevSum += pow(sensorValues[sensorIndex][i] - mean, 2);}
    sensorStdDevs[sensorIndex] = sqrt(stdDevSum / count);
}

// 평균과 표준편차를 UART로 전송하는 함수
void TransmitStats() {
	HAL_UART_Transmit(&huart1, txMsg, sprintf((char*)txMsg, "Sensor Avg Std\r\n"), 100);
    for (int i = 0; i < NUM_SENSOR; i++) {
        CalculateStats(i); // 통계 계산
    	HAL_UART_Transmit(&huart1, txMsg, sprintf((char*)txMsg, "%d %.2f %.2f\r\n", i, sensorAverages[i], sensorStdDevs[i]), 100);
    }
}

void ResetSensorData() {
    // 모든 센서 값과 읽기 횟수를 0으로 설정
    for (int i = 0; i < NUM_SENSOR; i++) {
        memset(sensorValues[i], 0, sizeof(sensorValues[i]));
        readingCount[i] = 0;
    }
}

void InitStats(){
	for(int i=0; i<NUM_SENSOR;i++){
		sensorAverages[i] = 0;
		sensorStdDevs[i] = 0;
	}
}

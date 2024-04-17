/*
 * avgstd.h
 *
 *  Created on: 2023. 11. 9.
 *      Author: JH_LAB
 */

#ifndef INC_AVGSTD_H_
#define INC_AVGSTD_H_

#include "vl53l0x_jh.h"

#define NUM_READINGS 120
#define throwSomenumber 20


extern float sensorValues[NUM_SENSOR][NUM_READINGS-throwSomenumber];
extern float sensorAverages[NUM_SENSOR];
extern float sensorStdDevs[NUM_SENSOR];
extern int readingCount[NUM_SENSOR];

void CalculateStats(int sensorIndex);
void TransmitStats();
void ResetSensorData();
void InitStats();

#endif /* INC_AVGSTD_H_ */

/*
 * command.h
 *
 *  Created on: Apr 16, 2024
 *      Author: 21310
 */

#ifndef INC_COMMAND_H_
#define INC_COMMAND_H_

#include "main.h"

#include "string.h"
#include "stdio.h"
#include "vl53l0x_jh.h"
#include "kalman.h"
#include "i2c.h"
#include "usart.h"
#include "threeLine.h"
#include "threeLine_data.h"
#include "ai.h"
#include "avgstd.h"
#include "motor.h"
#include "hx711.h"



void ProcessCommand(uint8_t *command);
void SensorI2CCommand();
void SetI2CCommand();
void RevCommand(char *arg);
void LinCommand(char *arg);
void ServoCommand();
void Servo2Command();
void Servo3Command();
void AvgStdCommand();
void InferenceHeatI2CCommand();
void PointingVertical();
void PointingRadial();
void InitializaionCalibrationCommand();
void AutoI2CCommand();
void LoadcellCommand();




#endif /* INC_COMMAND_H_ */

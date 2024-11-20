/*
 * command.c
 *
 *  Created on: Apr 16, 2024
 *      Author: 21310
 */
#include "command.h"

#define data

volatile uint8_t command_in_progress = 0; // 명령 실행 중 상태 플래그


extern TIM_HandleTypeDef htim2;


void ProcessCommand(uint8_t *commandBuffer)
{

    if (command_in_progress) {
        HAL_UART_Transmit(&huart1, (uint8_t*)"Command is currently executing, please wait...\n", 48, 100);
        return;
    }

    command_in_progress = 1; // 명령 실행 상태 설정

    char *command = strtok((char*)commandBuffer, " "); // Command separation
    char *argument = strtok(NULL, " "); // argument seperation

    if (strcmp((char*)command, "echo") == 0) {HAL_UART_Transmit(&huart1, txMsg, sprintf((char*)txMsg, "echo\n"), 100);}
    else if (strcmp((char*)command, "sensori2c") == 0) {SensorI2CCommand();} //sensori2c
    else if (strcmp((char*)command, "seti2c") == 0) {SetI2CCommand();} //seti2c
    else if (strcmp((char*)command, "rev") == 0) {RevCommand(argument);}
    else if (strcmp((char*)command, "lin") == 0) {LinCommand(argument);}
    else if (strcmp((char*)command, "servo") == 0) {ServoCommand(argument);}
    else if (strcmp((char*)command, "servo2") == 0) {Servo2Command(argument);}
    else if (strcmp((char*)command, "avg") == 0) {AvgStdCommand();}
    else if (strcmp((char*)command, "inferheati2c") == 0) {InferenceHeatI2CCommand();} //infercnni2c
    else if (strcmp((char*)command, "pointv") == 0) {PointingVertical();} // (0,20) -> (0,140)
    else if (strcmp((char*)command, "pointr") == 0) {PointingRadial();} // (0,20) -> (0,140)
    else if (strcmp((char*)command, "ini") == 0) {InitializaionCalibrationCommand();}
    else if (strcmp((char*)command, "autoi2c") == 0) {AutoI2CCommand();}
    else if (strcmp((char*)command, "loadcell") == 0) {LoadcellCommand();}
    else {HAL_UART_Transmit(&huart1, txMsg, sprintf((char*)txMsg, "Please insert correct command\n"), 100);}

    command_in_progress = 0; // 명령 실행 완료 상태 해제
}


void SensorI2CCommand(){
	ResetAllDevices();
	setOnAllDevices();
	HAL_UART_Transmit(&huart1, (uint8_t*)txMsg, sprintf((char*)txMsg, "sensor test\r\n"), 100);
	uint32_t startTime = 0, endTime = 0, diffTime = 0;

    for(int count =0; count < NUM_READINGS; count++){
    	uint8_t sensorCount = 0;
    	startTime = HAL_GetTick();
		for (int i = 0; i < NUM_SENSOR; i++) {
			Dev = &vl53l0x_s[i];
			VL53L0X_PerformContinuousRangingMeasurement(Dev, &RangingData); // 1500us
			if (RangingData.RangeStatus == 0) {
			  if (RangingData.RangeMilliMeter < 100) {
				  filteredValue[i] = Kalman_Estimate(&filters[i], RangingData.RangeMilliMeter);
				  //filteredValue[i] = RangingData.RangeMilliMeter;
				  sensorValues[i][readingCount[i]] = filteredValue[i];
				  if(count>throwSomenumber){
				  readingCount[i]++;}
				  sensorCount++;
			  }
			}else{
				  //HAL_UART_Transmit(&huart1, (uint8_t*)txMsg, sprintf((char*)txMsg, "%d ", RangingData.RangeStatus), 500);
				  // 1 : Sigma Fail | 2 : Signal Fail | 3 : Min Range Fail | 4 : Phase Fail | 5 : Hardware Fail | 255 : No update
			  }
		}
		do {
		    endTime = HAL_GetTick();
		    diffTime = endTime - startTime;
		} while (diffTime <= TIMBUDGET);
		#ifdef data
		for (int i = 0; i < NUM_SENSOR; i++) {
			  HAL_UART_Transmit(&huart1, (uint8_t*)txMsg, sprintf((char*)txMsg, "%.1f ", filteredValue[i]), 500);
		  }
		HAL_UART_Transmit(&huart1, (uint8_t*)txMsg, sprintf((char*)txMsg, "%d ", NUM_READINGS), 100);
				HAL_UART_Transmit(&huart1, (uint8_t*)txMsg, sprintf((char*)txMsg, "%d ", sensorCount), 100);

		HAL_UART_Transmit(&huart1, (uint8_t*)txMsg, sprintf((char*)txMsg, "%lu\n", diffTime), 100);
		#endif
		startTime = 0;
		endTime = 0;
		diffTime = 0;
    }
    TransmitStats();
    ResetSensorData();
}

void SetI2CCommand(){
	HAL_UART_Transmit(&huart1, (uint8_t*)txMsg, sprintf((char*)txMsg, "SetCommand\n\r"), 100);

	ResetAllDevices();
	memset(vl53l0x_s, 0, sizeof(VL53L0X_Dev_t));
  	for (int i = 0; i < NUM_SENSOR; i++) {
  	    uint8_t q = i / 12;
  	    uint8_t r = i % 12;
  	    uint8_t active_device = q * 2 + (r >= 8 ? 1 : 0);
  	    uint8_t channel = (r >= 8) ? r - 8 : r;

        ResetDevicesExcept(active_device);
        setActiveTcaChannel(active_device,channel);
  		Dev = &vl53l0x_s[i];
  		Dev->I2cHandle = &hi2c1;
  		Dev->I2cDevAddr = VL53L0X_ADDR;
  		Dev->comms_type = 1;
  		Dev->comms_speed_khz = 100;
  		uint8_t newadd = 0x52 + 2*i;
  		VL53L0X_SetDeviceAddress(Dev, newadd);
  		Dev->I2cDevAddr = newadd;

  		VL53L0X_WaitDeviceBooted( Dev );
  		VL53L0X_DataInit( Dev );
  		VL53L0X_StaticInit( Dev );
  		VL53L0X_SetDeviceMode(Dev, VL53L0X_DEVICEMODE_CONTINUOUS_RANGING);

		VL53L0X_SetReferenceSpads(Dev, refSpadCountHost[i], isApertureSpadsHost[i]);
  		VL53L0X_SetRefCalibration(Dev, VhvSettingsHost[i], PhaseCalHost[i]);

  		VL53L0X_SetLimitCheckEnable(Dev, VL53L0X_CHECKENABLE_SIGMA_FINAL_RANGE, 1);
  		VL53L0X_SetLimitCheckEnable(Dev, VL53L0X_CHECKENABLE_SIGNAL_RATE_FINAL_RANGE, 1);
  		VL53L0X_SetLimitCheckValue(Dev, VL53L0X_CHECKENABLE_SIGNAL_RATE_FINAL_RANGE, (FixPoint1616_t)(0.1*65536));
  		VL53L0X_SetLimitCheckValue(Dev, VL53L0X_CHECKENABLE_SIGMA_FINAL_RANGE, (FixPoint1616_t)(60*65536));
  		VL53L0X_SetMeasurementTimingBudgetMicroSeconds(Dev, 100000);
  		VL53L0X_SetVcselPulsePeriod(Dev, VL53L0X_VCSEL_PERIOD_PRE_RANGE, 18);
  		VL53L0X_SetVcselPulsePeriod(Dev, VL53L0X_VCSEL_PERIOD_FINAL_RANGE, 14);

		Kalman_Init(&filters[i], Q, R, P, 0);  // Q, R, P

		#ifdef data
 		HAL_UART_Transmit(&huart1, (uint8_t*)txMsg, sprintf((char*)txMsg, "%02d:(",i), 100);
 		HAL_UART_Transmit(&huart1, (uint8_t*)txMsg, sprintf((char*)txMsg, "%02lu ",refSpadCountHost[i]), 100);
 		HAL_UART_Transmit(&huart1, (uint8_t*)txMsg, sprintf((char*)txMsg, "%02d ",isApertureSpadsHost[i]), 100);
 		HAL_UART_Transmit(&huart1, (uint8_t*)txMsg, sprintf((char*)txMsg, "%02d ",VhvSettingsHost[i]), 100);
 		HAL_UART_Transmit(&huart1, (uint8_t*)txMsg, sprintf((char*)txMsg, "%02d) ",PhaseCalHost[i]), 100);
 		if(i%12 ==11){HAL_UART_Transmit(&huart1, (uint8_t*)txMsg, sprintf((char*)txMsg, "\n\r"), 100);}
		#endif
  	}
  	InitStats();
}

void RevCommand(char *arg){
    int step_rev_angle;
    uint32_t startTime, endTime, elapsedTime;
    if(sscanf(arg, "%d", &step_rev_angle) == 1){
        startTime = HAL_GetTick();
		HAL_UART_Transmit(&huart1, (uint8_t*)txMsg, sprintf((char*)txMsg, "%d deg revolution Start \n\r",step_rev_angle), 100);
        stepRev(step_rev_angle);
		HAL_UART_Transmit(&huart1, (uint8_t*)txMsg, sprintf((char*)txMsg, "%d deg revolution End \n\r",step_rev_angle), 100);
		endTime = HAL_GetTick();
		elapsedTime = endTime - startTime;
        HAL_UART_Transmit(&huart1, (uint8_t*)txMsg, sprintf((char*)txMsg, "Elapsed Time: %lu ms\n\r", elapsedTime), 100);
    }else{
    	HAL_UART_Transmit(&huart1, (uint8_t*)txMsg, sprintf((char*)txMsg, "invalid data\r\n"), 100);
    }
    HAL_Delay(1000); // Delay for 1 second
}

void LinCommand(char *arg){
    int step_lin_dist = 0;
    uint32_t startTime, endTime, elapsedTime;
    if (sscanf(arg, "%d", &step_lin_dist) == 1) {
        startTime = HAL_GetTick();
		HAL_UART_Transmit(&huart1, (uint8_t*)txMsg, sprintf((char*)txMsg, "%d mm lin Still moving \n\r",step_lin_dist), 100);
        stepLin(step_lin_dist);
        HAL_UART_Transmit(&huart1, (uint8_t*)txMsg, sprintf((char*)txMsg, "%d mm lin End\n\r", step_lin_dist), 100);
		endTime = HAL_GetTick();
		elapsedTime = endTime - startTime;
        HAL_UART_Transmit(&huart1, (uint8_t*)txMsg, sprintf((char*)txMsg, "Elapsed Time: %lu ms\n\r", elapsedTime), 100);
    } else {
        HAL_UART_Transmit(&huart1, (uint8_t*)txMsg, sprintf((char*)txMsg, "invalid data\r\n"), 100);
    }
    HAL_Delay(1000); // Delay for 1 second
}

void ServoCommand(char *arg){
    float servo_angle_val = 0;
    if(sscanf(arg, "%f", &servo_angle_val) == 1) {
    	HAL_UART_Transmit(&huart1, (uint8_t*)txMsg, sprintf((char*)txMsg, "%.2f servo Still moving \n\r", servo_angle_val), 100);
    	sayServoAngle(&htim2, TIM_CHANNEL_1, servo_angle_val);
    	HAL_UART_Transmit(&huart1, (uint8_t*)txMsg, sprintf((char*)txMsg, "%.2f servo End \n\r", servo_angle_val), 100);
        HAL_Delay(2000); // Delay for 2 seconds
        sayServoAngle(&htim2, TIM_CHANNEL_1, 0); // return to servo origin
    }else{
        HAL_UART_Transmit(&huart1, (uint8_t*)txMsg, sprintf((char*)txMsg, "invalid data\r\n"), 100);
    }
}

void Servo2Command(char *arg){
    float servo_angle_val = 0;
    if(sscanf(arg, "%f", &servo_angle_val) == 1) {
    	HAL_UART_Transmit(&huart1, (uint8_t*)txMsg, sprintf((char*)txMsg, "%.2f servo Still moving \n\r", servo_angle_val), 100);
    	sayServoAngle(&htim2, TIM_CHANNEL_1, servo_angle_val);
    	HAL_UART_Transmit(&huart1, (uint8_t*)txMsg, sprintf((char*)txMsg, "%.2f servo End \n\r", servo_angle_val), 100);
    }else{
        HAL_UART_Transmit(&huart1, (uint8_t*)txMsg, sprintf((char*)txMsg, "invalid data\r\n"), 100);
    }
}




void AvgStdCommand(){
	HAL_UART_Transmit(&huart1, (uint8_t*)txMsg, sprintf((char*)txMsg, "Avg Std Force Z\n" ), 1000);
    for(int i = 0; i < sizeof(Xmean)/sizeof(Xmean[0]); i++) {
        HAL_UART_Transmit(&huart1, (uint8_t*)txMsg, sprintf((char*)txMsg, "%.2f ", Xmean[i]), 1000);
        if(i%8==7){HAL_UART_Transmit(&huart1, (uint8_t*)txMsg, sprintf((char*)txMsg, "\n"), 1000);}
    }
    for(int i = 0; i < sizeof(Xstd)/sizeof(Xstd[0]); i++) {
        HAL_UART_Transmit(&huart1, (uint8_t*)txMsg, sprintf((char*)txMsg, "%.2f ", Xstd[i]), 1000);
        if(i%8==7){HAL_UART_Transmit(&huart1, (uint8_t*)txMsg, sprintf((char*)txMsg, "\n"), 1000);}
    }
    HAL_UART_Transmit(&huart1, (uint8_t*)txMsg, sprintf((char*)txMsg, "%.2f ", Fminmax[0]), 1000);
    HAL_UART_Transmit(&huart1, (uint8_t*)txMsg, sprintf((char*)txMsg, "%.2f ", Fminmax[1]), 1000);
	HAL_UART_Transmit(&huart1, (uint8_t*)txMsg, sprintf((char*)txMsg, "\n"), 1000);
    HAL_UART_Transmit(&huart1, (uint8_t*)txMsg, sprintf((char*)txMsg, "%.2f ", Zminmax[0]), 1000);
    HAL_UART_Transmit(&huart1, (uint8_t*)txMsg, sprintf((char*)txMsg, "%.2f ", Zminmax[1]), 1000);
	HAL_UART_Transmit(&huart1, (uint8_t*)txMsg, sprintf((char*)txMsg, "\n"), 1000);
}


void InferenceHeatI2CCommand()
{
	SetI2CCommand();
	SensorI2CCommand();
	ResetAllDevices();
	setOnAllDevices();
    HAL_UART_Transmit(&huart1, (uint8_t*)txMsg, sprintf((char*)txMsg, "sensor test\r\n"), 100);
    uint32_t startTime, endTime, diffTime;
    uint8_t isBelowMinusTwo = 0;

    for (int count =0; count <50000;count ++){
    	uint8_t tofCount =0;
        isBelowMinusTwo = 0; // -2보다 작은 값이 있는지 여부를 저장
    	startTime = HAL_GetTick();
        for (int i = 0; i < NUM_SENSOR; i++) {
            Dev = &vl53l0x_s[i];
            VL53L0X_PerformContinuousRangingMeasurement(Dev, &RangingData); // 1500 uss
            if (RangingData.RangeStatus == 0) {
  			  if (RangingData.RangeMilliMeter < sensorAverages[i]+20) {
            	filteredValue[i] = Kalman_Estimate(&filters[i], RangingData.RangeMilliMeter); // 500 us
                filteredValue[i] -= sensorAverages[i];
                //filteredValue[i] -= Xmean[i];
                filteredValue[i] /= Xstd[i];
                tofCount++;
                if (filteredValue[i] < -2.0) {
                	isBelowMinusTwo++;

                }
  			  }
            }
        }

        in_data[0] = filteredValue[0];
        in_data[1] = filteredValue[1];
        in_data[2] = filteredValue[2];
        in_data[3] = filteredValue[3];
        in_data[4] = filteredValue[4];
        in_data[5] = filteredValue[5];
        in_data[6] = filteredValue[6];
        in_data[7] = filteredValue[7];
        in_data[8] = filteredValue[8];
        in_data[9] = filteredValue[9];
        in_data[10] = filteredValue[10];
        in_data[11] = filteredValue[11];
        in_data[12] = filteredValue[0];

        in_data[13] = filteredValue[12];
        in_data[14] = filteredValue[13];
        in_data[15] = filteredValue[14];
        in_data[16] = filteredValue[15];
        in_data[17] = filteredValue[16];
        in_data[18] = filteredValue[17];
        in_data[19] = filteredValue[18];
        in_data[20] = filteredValue[19];
        in_data[21] = filteredValue[20];
        in_data[22] = filteredValue[21];
        in_data[23] = filteredValue[22];
        in_data[24] = filteredValue[23];
        in_data[25] = filteredValue[12];
		#if NUM_SENSOR >= 36
        in_data[26] = filteredValue[24];
        in_data[27] = filteredValue[25];
        in_data[28] = filteredValue[26];
        in_data[29] = filteredValue[27];
        in_data[30] = filteredValue[28];
        in_data[31] = filteredValue[29];
        in_data[32] = filteredValue[30];
        in_data[33] = filteredValue[31];
        in_data[34] = filteredValue[32];
        in_data[35] = filteredValue[33];
        in_data[36] = filteredValue[34];
        in_data[37] = filteredValue[35];
        in_data[38] = filteredValue[24];
		#endif
		#if NUM_SENSOR >= 48
		in_data[39] = filteredValue[36];
		in_data[40] = filteredValue[37];
		in_data[41] = filteredValue[38];
		in_data[42] = filteredValue[39];
		in_data[43] = filteredValue[40];
		in_data[44] = filteredValue[41];
		in_data[45] = filteredValue[42];
		in_data[46] = filteredValue[43];
		in_data[47] = filteredValue[44];
		in_data[48] = filteredValue[45];
		in_data[49] = filteredValue[46];
		in_data[50] = filteredValue[47];
		in_data[51] = filteredValue[36];
		#endif

		if(tofCount == NUM_SENSOR){
	        for(int i=0; i<NUM_SENSOR;i++){HAL_UART_Transmit(&huart1, (uint8_t*)txMsg, sprintf((char*)txMsg, "%.1f ", filteredValue[i]), 100);}

			aiRun(in_data,out_data);
			float sqSum= out_data[2]*out_data[2] + out_data[3]*out_data[3];

		if (isBelowMinusTwo>0) {
		    uint32_t timestamp = HAL_GetTick();
				out_data[0] = (out_data[0] + 1) * (Fminmax[1] - Fminmax[0]) / 2 + Fminmax[0];
				out_data[1] = (out_data[1] + 1) * (Zminmax[1] - Zminmax[0]) / 2 + Zminmax[0];
				if(out_data[1] >=144){out_data[1]=144;}
				if(out_data[1] <=16){out_data[1]=16;}
				if(out_data[0]>=Fminmax[0]+0.5){
					for(int k=0; k<4;k++){
						HAL_UART_Transmit(&huart1, (uint8_t*)txMsg, sprintf((char*)txMsg, "%.2f ", out_data[k]), 1000);
					}
					HAL_UART_Transmit(&huart1, (uint8_t*)txMsg, sprintf((char*)txMsg, "%.2f ", sqSum), 1000);
				    HAL_UART_Transmit(&huart1, (uint8_t*)txMsg, sprintf((char*)txMsg, "%lu ", timestamp), 1000);
				    //HAL_UART_Transmit(&huart1, (uint8_t*)txMsg, sprintf((char*)txMsg, "1"), 1000);
				}
		}

		}
		do{
			endTime = HAL_GetTick();
			diffTime = endTime - startTime;
		}while (diffTime <= TIMBUDGET);
		HAL_UART_Transmit(&huart1, (uint8_t*)txMsg, sprintf((char*)txMsg, "\n"), 100);
		//HAL_UART_Transmit(&huart1, (uint8_t*)txMsg, sprintf((char*)txMsg, "%d\r\n",isBelowMinusTwo), 100);
    }
}

void PointingVertical(){

	SetI2CCommand();
	SensorI2CCommand();
	ResetAllDevices();
	setOnAllDevices();


	for(int i = 0; i < 5; i++) {

	    uint32_t ServoStartTime = HAL_GetTick(); // 시작 시간 기록
	        servo_angle(&htim2, TIM_CHANNEL_1, 10);
	        HAL_Delay(1000);
		    while(HAL_GetTick() - ServoStartTime < 7000) {
	        uint32_t startTime, endTime, diffTime;
	        uint8_t tofCount =0;
			startTime = HAL_GetTick();
			for (int i = 0; i < NUM_SENSOR; i++) {
				Dev = &vl53l0x_s[i];
				VL53L0X_PerformContinuousRangingMeasurement(Dev, &RangingData); // 1500 uss
				if (RangingData.RangeStatus == 0) {
				  if (RangingData.RangeMilliMeter < sensorAverages[i]+20) {
					filteredValue[i] = Kalman_Estimate(&filters[i], RangingData.RangeMilliMeter); // 500 us
					filteredValue[i] -= sensorAverages[i];
					//filteredValue[i] -= Xmean[i];
					filteredValue[i] /= Xstd[i];
					tofCount++;
				  }
				}
			}

			in_data[0] = filteredValue[0];
			in_data[1] = filteredValue[1];
			in_data[2] = filteredValue[2];
			in_data[3] = filteredValue[3];
			in_data[4] = filteredValue[4];
			in_data[5] = filteredValue[5];
			in_data[6] = filteredValue[6];
			in_data[7] = filteredValue[7];
			in_data[8] = filteredValue[8];
			in_data[9] = filteredValue[9];
			in_data[10] = filteredValue[10];
			in_data[11] = filteredValue[11];
			in_data[12] = filteredValue[0];

			in_data[13] = filteredValue[12];
			in_data[14] = filteredValue[13];
			in_data[15] = filteredValue[14];
			in_data[16] = filteredValue[15];
			in_data[17] = filteredValue[16];
			in_data[18] = filteredValue[17];
			in_data[19] = filteredValue[18];
			in_data[20] = filteredValue[19];
			in_data[21] = filteredValue[20];
			in_data[22] = filteredValue[21];
			in_data[23] = filteredValue[22];
			in_data[24] = filteredValue[23];
			in_data[25] = filteredValue[12];
			#if NUM_SENSOR >= 36
			in_data[26] = filteredValue[24];
			in_data[27] = filteredValue[25];
			in_data[28] = filteredValue[26];
			in_data[29] = filteredValue[27];
			in_data[30] = filteredValue[28];
			in_data[31] = filteredValue[29];
			in_data[32] = filteredValue[30];
			in_data[33] = filteredValue[31];
			in_data[34] = filteredValue[32];
			in_data[35] = filteredValue[33];
			in_data[36] = filteredValue[34];
			in_data[37] = filteredValue[35];
			in_data[38] = filteredValue[24];
			#endif
			#if NUM_SENSOR >= 48
			in_data[39] = filteredValue[36];
			in_data[40] = filteredValue[37];
			in_data[41] = filteredValue[38];
			in_data[42] = filteredValue[39];
			in_data[43] = filteredValue[40];
			in_data[44] = filteredValue[41];
			in_data[45] = filteredValue[42];
			in_data[46] = filteredValue[43];
			in_data[47] = filteredValue[44];
			in_data[48] = filteredValue[45];
			in_data[49] = filteredValue[46];
			in_data[50] = filteredValue[47];
			in_data[51] = filteredValue[36];
			#endif

			if(tofCount == NUM_SENSOR){
				for(int i=0; i<NUM_SENSOR;i++){HAL_UART_Transmit(&huart1, (uint8_t*)txMsg, sprintf((char*)txMsg, "%.1f ", filteredValue[i]), 100);}
				int a =0;
				aiRun(in_data,out_data);
				float sqSum= out_data[2]*out_data[2] + out_data[3]*out_data[3];
				//float sqrange = 0.08;
				uint32_t timestamp = HAL_GetTick();
				if(sqSum>=0.97){
					out_data[0] = (out_data[0] + 1) * (Fminmax[1] - Fminmax[0]) / 2 + Fminmax[0];
					out_data[1] = (out_data[1] + 1) * (Zminmax[1] - Zminmax[0]) / 2 + Zminmax[0];
					if(out_data[1] >=144){out_data[1]=144;}
					if(out_data[1] <=16){out_data[1]=16;}
					if(out_data[0]>=Fminmax[0]){
						for(int k=0; k<4;k++){
							HAL_UART_Transmit(&huart1, (uint8_t*)txMsg, sprintf((char*)txMsg, "%.2f ", out_data[k]), 1000);
						}
						HAL_UART_Transmit(&huart1, (uint8_t*)txMsg, sprintf((char*)txMsg, "%.2f ", sqSum), 1000);
						HAL_UART_Transmit(&huart1, (uint8_t*)txMsg, sprintf((char*)txMsg, "%lu ", timestamp), 1000);
						//HAL_UART_Transmit(&huart1, (uint8_t*)txMsg, sprintf((char*)txMsg, "1"), 1000);
					}
				}else if(a==1){
					for(int k=0; k<4;k++){
						HAL_UART_Transmit(&huart1, (uint8_t*)txMsg, sprintf((char*)txMsg, "%.2f ", out_data[k]), 1000);
					}
					HAL_UART_Transmit(&huart1, (uint8_t*)txMsg, sprintf((char*)txMsg, "%.2f ", sqSum), 1000);
					HAL_UART_Transmit(&huart1, (uint8_t*)txMsg, sprintf((char*)txMsg, "%lu ", timestamp), 1000);
					HAL_UART_Transmit(&huart1, (uint8_t*)txMsg, sprintf((char*)txMsg, "0"), 1000);
				}
			}
			do{
				endTime = HAL_GetTick();
				diffTime = endTime - startTime;
			}while (diffTime <= TIMBUDGET);
			HAL_UART_Transmit(&huart1, (uint8_t*)txMsg, sprintf((char*)txMsg, "\n"), 100);
	    }
	    HAL_Delay(1000);

		servo_angle(&htim2, TIM_CHANNEL_1, 0);
		HAL_Delay(1000);
	    stepLin(-25);
	}

}

void PointingRadial(){
	for(int i = 0; i < 7; i++) {
		servo_angle(&htim2, TIM_CHANNEL_1, 12); // poking 8
		HAL_Delay(5000);
		servo_angle(&htim2, TIM_CHANNEL_1, 0); // poking 8
	    stepRev(15);
		HAL_Delay(5000);
	}

	// 0 15 30 45 60 75 90
}
void InitializaionCalibrationCommand()
{
	HAL_UART_Transmit(&huart1, (uint8_t*)txMsg, sprintf((char*)txMsg, "InitializationCommand\n\r"), 100);

	ResetAllDevices();
  	for (int i = 0; i < NUM_SENSOR; i++) {
  	    uint8_t q = i / 12;
  	    uint8_t r = i % 12;
  	    uint8_t active_device = q * 2 + (r >= 8 ? 1 : 0);
  	    uint8_t channel = (r >= 8) ? r - 8 : r;

        ResetDevicesExcept(active_device);
        setActiveTcaChannel(active_device,channel);

  		Dev = &vl53l0x_s[i];
  		Dev->I2cHandle = &hi2c1;
  		Dev->I2cDevAddr = VL53L0X_ADDR;

  		VL53L0X_WaitDeviceBooted( Dev );
  		VL53L0X_DataInit( Dev );
  		VL53L0X_StaticInit( Dev );
  		VL53L0X_SetDeviceMode(Dev, VL53L0X_DEVICEMODE_CONTINUOUS_RANGING);

  		VL53L0X_PerformRefSpadManagement( Dev, &refSpadCount[i], &isApertureSpads[i]);
  		VL53L0X_PerformRefCalibration( Dev, &VhvSettings[i], &PhaseCal[i]);

  		refSpadCountHost[i] = refSpadCount[i];
  		isApertureSpadsHost[i] = isApertureSpads[i];
  		VhvSettingsHost[i] = VhvSettings[i];
  		PhaseCalHost[i] = PhaseCal[i];

  		VL53L0X_SetLimitCheckEnable( Dev, VL53L0X_CHECKENABLE_SIGMA_FINAL_RANGE, 1);
  		VL53L0X_SetLimitCheckEnable( Dev, VL53L0X_CHECKENABLE_SIGNAL_RATE_FINAL_RANGE, 1);
  		VL53L0X_SetLimitCheckValue( Dev, VL53L0X_CHECKENABLE_SIGNAL_RATE_FINAL_RANGE, (FixPoint1616_t)(0.1*65536));
  		VL53L0X_SetLimitCheckValue( Dev, VL53L0X_CHECKENABLE_SIGMA_FINAL_RANGE, (FixPoint1616_t)(60*65536));
  		VL53L0X_SetMeasurementTimingBudgetMicroSeconds( Dev, 100000);
  		VL53L0X_SetVcselPulsePeriod( Dev, VL53L0X_VCSEL_PERIOD_PRE_RANGE, 18);
  		VL53L0X_SetVcselPulsePeriod( Dev, VL53L0X_VCSEL_PERIOD_FINAL_RANGE, 14);

		Kalman_Init(&filters[i], Q, R, P, 0);  // Q, R, P

 		HAL_UART_Transmit(&huart1, (uint8_t*)txMsg, sprintf((char*)txMsg, "%02d ",i), 100);
 		if(i%12 ==11){HAL_UART_Transmit(&huart1, (uint8_t*)txMsg, sprintf((char*)txMsg, "\n\r"), 100);}
  	}


	HAL_UART_Transmit(&huart1, (uint8_t*)txMsg, sprintf((char*)txMsg, "uint32_t refSpadCountHost[NUM_SENSOR]={"), 100);
	for (int i = 0; i < NUM_SENSOR; i++){
		if(i < NUM_SENSOR - 1){
			HAL_UART_Transmit(&huart1, (uint8_t*)txMsg, sprintf((char*)txMsg, "%lu,",refSpadCount[i]), 100);
		} else {
			HAL_UART_Transmit(&huart1, (uint8_t*)txMsg, sprintf((char*)txMsg, "%lu};\n",refSpadCount[i]), 100);
		}
	}

	HAL_UART_Transmit(&huart1, (uint8_t*)txMsg, sprintf((char*)txMsg, "uint8_t isApertureSpadsHost[NUM_SENSOR]={"), 100);
	for (int i = 0; i < NUM_SENSOR; i++){
		if(i < NUM_SENSOR - 1){
			HAL_UART_Transmit(&huart1, (uint8_t*)txMsg, sprintf((char*)txMsg, "%d,",isApertureSpads[i]), 100);
		} else {
			HAL_UART_Transmit(&huart1, (uint8_t*)txMsg, sprintf((char*)txMsg, "%d};\n",isApertureSpads[i]), 100);
		}
	}

	HAL_UART_Transmit(&huart1, (uint8_t*)txMsg, sprintf((char*)txMsg, "uint8_t VhvSettingsHost[NUM_SENSOR]={"), 100);
	for (int i = 0; i < NUM_SENSOR; i++){
		if(i < NUM_SENSOR - 1){
			HAL_UART_Transmit(&huart1, (uint8_t*)txMsg, sprintf((char*)txMsg, "%d,",VhvSettings[i]), 100);
		} else {
			HAL_UART_Transmit(&huart1, (uint8_t*)txMsg, sprintf((char*)txMsg, "%d};\n",VhvSettings[i]), 100);
		}
	}

	HAL_UART_Transmit(&huart1, (uint8_t*)txMsg, sprintf((char*)txMsg, "uint8_t PhaseCalHost[NUM_SENSOR]={"), 100);
	for (int i = 0; i < NUM_SENSOR; i++){
		if(i < NUM_SENSOR - 1){
			HAL_UART_Transmit(&huart1, (uint8_t*)txMsg, sprintf((char*)txMsg, "%d,",PhaseCal[i]), 100);
		} else {
			HAL_UART_Transmit(&huart1, (uint8_t*)txMsg, sprintf((char*)txMsg, "%d};\n",PhaseCal[i]), 100);
		}
	}
}

void AutoI2CCommand(){

    HAL_UART_Transmit(&huart1, (uint8_t*)txMsg, sprintf((char*)txMsg, "Auto Command \r\n"), 100);

    SetI2CCommand();
    SensorI2CCommand();
    ResetAllDevices();
    setOnAllDevices();

    //float forceSensorZeroPoint = 0.0f;
    uint32_t startTime = 0, endTime = 0;
    uint8_t diffTime = 0;

    setServoAngle(&htim2, TIM_CHANNEL_1, 0); // 초기 ?��?�� ?���?? ?��?��

    for(int lin = 2; lin < 19; lin++){
        for(int rev = 0; rev < 72; rev++){
            for(int r = 30; r <80; r+=10){
            	setServoAngle(&htim2, TIM_CHANNEL_1, r); // ?��?�� ?��?��
                HAL_Delay((r-20)*6+100);
                int tofHitCount = 0;
                while(tofHitCount < 20){
                    uint8_t tofcount = 0;
					/*if(lin ==2 && rev ==0 && r == 30){
						forceSensorZeroPoint = Read_HX711();
						Hx711Data = 0;

					}else{
						Hx711Data = Read_HX711() - forceSensorZeroPoint;
					}*/
                    Hx711Data = Read_HX711();



   					startTime = HAL_GetTick();
   					for (int i = 0; i < NUM_SENSOR; i++) {
   						Dev = &vl53l0x_s[i];
   						VL53L0X_PerformContinuousRangingMeasurement(Dev, &RangingData); // 1500us
   						if (RangingData.RangeStatus == 0) {
   						  if (RangingData.RangeMilliMeter < 100) {
   							  filteredValue[i] = Kalman_Estimate(&filters[i], RangingData.RangeMilliMeter);
   							  filteredValue[i] -= sensorAverages[i];
   							  //filteredValue /= Xstd[i];
   							  tofcount++;
   						  }
   						}
   						if(tofcount==NUM_SENSOR){
   							for(int i = 0; i< NUM_SENSOR;i++){
   							  HAL_UART_Transmit(&huart1, (uint8_t*)txMsg, sprintf((char*)txMsg, "%.1f ", filteredValue[i]), 100);
   							}
   	                        tofHitCount++;
   						}
   					}
   					do {
   					endTime = HAL_GetTick();
   					diffTime = endTime - startTime;
   					} while (diffTime <= TIMBUDGET);

   					startTime = 0;
   					endTime = 0;
   					diffTime = 0;

   					//UART_SendWeight_N(Hx711Data,-1/1600.00f,0); // Send the weight data over UART
   					UART_SendWeight_N(Hx711Data,-1/1600.00f,97.4220); // Send the weight data over UART

   					HAL_UART_Transmit(&huart1, (uint8_t*)txMsg, sprintf((char*)txMsg, " %d %d %d\n", 8*lin, 5*rev, r), 100);

                    if (tofHitCount >= 20) {
                        break;
                    }
                }
                setServoAngle(&htim2, TIM_CHANNEL_1, 20); // ?��?�� ?��치로 ?��?���??
                HAL_Delay((r-20)*6+100);

            }

            stepRev(5); // ?�� 바�?? ?��?��
        }
        HAL_Delay(200);
        stepRev(-360); // ?��?���??
        stepLin(8); // ?��?�� ?��?��
    }
    //stepLin(144); // 마�?�?? ?��치로 ?��?��
}


void LoadcellCommand(){

    uint32_t startTime = 0, endTime = 0;
    uint8_t diffTime = 0;
    float LoadcellData=0;

	startTime = HAL_GetTick();
	do {
		LoadcellData = Read_HX711();
		UART_SendWeight_N(LoadcellData,-1/1600.00f,97.4220);
		HAL_UART_Transmit(&huart1, (uint8_t*)txMsg, sprintf((char*)txMsg, "\n"), 100);

		endTime = HAL_GetTick();
		diffTime = endTime - startTime;
	} while (diffTime <= 4000);


}

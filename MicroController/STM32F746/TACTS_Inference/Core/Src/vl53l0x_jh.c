/*
 * vl53l0x_jh.c
 *
 *  Created on: Oct 24, 2023
 *      Author: JH_LAB
 */


#include "vl53l0x_jh.h"
#include "vl53l0x_api.h"
#include "kalman.h"
#include "usart.h"

#define preset

VL53L0X_RangingMeasurementData_t RangingData;

uint32_t refSpadCount[NUM_SENSOR] = {0};
uint8_t isApertureSpads[NUM_SENSOR] = {0};
uint8_t VhvSettings[NUM_SENSOR] = {0};
uint8_t PhaseCal[NUM_SENSOR] = {0};

#ifdef preset
	#if  NUM_SENSOR == 12
	uint32_t refSpadCountHost[NUM_SENSOR]={6,4,11,6,5,4,4,5,4,6,4,3};
	uint8_t isApertureSpadsHost[NUM_SENSOR]={0,0,1,0,0,0,0,0,0,0,0,0};
	uint8_t VhvSettingsHost[NUM_SENSOR]={32,26,27,32,25,28,36,26,31,34,30,30};
	uint8_t PhaseCalHost[NUM_SENSOR]={1,1,1,1,1,1,1,1,1,1,1,1};
	#elif  NUM_SENSOR == 24
	uint32_t refSpadCountHost[NUM_SENSOR]={6,4,11,6,5,4,4,5,4,6,4,3,5,4,4,5,6,4,5,4,4,4,5,6};
	uint8_t isApertureSpadsHost[NUM_SENSOR]={0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	uint8_t VhvSettingsHost[NUM_SENSOR]={32,26,27,32,25,28,36,26,31,34,30,30,28,28,32,32,33,29,32,32,26,29,30,25};
	uint8_t PhaseCalHost[NUM_SENSOR]={1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
	#elif NUM_SENSOR == 36
	uint32_t refSpadCountHost[NUM_SENSOR]={4,5,4,5,5,5,4,4,9,5,5,6,5,5,4,4,4,5,4,5,5,3,4,6,5,4,4,5,5,5,5,5,5,5,4,5};
	uint8_t isApertureSpadsHost[NUM_SENSOR]={0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	uint8_t VhvSettingsHost[NUM_SENSOR]={25,27,28,24,29,30,27,34,29,29,25,27,32,31,31,29,30,26,27,32,33,31,29,28,32,27,31,32,32,31,33,31,29,31,29,33};
	uint8_t PhaseCalHost[NUM_SENSOR]={1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
	#elif NUM_SENSOR == 48
	uint32_t refSpadCountHost[NUM_SENSOR]={4,4,4,5,4,4,5,4,4,4,4,5,4,5,3,3,4,3,4,4,5,4,4,4,4,5,4,4,4,5,5,4,4,5,5,4,4,3,5,4,5,5,4,4,4,5,4,4};
	uint8_t isApertureSpadsHost[NUM_SENSOR]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	uint8_t VhvSettingsHost[NUM_SENSOR]={28,28,30,30,25,30,27,25,27,30,25,28,33,26,27,26,28,29,26,27,33,29,28,32,32,27,30,30,25,28,31,29,26,26,32,30,30,25,27,25,25,29,30,25,26,29,27,28};
	uint8_t PhaseCalHost[NUM_SENSOR]={1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
	#endif
#else
uint32_t refSpadCountHost[NUM_SENSOR] = {0};
uint8_t isApertureSpadsHost[NUM_SENSOR] = {0};
uint8_t VhvSettingsHost[NUM_SENSOR] = {0};
uint8_t PhaseCalHost[NUM_SENSOR] = {0};
#endif



VL53L0X_Dev_t vl53l0x_s[NUM_SENSOR];
VL53L0X_DEV Dev;

uint8_t tca_ch[8] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80}; // control register of TCA9548A
uint8_t tca_ch_reset = 0x00;
uint8_t tca_ch_all_on = 0xFF;


#if NUM_SENSOR <= 12
	uint8_t tca_addr[2] = {0x70,0x71};
#elif NUM_SENSOR <= 24
	uint8_t tca_addr[4] = {0x70, 0x71, 0x72, 0x73};
	uint8_t tcaLength = 4;
	float Xmean[24] = { 42.84, 43.38, 49.69, 44.07, 48.22, 60.49, 55.37, 46.97, 58.66, 54.8, 53.67, 49.57, 45.03, 47.63, 48.58, 43.53, 50.25, 48.23, 44.56, 52.52, 51.1, 52.06, 51.06, 42.76 };
	float Xstd[24] = { 1.71, 2.27, 1.63, 2.01, 1.88, 2.9, 2.39, 2.32, 2.05, 1.75, 2.14, 1.73, 1.91, 1.71, 1.54, 1.49, 1.46, 3.19, 2.64, 3.22, 2.65, 2.06, 1.96, 2.08 };
	float Fminmax[2] = { 0.0, 93.61 };
	float Zminmax[2] = { 2.0, 154.0 };
#elif NUM_SENSOR <= 36
	uint8_t tca_addr[6] = {0x70, 0x71, 0x72, 0x73, 0x74, 0x75};
	uint8_t tcaLength = 6;
	float Xmean[36] = {3.07, -0.56, 3.38, -0.68, 0.1, -0.1, 0.97, 1.38, 0.03, 2.01, -0.64, 2.23, 0.87, 1.84, 5.23, 1.32, 3.97, 1.29, -1.75, 2.85, 2.34, 4.38, 3.65, 3.5, 0.34, -0.17, -0.01, 0.12, -0.59, 0.39, 0.54, 1.11, -0.07, 0.34, 1.68, 1.76};
	float Xstd[36] = {1.74, 1.46, 1.61, 1.25, 1.41, 1.36, 1.53, 1.72, 1.47, 1.39, 1.32, 1.48, 2.32, 3.33, 2.99, 2.11, 2.21, 2.32, 1.79, 2.04, 2.16, 1.89, 1.75, 1.75, 1.54, 1.48, 1.54, 1.58, 1.46, 1.56, 1.49, 1.54, 1.51, 1.39, 1.15, 1.56};
	float Fminmax[2]={0.0, 2.74};
	float Zminmax[2]={16, 144};
#elif NUM_SENSOR <= 48
	uint8_t tca_addr[8] = {0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77};
	uint8_t tcaLength = 8;
	float Xmean[48] = {1.3, -0.4, -3.81, 0.88, 1.01, -1.54, 0.46, 2.92, 0.13, -2.34, -0.31, -0.93, 1.7, 3.48, -0.13, 2.96, 1.61, -0.26, 1.15, 0.37, 1.54, 1.65, 0.22, 0.37, -1.4, 0.5, 1.68, -0.04, 1.61, 0.22, 1.32, -0.31, 0.97, -0.8, 1.54, 0.43, -0.83, 1.97, -2.74, -1.09, -0.91, 0.6, -1.2, 0.97, 1.89, 0.81, -1.43, 1.16};
	float Xstd[48] = {0.7, 0.69, 0.6, 0.61, 0.48, 0.55, 0.52, 0.72, 0.78, 0.78, 0.85, 0.89, 1.84, 1.64, 1.42, 1.16, 1.15, 1.35, 1.33, 1.52, 1.83, 2.01, 1.99, 2.02, 1.8, 1.64, 1.28, 1.11, 1.2, 1.24, 1.48, 1.63, 2.03, 2.14, 2.25, 2.09, 0.94, 0.69, 0.56, 0.64, 0.63, 0.56, 0.67, 0.66, 0.95, 0.93, 0.77, 0.99};
	float Fminmax[2]={1.74, 4.34};
	float Zminmax[2]={16, 136};
#endif


#if 0
void resetTcaDevicesExcept(uint8_t active_device, const uint8_t *tca_addr) {
    for (int j = 0; j < sizeof(tca_addr); ++j) {
        if (j != active_device) {
            HAL_I2C_Master_Transmit(&hi2c1, tca_addr[j] << 1, &tca_ch_reset, 1, 1000);
        }
    }
}

void setActiveTcaChannel(uint8_t active_device, uint8_t channel, const uint8_t *tca_addr) {
    HAL_I2C_Master_Transmit(&hi2c1, tca_addr[active_device] << 1, &tca_ch[channel], 1, 1000);
}

void initializeVl53l0x(VL53L0X_Dev_t *Dev) {
	Dev->I2cHandle = &hi2c1;
	Dev->I2cDevAddr = VL53L0X_ADDR;

	VL53L0X_WaitDeviceBooted( Dev );
	VL53L0X_DataInit( Dev );
	VL53L0X_StaticInit( Dev );
	VL53L0X_SetDeviceMode(Dev, VL53L0X_DEVICEMODE_CONTINUOUS_RANGING);
	VL53L0X_PerformRefCalibration( Dev, &VhvSettings, &PhaseCal);
	VL53L0X_PerformRefSpadManagement( Dev, &refSpadCount, &isApertureSpads);
	VL53L0X_SetLimitCheckEnable( Dev, VL53L0X_CHECKENABLE_SIGMA_FINAL_RANGE, 1);
	VL53L0X_SetLimitCheckEnable( Dev, VL53L0X_CHECKENABLE_SIGNAL_RATE_FINAL_RANGE, 1);
	VL53L0X_SetLimitCheckValue( Dev, VL53L0X_CHECKENABLE_SIGNAL_RATE_FINAL_RANGE, (FixPoint1616_t)(0.1*65536));
	VL53L0X_SetLimitCheckValue( Dev, VL53L0X_CHECKENABLE_SIGMA_FINAL_RANGE, (FixPoint1616_t)(60*65536));
	VL53L0X_SetMeasurementTimingBudgetMicroSeconds( Dev, 33000);
	VL53L0X_SetVcselPulsePeriod( Dev, VL53L0X_VCSEL_PERIOD_PRE_RANGE, 18);
	VL53L0X_SetVcselPulsePeriod( Dev, VL53L0X_VCSEL_PERIOD_FINAL_RANGE, 14);
}

void initializeAllSensors(uint8_t *tca_addr, VL53L0X_Dev_t *vl53l0x_s, KalmanFilter *filters) {
    for (int j = 0; j < sizeof(tca_addr)/sizeof(tca_addr[0]); ++j) {
        HAL_I2C_Master_Transmit(&hi2c1, tca_addr[j] << 1, &tca_ch_reset, 1, 1000);
    }

    for (int i = 0; i < NUM_SENSOR; i++) {
        uint8_t q = i / 12;
        uint8_t r = i % 12;
        uint8_t active_device = q * 2 + (r >= 8 ? 1 : 0);
        uint8_t channel = (r >= 8) ? r - 8 : r;

        resetTcaDevicesExcept(active_device, tca_addr);
        setActiveTcaChannel(active_device, channel, tca_addr);

        initializeVl53l0x(&vl53l0x_s[i]);
        Kalman_Init(&filters[i], Q, R, P, 0);  // Q, R, P, 초기값

        HAL_UART_Transmit(&huart1, (uint8_t*)txMsg, sprintf((char*)txMsg, "%d complete \n\r", i), 100);
    }
}

void excuteVl53l0x(VL53L0X_Dev_t *Dev,int i) {
    VL53L0X_PerformContinuousRangingMeasurement(Dev, &RangingData); // 1500us
    if (RangingData.RangeStatus == 0) {
        float filteredValue = Kalman_Estimate(&filters[i], RangingData.RangeMilliMeter);
        HAL_UART_Transmit(&huart1, (uint8_t*)txMsg, sprintf((char*)txMsg, "%.2f ", filteredValue), 100);
    }else{
        HAL_UART_Transmit(&huart1, (uint8_t*)txMsg, sprintf((char*)txMsg, "999 "), 100);
    }
}
#endif


void ResetAllDevices() {
  for (int j = 0; j < tcaLength; ++j) {
	  HAL_I2C_Master_Transmit(&hi2c1, tca_addr[j] << 1, &tca_ch_reset, 1, 1000);
  }
}

void ResetDevicesExcept(uint8_t active_device) {
    for (int j = 0; j < tcaLength; ++j) {
        if (j != active_device) {
            HAL_I2C_Master_Transmit(&hi2c1, tca_addr[j] << 1, &tca_ch_reset, 1, 1000);
        }
    }
}

void setActiveTcaChannel(uint8_t active_device, uint8_t channel){
	HAL_I2C_Master_Transmit(&hi2c1, tca_addr[active_device] << 1, &tca_ch[channel], 1, 1000);
}

void setOnAllDevices(){
  for (int j = 0; j < tcaLength; ++j) {
	  HAL_I2C_Master_Transmit(&hi2c1, tca_addr[j] << 1, &tca_ch_all_on, 1, 1000);
  }
}

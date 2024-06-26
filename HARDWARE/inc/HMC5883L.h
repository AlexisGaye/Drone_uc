#ifndef __HMC5883L_H_
#define __HMC5883L_H_

#include "HMC5883LAdress.h"
#include "MPU.h"
#include "Moter.h"
#include "MyI2C.h"
#include "Receiver.h"
#include "Serial.h"
#include "delay.h"
#include "stm32f4xx.h"

#define HMC5883L_ADDRESS_W 0x3C // write adress
#define HMC5883L_ADDRESS_R 0x3D // read adress

typedef struct HMC_Data {
  int16_t GSX;
  int16_t GSY;
  int16_t GSZ;
} HMC_Data;

extern HMC_Data HMC_Data_Structure;

void HMC5883L_WriteReg(uint8_t RegAddress, uint8_t Data);
uint8_t HMC5883L_ReadReg(uint8_t RegAddress);
void HMC5883L_Init(void);
void HMC5883L_GetData(HMC_Data *HMC_Data_Structure);
double HMC5883L_Magangle(HMC_Data HMC_Data_Structure);
void HMC5882L_ReadAllReg(uint8_t RegAddress, int16_t *data, uint8_t count);
#endif

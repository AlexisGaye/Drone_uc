/**
 ******************************************************************************
 * @file    Project/STM32F4xx_StdPeriph_Templates/main.h
 * @author  MCD Application Team
 * @version V1.8.1
 * @date    27-January-2022
 * @brief   Header for main.c module
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2016 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

/* Includes ------------------------------------------------------------------*/
#include "HMC5883L.h"
#include "MPU.h"
#include "Moter.h"
#include "Receiver.h"
#include "SEGGER_SYSVIEW.h"
#include "Serial.h"
#include "delay.h"
#include "os_cpu.h"
#include "stm32f4xx.h"
#include "system_stm32f4xx.h"
#include "ucos_ii.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void TimingDelay_Decrement(void);

#endif /* __MAIN_H */

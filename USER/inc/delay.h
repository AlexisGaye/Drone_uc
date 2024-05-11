#ifndef __DELAY_H
#define __DELAY_H
#include "stdint.h"
#include "stm32f4xx.h"

void Delay_us(uint32_t us);
void Delay_ms(uint32_t ms);
void Delay_s(uint32_t s);
void TimingDelay_Decrement(void);

void SysTick_Init(u8 SYSCLK);
// void delay_ms(u16 nms);
// void delay_us(u32 nus);

#endif

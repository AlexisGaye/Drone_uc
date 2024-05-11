#include "delay.h"
#include "stm32f4xx.h"
#include "ucos_ii.h"

// static u8  fac_us=0; //us延时倍乘数 static u16 fac_ms=0;
// //ms延时倍乘数,在os下,代表每个节拍的ms数

#define delay_ostickspersec OS_TICKS_PER_SEC // OS时钟节拍,即每秒调度次数

void Delay_init() { SysTick->CTRL |= 1 << 16; }

/**
 * @brief  微秒级延时
 * @param  xus 延时时长，范围：0~233015
 * @retval 无
 */
void Delay_us(uint32_t xus) {
  SysTick->LOAD = 84 * xus;   //设置定时器重装值
  SysTick->VAL = 0x00;        //清空当前计数值
  SysTick->CTRL = 0x00000005; //设置时钟源为HCLK，启动定时器
  while (!(SysTick->CTRL & 0x00010000))
    ;                         //等待计数到0
  SysTick->CTRL = 0x00000004; //关闭定时器
}

/**
 * @brief  毫秒级延时
 * @param  xms 延时时长，范围：0~4294967295
 * @retval 无
 */
void Delay_ms(uint32_t xms) {
  while (xms--) {
    Delay_us(1000);
  }
}

/**
 * @brief  秒级延时
 * @param  xs 延时时长，范围：0~4294967295
 * @retval 无
 */
void Delay_s(uint32_t xs) {
  while (xs--) {
    Delay_ms(1000);
  }
}

static __IO uint32_t TimingDelay;

void TimingDelay_Decrement(void) {
  if (TimingDelay != 0x00) {
    TimingDelay--;
  }
}

//初始化延迟函数
//当使用OS的时候,此函数会初始化OS的时钟节拍
// SYSTICK的时钟固定为AHB时钟的1/8
// SYSCLK:系统时钟频率
void SysTick_Init(u8 SYSCLK) {
  u32 reload;
  SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);
  reload = SYSCLK / 8;                  //每秒钟的计数次数 单位为M
  reload *= 1000000 / OS_TICKS_PER_SEC; //根据OS_TICKS_PER_SEC设定溢出时间
                                        // reload为24位寄存器,最大值:16777216
  SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk; //开启SYSTICK中断
  SysTick->LOAD = reload; //每1/OS_TICKS_PER_SEC秒中断一次
  SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk; //开启SYSTICK
}
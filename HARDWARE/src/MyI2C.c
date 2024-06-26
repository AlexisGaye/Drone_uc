#include "delay.h"

// PB8/9
void MyI2C_W_SCL(uint8_t BitValue) {
  if (BitValue == 0) {
    GPIOB->ODR &= ~(1 << 8);
  } else {
    GPIOB->ODR |= 1 << 8;
  }
  Delay_us(10);
}

void MyI2C_W_SDA(uint8_t BitValue) {
  if (BitValue == 0) {
    GPIOB->ODR &= ~(1 << 9);
  } else {
    GPIOB->ODR |= 1 << 9;
  }
  Delay_us(10);
}

uint8_t MyI2C_R_SDA(void) {
  uint8_t BitValue;
  // BitValue = GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_2);
  if (((GPIOB->IDR) & (1 << 9)) != 0) {
    BitValue = 1;
  } else {
    BitValue = 0;
  }
  Delay_us(10);
  return BitValue;
}

void MyI2C_Init(void) {
  RCC->AHB1ENR |= 1 << 1; // GPIOB clock is enable

  GPIOB->MODER &= ~((3 << 16) | (3 << 18));  // return to 00
  GPIOB->MODER |= (1 << 16) | (1 << 18);     // Gen out
  GPIOB->OTYPER |= ((1 << 8) | (1 << 9));    // OD
  GPIOB->OSPEEDR |= ((1 << 17) | (1 << 19)); // High speed
  GPIOB->PUPDR &= ~((3 << 16) | (3 << 18));  // NO pull-up,pull down
  // PB1 and PB2 are set to be OD
  GPIOB->ODR |= 1 << 8;
  GPIOB->ODR |= 1 << 9;
}

void MyI2C_Start(void) {
  MyI2C_W_SDA(1);
  MyI2C_W_SCL(1);
  MyI2C_W_SDA(0);
  MyI2C_W_SCL(0);
}

void MyI2C_Stop(void) {
  MyI2C_W_SDA(0);
  MyI2C_W_SCL(1);
  MyI2C_W_SDA(1);
}

void MyI2C_SendByte(uint8_t Byte) {
  uint8_t i;
  for (i = 0; i < 8; i++) {
    MyI2C_W_SDA(Byte & (0x80 >> i));
    MyI2C_W_SCL(1);
    MyI2C_W_SCL(0);
  }
}

uint8_t MyI2C_ReceiveByte(void) {
  uint8_t i, Byte = 0x00;
  MyI2C_W_SDA(1);
  for (i = 0; i < 8; i++) {
    MyI2C_W_SCL(1);
    if (MyI2C_R_SDA() == 1) {
      Byte |= (0x80 >> i);
    }
    MyI2C_W_SCL(0);
  }
  return Byte;
}

void MyI2C_SendAck(uint8_t AckBit) {
  MyI2C_W_SDA(AckBit);
  MyI2C_W_SCL(1);
  MyI2C_W_SCL(0);
}

uint8_t MyI2C_ReceiveAck(void) {
  uint8_t AckBit;
  MyI2C_W_SDA(1);
  MyI2C_W_SCL(1);
  AckBit = MyI2C_R_SDA();
  MyI2C_W_SCL(0);
  return AckBit;
}

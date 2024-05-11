#include "main.h"

#define TASK_STK_SIZE 512
OS_STK First_Task_Stk[TASK_STK_SIZE], Receiver_Task_Stk[TASK_STK_SIZE],
    Serial_Task_Stk[TASK_STK_SIZE];
#define First_Task_Prio 5
#define Receiver_Task_Prio 7
#define Serial_Task_Prio 6

void First_Task() {
  SysTick_Init(84);
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  MPU6050_Init();
  HMC5883L_Init();
  Serial_Init();
  Receiver_Init();
  PWM_Init();
}
void Receiver_Task() {
  while (1) {
    if (receiver.yes == 1) {
      ChangeAccelrator(motor);
    }
    OSTimeDlyHMSM(0, 0, 0, 1);
  }
}

void Serial_Task() {
  while (1) {
    MPU6050_GetData(&MPU_Data_Structure);
    HMC5883L_GetData(&HMC_Data_Structure);
    Serial_SendArray("REC:", 4);
    Serial_SendNumber(receiver.ch[1], 4);
    Serial_SendByte(' ');
    Serial_SendNumber(receiver.ch[2], 4);
    Serial_SendByte(' ');
    Serial_SendNumber(receiver.ch[3], 4);
    Serial_SendByte('\n');
    Serial_SendArray("MPU:", 4);
    Serial_SendNumber(MPU_Data_Structure.AccX, 4);
    Serial_SendByte(' ');
    Serial_SendNumber(MPU_Data_Structure.AccY, 4);
    Serial_SendByte(' ');
    Serial_SendNumber(MPU_Data_Structure.AccZ, 4);
    Serial_SendByte('\n');
    OSTimeDlyHMSM(0, 0, 0, 5);
  }
}

int main(void) {
  INT8U os_err;

  SystemInit();
  OSInit();
  // function pointer;;argc;;Stack Pointer
  // Priority;;pstk;;Stack size;;TCB pointer
  // task option
  OSTaskCreateExt(&First_Task, (void *)0, &First_Task_Stk[TASK_STK_SIZE - 1],
                  First_Task_Prio, First_Task_Prio, First_Task_Stk,
                  TASK_STK_SIZE, (void *)0,
                  OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR);
  OSTaskNameSet(First_Task_Prio, (INT8U *)"First_Task", &os_err);
  OSStart();

  // OSTaskCreateExt(&Receiver_Task, (void *)0,
  //                 &Receiver_Task_Stk[TASK_STK_SIZE - 1], Receiver_Task_Prio,
  //                 Receiver_Task_Prio, Receiver_Task_Stk, TASK_STK_SIZE,
  //                 (void *)0, OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR);
  // OSTaskNameSet(Receiver_Task_Prio, (INT8U *)"First_Task", &os_err);
  while (1) {
    OSTaskCreateExt(&Serial_Task, (void *)0,
                    &Serial_Task_Stk[TASK_STK_SIZE - 1], Serial_Task_Prio,
                    Serial_Task_Prio, Serial_Task_Stk, TASK_STK_SIZE, (void *)0,
                    OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR);
    OSTaskNameSet(Receiver_Task_Prio, (INT8U *)"First_Task", &os_err);

    OSStart();
  }
  // return 0;
}
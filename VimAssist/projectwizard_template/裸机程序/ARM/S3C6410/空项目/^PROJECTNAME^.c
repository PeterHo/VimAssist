#include "def.h"
#include "gpio.h"

//GPIO
#define GPIO_BASE				(0x7F008000)
//oGPIO_REGS������ gpio.h �ж���
#define GPIO 	                (( volatile oGPIO_REGS *)GPIO_BASE)

//��������
void delay(int times);

/*
 * �������
 * */
int main(void)
{	
}

/*
 * ��ʱ����
 * */
void delay(int times)
{
    int i;
    for(;times>0;times--)
      for(i=0;i<3000;i++);
}

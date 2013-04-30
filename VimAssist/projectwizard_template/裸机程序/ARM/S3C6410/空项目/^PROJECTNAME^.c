#include "def.h"
#include "gpio.h"

//GPIO
#define GPIO_BASE				(0x7F008000)
//oGPIO_REGS类型在 gpio.h 中定义
#define GPIO 	                (( volatile oGPIO_REGS *)GPIO_BASE)

//函数声明
void delay(int times);

/*
 * 程序入口
 * */
int main(void)
{	
}

/*
 * 延时函数
 * */
void delay(int times)
{
    int i;
    for(;times>0;times--)
      for(i=0;i<3000;i++);
}

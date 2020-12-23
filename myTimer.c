#include "myTimer.h"

extern char exti1;

void timer0Init(uint32_t count){
	
 /* 配置Timer32的第一个计数器为32位模式，周期模式，定时器频率=MCLK/定时器分频系数 此处第一个计数器频率=MCLK=4M */
    MAP_Timer32_initModule(TIMER32_0_BASE, TIMER32_PRESCALER_1, TIMER32_32BIT,TIMER32_PERIODIC_MODE);
 
		/* 使能Timer32第一个计数器中断开关*/
    MAP_Interrupt_enableInterrupt(INT_T32_INT1);    
    MAP_Timer32_enableInterrupt(TIMER32_0_BASE);
	
		MAP_Interrupt_enableMaster();/*使能中断总开关*/
    
    MAP_Timer32_setCount(TIMER32_0_BASE,count); /*设置Timer32第一个计数器计数周期，此处 4M/4M=1s*/    
    MAP_Timer32_startTimer(TIMER32_0_BASE, false);/*Timer32第一个计数器以周期性模式开始计数*/
	
}


/* Timer32第一个计数器中断函数*/
void T32_INT1_IRQHandler(void)
{
    MAP_Timer32_clearInterruptFlag(TIMER32_0_BASE); /*清除Timer32第一个计数器中断标志*/  
    //MAP_GPIO_toggleOutputOnPin(GPIO_PORT_P1,GPIO_PIN0); /*翻转P1.0的电平*/
		exti1 = 1;
}


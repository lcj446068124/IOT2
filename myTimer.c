#include "myTimer.h"

extern char exti1;

void timer0Init(uint32_t count){
	
 /* ����Timer32�ĵ�һ��������Ϊ32λģʽ������ģʽ����ʱ��Ƶ��=MCLK/��ʱ����Ƶϵ�� �˴���һ��������Ƶ��=MCLK=4M */
    MAP_Timer32_initModule(TIMER32_0_BASE, TIMER32_PRESCALER_1, TIMER32_32BIT,TIMER32_PERIODIC_MODE);
 
		/* ʹ��Timer32��һ���������жϿ���*/
    MAP_Interrupt_enableInterrupt(INT_T32_INT1);    
    MAP_Timer32_enableInterrupt(TIMER32_0_BASE);
	
		MAP_Interrupt_enableMaster();/*ʹ���ж��ܿ���*/
    
    MAP_Timer32_setCount(TIMER32_0_BASE,count); /*����Timer32��һ���������������ڣ��˴� 4M/4M=1s*/    
    MAP_Timer32_startTimer(TIMER32_0_BASE, false);/*Timer32��һ����������������ģʽ��ʼ����*/
	
}


/* Timer32��һ���������жϺ���*/
void T32_INT1_IRQHandler(void)
{
    MAP_Timer32_clearInterruptFlag(TIMER32_0_BASE); /*���Timer32��һ���������жϱ�־*/  
    //MAP_GPIO_toggleOutputOnPin(GPIO_PORT_P1,GPIO_PIN0); /*��תP1.0�ĵ�ƽ*/
		exti1 = 1;
}


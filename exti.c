#include "exti.h"

char exti1 = 0;


void EXTIX_Init(void)
{
		MAP_GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P1, GPIO_PIN1);  //����P1.1��s1������Ϊ����ģʽ������
    MAP_GPIO_clearInterruptFlag(GPIO_PORT_P1, GPIO_PIN1);               //���P1.1�ж� 
    MAP_GPIO_enableInterrupt(GPIO_PORT_P1, GPIO_PIN1);                  //ʹ��GPIO1.1�ж�
   
		MAP_Interrupt_setPriority(INT_PORT1, 0x20);
    MAP_Interrupt_enableInterrupt(INT_PORT1);                           //ʹ��PORT1�ж�
    
		MAP_Interrupt_enableMaster();  //�����ж��ܿ���  
}

void PORT1_IRQHandler(void)
{
    uint32_t status;
    status = MAP_GPIO_getEnabledInterruptStatus(GPIO_PORT_P1);
    MAP_GPIO_clearInterruptFlag(GPIO_PORT_P1, status);
    //GPIO_setOutputHighOnPin(GPIO_PORT_P2,GPIO_PIN0); //P2.0����ߵ�ƽ��LED2�к����
    if(status & GPIO_PIN1) //�ж�P1.1������S1�����Ƿ�ѹ��
    {      
			exti1 = 1;
    }
}

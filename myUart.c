#include "myUart.h"
void myUartInit(){
//		eUSCI_UART_Config uartConfig =
//		{
//						EUSCI_A_UART_CLOCKSOURCE_SMCLK,          //ѡ��SMCLK��1M��ʱ��Դ
//						6,                                       // BRDIV = 6 ��clockPrescalarʱ�ӷ�Ƶϵ�� 
//						8,                                       // UCxBRF = 8  firstModReg ��BRDIV��UCxBRF�� UCxBRS��SMCLK���������ô��ڲ����ʣ�
//						17,                                      // UCxBRS = 17 secondModReg
//						EUSCI_A_UART_NO_PARITY,                  // У��λNone
//						EUSCI_A_UART_LSB_FIRST,                  // ��λ���ȣ�С��ģʽ
//						EUSCI_A_UART_ONE_STOP_BIT,               // ֹͣλ1λ
//						EUSCI_A_UART_MODE,                       // UART mode
//						EUSCI_A_UART_OVERSAMPLING_BAUDRATE_GENERATION  // ����Ϊ������������ֵΪ1
//		};
	
		eUSCI_UART_Config uartConfig =
		{
						EUSCI_A_UART_CLOCKSOURCE_SMCLK,          //ѡ��SMCLK��1M��ʱ��Դ
						8,                                       // BRDIV = 8 ��clockPrescalarʱ�ӷ�Ƶϵ�� 
						0,                                       // UCxBRF = 0  firstModReg ��BRDIV��UCxBRF�� UCxBRS��SMCLK���������ô��ڲ����ʣ�
						214,                                      // UCxBRS = 214 secondModReg
						EUSCI_A_UART_NO_PARITY,                  // У��λNone
						EUSCI_A_UART_LSB_FIRST,                  // ��λ���ȣ�С��ģʽ
						EUSCI_A_UART_ONE_STOP_BIT,               // ֹͣλ1λ
						EUSCI_A_UART_MODE,                       // UART mode
						EUSCI_A_UART_LOW_FREQUENCY_BAUDRATE_GENERATION 
		};
	
		/* ѡ��P1.2��P1.3ʹ��UARTģʽ */
    MAP_GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P1,GPIO_PIN2 | GPIO_PIN3, GPIO_PRIMARY_MODULE_FUNCTION);
    
    /* ʹ��uartConfig����UART_A0 */
    MAP_UART_initModule(EUSCI_A0_BASE, &uartConfig);

    /* ʹ��UART_A0 */
    MAP_UART_enableModule(EUSCI_A0_BASE);
		
		/* ѡ��P3.2��P3.3ʹ��UARTģʽ */
    MAP_GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P3,GPIO_PIN2 | GPIO_PIN3, GPIO_PRIMARY_MODULE_FUNCTION);
    
    /* ʹ��uartConfig����UART_A2 */
    MAP_UART_initModule(EUSCI_A2_BASE, &uartConfig);

    /* ʹ��UART_A2 */
    MAP_UART_enableModule(EUSCI_A2_BASE);
		
		MAP_UART_enableInterrupt(EUSCI_A2_BASE, EUSCI_A_UART_RECEIVE_INTERRUPT); /*ʹ��UART_A2���ڽ����ж�*/ 
    MAP_Interrupt_enableInterrupt(INT_EUSCIA2); /*ʹ��UART_A2�ж�*/  
    MAP_Interrupt_enableMaster();  /*ʹ���ж��ܿ���*/   
		
		BufferInit(&myBuffer);				//��ʼ��UART_A2���ջ���
}

void myEUSCIA0Init(){
	
	eUSCI_UART_Config uartConfig =
		{
						EUSCI_A_UART_CLOCKSOURCE_SMCLK,          //ѡ��SMCLK��1M��ʱ��Դ
						8,                                       // BRDIV = 8 ��clockPrescalarʱ�ӷ�Ƶϵ�� 
						0,                                       // UCxBRF = 0  firstModReg ��BRDIV��UCxBRF�� UCxBRS��SMCLK���������ô��ڲ����ʣ�
						214,                                      // UCxBRS = 214 secondModReg
						EUSCI_A_UART_NO_PARITY,                  // У��λNone
						EUSCI_A_UART_LSB_FIRST,                  // ��λ���ȣ�С��ģʽ
						EUSCI_A_UART_ONE_STOP_BIT,               // ֹͣλ1λ
						EUSCI_A_UART_MODE,                       // UART mode
						EUSCI_A_UART_LOW_FREQUENCY_BAUDRATE_GENERATION 
		};
	
		/* ѡ��P1.2��P1.3ʹ��UARTģʽ */
    MAP_GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P1,GPIO_PIN2 | GPIO_PIN3, GPIO_PRIMARY_MODULE_FUNCTION);
    
    /* ʹ��uartConfig����UART_A0 */
    MAP_UART_initModule(EUSCI_A0_BASE, &uartConfig);

    /* ʹ��UART_A0 */
    MAP_UART_enableModule(EUSCI_A0_BASE);

}

void Usart_SendByte(uint32_t moduleInstance, uint_fast8_t transmitData){
	UART_transmitData(moduleInstance, transmitData);
}

void Usart_SendString(uint32_t moduleInstance, char* str){
	uint32_t k = 0;
	while (*(str + k)!='\0'){
		Usart_SendByte( moduleInstance, *(str + k) );
		k++;
	}
}
/*UART_A2�жϺ���*/
void EUSCIA2_IRQHandler(void)
{
		uint8_t val;    
    uint32_t status = MAP_UART_getEnabledInterruptStatus(EUSCI_A2_BASE); /*��UART_A2�жϱ�־λ��ֵ��ֵ��status*/
    MAP_UART_clearInterruptFlag(EUSCI_A2_BASE, status);/*���UART_A2�жϱ�־λ*/
    if(status & EUSCI_A_UART_RECEIVE_INTERRUPT_FLAG) /*�ж��Ƿ�ΪUART_A2�����ж�*/
    {      
			
			val = UART_receiveData(EUSCI_A2_BASE);
			EnBuffer(&myBuffer,val);
			
			//UART_transmitData(EUSCI_A0_BASE, val);		
    }   
}

//        sprintf(tmp,"%c",MAP_UART_receiveData(EUSCI_A2_BASE));/*����UART_A0�н��յ��ĵ����ֽ���ʮ�����ƴ�ӡ��tmp��*/
//        /*��tmp�ַ���ͨ��UART_A0����ַ�����*/
//        for (i=0;i<strlen(tmp);i++) 
//            MAP_UART_transmitData(EUSCI_A0_BASE, tmp[i]); 


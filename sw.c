#include "sw.h"



void switchInit(){
	GPIO_setAsInputPin(GPIO_PORT_P5,GPIO_PIN5);//s1
	GPIO_setAsInputPin(GPIO_PORT_P5,GPIO_PIN4);//s2
}

int getS1Statu(){

	int statu = 0;
	statu = GPIO_getInputPinValue(GPIO_PORT_P5,GPIO_PIN5);
	return statu;
}

int getS2Statu(){
	int statu = 0;
	statu = GPIO_getInputPinValue(GPIO_PORT_P5,GPIO_PIN4);
	return statu;
}

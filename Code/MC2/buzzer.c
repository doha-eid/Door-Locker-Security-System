/***********************************************************************************************************
 *Module:Buzzer
 *
 * File Name: buzzer.c
 *
 *  Description:Source file for the buzzer driver
 *
 *      Author: Doha Eid
 **********************************************************************************************************/
#include"buzzer.h"
#include"gpio.h"
/*
 * Description:
 * Function to initialize the buzzer driver
 */
void Buzzer_Init(void)
{
	/*
	 * Setup the buzzer pin as output pin using GPIO driver
	 * Stop the buzzer at the beginning using GPIO driver
	 */
	GPIO_setupPinDirection(BUZZER_PORT_ID,BUZZER_PIN_ID,PIN_OUTPUT);
	GPIO_writePin(BUZZER_PORT_ID,BUZZER_PIN_ID,LOGIC_LOW);
}
/*
 * Description:
 * Function to turn on the buzzer
 */
void Buzzer_ON(void)
{
	/*Write 1 on the buzzer pin to turn off it */
	GPIO_writePin(BUZZER_PORT_ID,BUZZER_PIN_ID,LOGIC_HIGH);
}
/*
 * Description :
 * Function to turn off the buzzer
 */
void Buzzer_OFF(void)
{
	/*Write 0 on the buzzer pin to turn off it */
	GPIO_writePin(BUZZER_PORT_ID,BUZZER_PIN_ID,LOGIC_LOW);
}


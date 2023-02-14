/***********************************************************************************************************
 * Module: Buzzer
 *
 *File Name :buzzer.h
 *
 *  Description:Header file for buzzer driver
 *
 *      Author: Doha Eid
 **********************************************************************************************************/

#ifndef BUZZER_H_
#define BUZZER_H_
#include"std_types.h"

/***********************************************************************************************************
 *                                         Definitions                                                    *
 **********************************************************************************************************/
#define BUZZER_PORT_ID     PORTC_ID
#define BUZZER_PIN_ID      PIN5_ID
/***********************************************************************************************************
 *                                      Function Prototypes                                               *
 **********************************************************************************************************/
/*
 * Description:
 * Function to initialize the buzzer driver
 */
void Buzzer_Init(void);
/*
 * Description:
 * Function to turn on the buzzer
 */
void Buzzer_ON(void);
/*
 * Description :
 * Function to turn off the buzzer
 */
void Buzzer_OFF(void);

#endif /* BUZZER_H_ */

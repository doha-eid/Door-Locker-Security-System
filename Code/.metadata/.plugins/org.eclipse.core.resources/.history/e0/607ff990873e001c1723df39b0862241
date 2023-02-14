/*************************************************************************************************************
 *Module:Timer
 *
 * File Name :timer.h
 *
 *  Description: Header file for timer driver
 *
 *      Author: Doha Eid
 ************************************************************************************************************/

#ifndef TIMER_H_
#define TIMER_H_

#include"std_types.h"

/*************************************************************************************************************
 *                                            Type Deceleration                                             *
 ************************************************************************************************************/
typedef enum
{
	Timer0,Timer1,Timer2
}Timer_Type;
typedef enum
{
	Normal,PWM,CTC,FastPWM
}TIMER_MODE;
typedef enum
{
	No_clock,F_CPU_clock,F_CPU_8,F_CPU_64,F_CPU_256,F_CPU_1024,External_clock
}TIMER_CLOCK;
typedef enum
{
	No_clock2,F_CPU2_clock,F_CPU2_8,F_CPU2_32,F_CPU2_64,F_CPU2_128,F_CPU2_256,F_CPU2_1024
}TIMER2_CLOCK;
typedef struct
{
	Timer_Type Timer_ID;
	TIMER_MODE Mode;
	TIMER_CLOCK Clock_select;
    TIMER2_CLOCK Clock2_select;
	uint8 TCNT;
	uint8 OCR;
}Timer_ConfigType;
/*************************************************************************************************************
 *                                          Function Prototypes                                             *
 ************************************************************************************************************/
/*
 * Description: Function to set the Call Back function address of timer0.
 */
void Timer0_setCallBack(void(*a_ptr)(void));
/*
 * Description: Function to set the Call Back function address of timer1.
 */
void Timer1_setCallBack(void(*b_ptr)(void));
/*
 * Description: Function to set the Call Back function address of timer2.
 */
void Timer2_setCallBack(void(*c_ptr)(void));
/*
 * Description:
 * Function to Enable Timer0 registers to initialize timer0 driver
 * Choose between overflow mode and compare mode
 * setup the clock select
 */
void Timer_Init(const Timer_ConfigType *config_ptr);
/*
 * Description:
 * Function to Disable Timer0
 */
void Timer_DeInit(const Timer_ConfigType *config_ptr);
#endif /* TIMER_H_ */

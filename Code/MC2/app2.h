/***********************************************************************************************************
 * Module: Application2
 *
 * File Name :app2.h
 *
 * Description:Header file for application
 *      Author: Doha Eid
 **********************************************************************************************************/
#include"std_types.h"
#include"timer.h"
#include"uart.h"
#include"DC_Motor.h"
#include"twi.h"
#include"external_eeprom.h"
#include"buzzer.h"
#include"gpio.h"
#include<avr/io.h>
#include<avr/interrupt.h>
#include<util/delay.h>
/***********************************************************************************************************
 *                                        Definitions                                                      *
 ***********************************************************************************************************/
#define NUMBER_OF_OVERFLOWS_PER_SECOND 32
#define M1_READY 0x20
#define M2_READY 0x10
#define ADDRESS 0x01
/***********************************************************************************************************
 *                                       Extern Variables                                                 *
 **********************************************************************************************************/
extern uint8 volatile g_step;
extern uint16 volatile g_tick;
extern uint8 checkPass;
extern uint8 pass1[5];
extern uint8 pass2[5];
extern uint8 i;
extern uint8 symbol;
extern uint8 attempts;
extern uint8 counter;
/**********************************************************************************************************
 *                                      Function Prototypes                                               *
 **********************************************************************************************************/
/*
 * Description:
 * Function that using timer to count
 * it is call back function of timer
 */
void timer_count(void);
void timer(uint8 volatile g_seconds_required) ;
/*
 * Description :
 * Function that  receive the passwords from the MCU1
 */
void recieve_Pass(void);
/*
 * Description :Function checks if the password is matching with the saved in eeprom or not
 */
void pass_with_eeprom();
/*
 * Description:
 * Function to save the password at EEPROM
 */
void save_at_eeprom();
/*
 * Description:
 * Function to receive from MCU1 the main list
 * *.open
 * -.change password
 */
void recieve_Main_List(void);
/*
 * Description:
 * Function that turn on the dc motor
 */
void matched_State(void);
/*
 * Description :
 * Function that when we enter the password 3 times wrong turn on the buzzer for 60 seconds
 */
void wrong_Passwords(void);

/***********************************************************************************************************
 * Module:Application2
 *
 * File Name :app2.c
 *
 * Description:Source file for the application
 *      Author: Doha Eid
 **********************************************************************************************************/
#include"app2.h"
#include"common_macros.h"

/***********************************************************************************************************
 *                                             Global variables                                           *
 **********************************************************************************************************/
/*global variable determine in which step the code is*/
uint8 volatile g_step = 0;
/*global variables for timer*/
uint16 volatile g_tick = 0;
/*Global variable to pass that saved in eeprom*/
uint8 checkPass;
/*The passwords that i received from MCU1 */
uint8 password_saved[5];
uint8 password_recieved[5];
uint8 i;
/*global variable to receive the symbols from keypad*/
uint8 symbol = 0;
/*global variables to check the 3 attempts of the password */
uint8 attempts = 0;
uint8 counter = 0;
/*Global configuration for timer1 */
Timer_ConfigType configure = { Timer0, Normal, F_CPU_1024, No_clock2, 0 };

/***********************************************************************************************************
 *                                           Function Definitions                                          *
 **********************************************************************************************************/
/*
 * Description:
 * Function that using timer to count
 * it is call back function of timer
 */
void timer_count(void) {

	/*increases the global tick each time the timer interrupt*/
	g_tick++;
	/*
	 * check if the timer count second
	 */

}

void timer(uint8 volatile g_seconds_required) {
	Timer_Init(&configure);
	while (g_tick != ((NUMBER_OF_OVERFLOWS_PER_SECOND) * g_seconds_required))
		;
	Timer_DeInit(&configure);
	g_tick = 0;

}
/*
 * Description :
 * Function that  receive the passwords from the MCU1
 */
void recieve_Pass(void) {

	/*Receiving the first password from the MCU1*/
	for (i = 0; i < 5; i++) {
		password_recieved[i] = UART_recieveByte();
	}
}

/*
 * Description :Function checks if the password is matching with the saved in eeprom or not
 */
void pass_with_eeprom() {

	for (i = 0; i < 5; i++) {
		/*read the password from eeprom*/
		EEPROM_readByte(ADDRESS + i, &password_saved[i]);
		if (password_saved[i] != password_recieved[i]) {
			checkPass = 0;
			break;
		}
	}
	if (i == 5) {
		checkPass = 1;
	}

}

/*
 * Description:
 * Function to save the password at EEPROM
 */
void save_at_eeprom() {

	for (i = 0; i < 5; i++) {
		EEPROM_writeByte((ADDRESS + i), password_recieved[i]);
		_delay_ms(10);
	}
}

/*
 * Description:
 * Function to receive from MCU1 the main list
 * *.open
 * -.change password
 */
void recieve_Main_List(void) {
	symbol = UART_recieveByte();
	if (symbol == '*') {
		g_step = 3;
		symbol=0;
	} else if (symbol == '-') {
		g_step = 4;
		symbol=0;
	}
}
/*
 * Description:
 * Function that turn on the dc motor
 */
void matched_State(void) {
	DcMotor_Rotate(Clock_Wise);
	timer(15);
	DcMotor_Rotate(Stop);
	timer(3);
	DcMotor_Rotate(Anti_Clock_Wise);
	timer(15);
	DcMotor_Rotate(Stop);
}

/*
 * Description :
 * Function that when we enter the password 3 times wrong turn on the buzzer for 60 seconds
 */
void wrong_Passwords(void) {
	/*Turn on the buzzer for 60 seconds */
	Buzzer_ON();
	timer(60);
	/*Stop the buzzer and timer  after 60 seconds  */
	Timer_DeInit(&configure);
	Buzzer_OFF();
}

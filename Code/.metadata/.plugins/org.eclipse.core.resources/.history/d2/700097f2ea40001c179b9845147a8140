/***********************************************************************************************************
 * Module :Application
 *
 * File Name :app.c
 *
 * Description:SOurce file for the application
 *
 *      Author: Doha Eid
 **********************************************************************************************************/
#include "app.h"

/***********************************************************************************************************
 *                                       Global Variables                                                  *
 ***********************************************************************************************************/
/*Global variable for edge count function for contain ticks counter of timer */
uint16 volatile g_tick = 0;
/*Global variable to know where the code will be */
uint8 volatile g_step;
/*Global variable to take the pass from the keypad */
uint8 password_send[5];
uint8 password_check[5];
uint8 i;
uint8 do_case;
/*Global variable used in function of options */
uint8 volatile option_key;
/*Global variable for check the passwords to open the door  */
uint8 volatile checker;
uint8 volatile checking_value;
/*Global configuration for timer */
Timer_ConfigType configure = { Timer0, Normal, F_CPU_1024, No_clock2, 0 };

/***********************************************************************************************************
 *                                      Function Definitions                                               *
 **********************************************************************************************************/
/*
 * Description :
 * call back function of timer to count the seconds that we need
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
 * Description:
 * Function that take the password twice from the keypad and display on LCD as *
 */
void Enter_Password(void) {
    /*receive the first password from the keypad and store at array*/
	LCD_displayString("Enter Password");
	LCD_moveCursor(1, 0);
	for (i = 0; i < 5; i++) {
		password_send[i] = KEYPAD_getPressedKey();
		LCD_displayCharacter('*');
		_delay_ms(500);
		/*if we press on ON/C key it clear the pass that entered and would start again from 0*/
		if (password_send[i] == 13) {
			/*clear the screen */
			LCD_clearScreen();
			/*enter the new password */
			LCD_displayString("Enter new password");
			LCD_moveCursor(2, 0);

		}
	}
	/*Enter the second password from the keypad and store at array */
	LCD_clearScreen();
	LCD_displayString("Reenter Password");
	LCD_moveCursor(1, 0);
	for (i = 0; i < 5; i++) {
		password_check[i] = KEYPAD_getPressedKey();
		LCD_displayCharacter('*');
		_delay_ms(500);
		/*if we press on ON/C key it clear the pass that entered and would start again from 0*/
		if (password_check[i] == 13) {
			/*clear the screen */
			LCD_clearScreen();
			/*enter the new password */
			LCD_displayString("Enter new password");
			LCD_moveCursor(2, 0);

		}
	}
/*calling the function to compare between two passwords */
	check_Password();
}
/*
 * Description :
 * Function to compare if the two passwords are matching or not
 */
void check_Password() {
	for (i = 0; i < 5; i++) {
		if (password_send[i] != password_check[i]) {
			checking_value = 0;
		}
	}
		if(i==5){
		checking_value = 1;
	}
}

/*
 * Description:
 * Function to send the password to the MCU2 by uart
 */
void send_Pass_ToMcu2(void) {
	LCD_displayString("Press=to send password");
	if (KEYPAD_getPressedKey() == '=') {
		for (i = 0; i < 5; i++) {
			UART_sendByte(password_send[i]);
		}
	}

}

/*
 * Description:
 * Function to decide open the door or change the password
 * option list from *.open
 * -. change password
 */
void options_list(void) {
	option_key = KEYPAD_getPressedKey();
	/*repeats until the user choose one of two options */
	do {
		option_key = KEYPAD_getPressedKey();
	} while ((option_key != '*') && (option_key != '-'));

	/*sends to MCU2 the option which the user chose*/
	UART_sendByte(option_key);
	LCD_clearScreen();
	LCD_displayCharacter(option_key);
	_delay_ms(500);
	/*decide where we need the code run */
	if (option_key == '*') {
		g_step = 3;
	} else if (option_key == '-') {
		g_step = 4;
	}

}
/*
 * Description :
 * Function that take the password once from the keypad and store at array
 */
void enter_saved_pass(void) {
	for (i = 0; i < 5; i++) {
		password_send[i] = KEYPAD_getPressedKey();
		LCD_displayCharacter('*');
		_delay_ms(500);
		/*if we press on ON/C key it clear the pass that entered and would start again from 0*/
		if (password_send[i] == 13) {
			/*clear the screen */
			LCD_clearScreen();
			/*enter the new password */
			LCD_displayString("Enter new password");
			LCD_moveCursor(2, 0);
			i = 0;
		}
	}

}
/*
 * Description:
 * Function that display the main list of the system
 */
void main_List(void) {
	LCD_clearScreen();
	LCD_moveCursor(0, 0);
	LCD_displayString("*:Open ");
	LCD_moveCursor(1, 0);
	LCD_displayString("-:");
	LCD_moveCursor(1, 1);
	LCD_displayString("Change Password");
	options_list();
}
/*
 * Description :
 * Function that receive if the pass was correct or not and if correct open the door
 */
void check_Pass(uint8 check_password) {
	/*In this case if the password unmatched
	 *so display on the screen unmatched
	 *and receive from the MCU2  the step that will go to
	 */
	if (check_password == 0) {
		LCD_displayString("Unmatched Password ");
		_delay_ms(1000);
		LCD_clearScreen();
		g_step = UART_recieveByte();
		do_case=0;

	}

	/*
	 * In this case if the password is matched
	 * So display on the screen Matched password
	 * and open the door and turn on the DC_motor and rotate clock wise for 15 seconds
	 * and display (The door is opening) while the DC_motor is rotating
	 *
	 */
	else if (check_password == 1) {
		LCD_displayString("Matched Password ");
		_delay_ms(1000);
		LCD_clearScreen();
		do_case=1;
	}
}
/*
 * DEscription :
 * Function that display on the lcd when the door is opening and closing
 */
void matched_State(void) {
	/*display on the lcd message for 15 seconds then clear the screen*/
	LCD_displayString("The door opening");
	timer(15);
	LCD_clearScreen();
	/*display on the lcd message for 3 seconds then clear the screen*/
	LCD_displayString("Door close in 3 secs");
	timer(3);
	LCD_clearScreen();
	/*display on the lcd message for 15 seconds then clear the screen*/
	LCD_displayString("The door closing");
	timer(15);
	LCD_clearScreen();
}
/*
 * Description :
 * Function that when we enter the password 3 times wrong display message on the lcd
 * for the 60 seconds
 * then return to main list
 */
void wrong_Passwords(void) {
	LCD_displayString("There is a thief!");
	timer(60);
	main_List();
}

/***********************************************************************************************************
 * Module :main
 *
 * File Name :main.c
 *
 *Description: source file for the main application
 *      Author: Doha Eid
 ***********************************************************************************************************/

#include "app.h"

int main(void) {

	/*Initialize the LCD */
	LCD_init();
	/* Initialize the UART driver with Baud-rate = 9600 bits/sec */
	UART_Config uart_ptr = { 9600, bit_8, disable, bit_1 };
	UART_init(&uart_ptr);
	/*Initialize timer driver */
	Timer0_setCallBack(timer_count);
	/*open pin of global interrupt the I-bit*/
	SREG |= (1 << 7);
	/*Display on the lcd welcome for 5 seconds and then display the list */
	LCD_displayString("Welcome");
	_delay_ms(500);
	LCD_clearScreen();
	/*Go to step 0*/
	g_step = 0;
	while (1) {
		switch (g_step) {
		/*
		 * At step 0 enter the pass twice to save the the pass in eeprom to open the system
		 *and press on = to send the pass by UART
		 */
		case 0:

			Enter_Password();
			/*checking if the password matched then go to step 1
			 * if unmatched repeat this step again
			 */
			if (checking_value == 1) {
				g_step = 1;
			} else {
				LCD_displayString("Unmatched");
				_delay_ms(1000);
				LCD_clearScreen();
				g_step = 0;
			}
			LCD_clearScreen();

			break;

			/*
			 * this steps displays that the two passwords sent are matched and saved in EEPROM
			 * if matched display matched
			 * and go to case 2
			 */
		case 1:

			LCD_displayString("matched!");
			_delay_ms(500);
			LCD_moveCursor(1, 0);
			send_Pass_ToMcu2();
			LCD_clearScreen();
			LCD_moveCursor(1, 0);
			LCD_displayString("pass saved!");
			_delay_ms(500);
			g_step = 2;
			break;

			/*
			 * This case to decide what the user need
			 * *.open the door
			 * -.change the password
			 */
		case 2:
			main_List();
			break;
			/*
			 * This case we open the system :
			 * enter the saved pass if the pass matched with the eeprom {
			 * open the door and turn on the DC_motor and rotate clock wise  for 15 seconds
			 * and wait 3 seconds and close the door and rotate the DC_motor Anti clock wise for 15 seconds }
			 * if the password unmatched their is 3 attempts to enter the correct and if the user does not
			 * enter the correct one the buzzer will turn on for 60 seconds and
			 */
		case 3:
			LCD_displayString("Enter password");
			LCD_moveCursor(1, 0);
			enter_saved_pass();
			LCD_moveCursor(1, 0);
			send_Pass_ToMcu2();
			LCD_clearScreen();
			checker = UART_recieveByte();
			check_Pass(checker);
			if(do_case)
			matched_State();
			g_step=2;
			break;
			/*
			 * This case change the password by reset the old password and change it
			 */
		case 4:
			LCD_displayString("Enter old password");
			LCD_moveCursor(1, 0);
			/*Enter the old password */
			enter_saved_pass();
			LCD_moveCursor(1, 0);
			/*Then send to MCU2 to compare with that saved in EEprom*/
			send_Pass_ToMcu2();
			LCD_clearScreen();
			/*receive the state from MCU2 in checker
			 * if the checker = 1 so enter the new password twice and save in eeprom
			 * if checker = 0 so return to case 0 to try again to enter the correct old password
			 */
			checker = UART_recieveByte();
			check_Pass(checker);
			if(do_case){
			Enter_Password();
			if (checking_value == 1) {
				g_step = 1;
			} else {
				LCD_displayString("Unmatched");
				_delay_ms(1000);
				LCD_clearScreen();
				g_step = 0;
			}
			LCD_clearScreen();
			}
			break;
			/*
			 * the code will go to this step in step the user entered wrong password for 3 times
			 * and turn on the buzzer for 60 seconds
			 * and display warning message
			 */
		case 5:
			wrong_Passwords();
			g_step=2;
			break;

		}
	}
}


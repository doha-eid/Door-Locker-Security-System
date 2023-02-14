/***********************************************************************************************************
 * Module:Main application
 *
 * File Name :main.c
 *
 *  Description: Main application that executes
 *    4  Author: Doha Eid
 **********************************************************************************************************/
#include"app2.h"

int main(void) {
	/*Initialize the buzzer*/
	Buzzer_Init();
	/*Initialize the DC_Motor*/
	DcMotor_Init();
	/* Initialize the UART driver with Baud-rate = 9600 bits/sec */
	UART_Config uart_ptr = { 9600, bit_8, disable, bit_1 };
	UART_init(&uart_ptr);
	/*Initialize the I2C driver */
	I2C_Configure I2C_config = { value_1, ADDRESS };
	TWI_init(&I2C_config);
	/*Initialize the timer */
	Timer0_setCallBack(timer_count);
	/*Enable global interrupt I-Bit*/
	SREG |= (1 << 7);
	/*Start the code from step = 0*/
	g_step = 0;


	while (1) {

		switch (g_step) {
		/*
		 * Step 0 that the first time you save password in eeprom
		 *there is no password saved in eeprom
		 */
		case 0:
			/*Receive the first try password
			 *And wait 1msec to receive the next password
			 */
			//	UART_sendByte(M2_READY);
			recieve_Pass();
			g_step = 1;
			break;
			/*
			 *At this case we save the new password at eeprom after check if the two passwords matching or not
			 */
		case 1:
			/*Its time to write the password at eeprom */
			save_at_eeprom();
			g_step = 2;
			break;
			/*
			 * At step =2 we receive the main list to decide what to do
			 * *.open door
			 * -.change password
			 */

		case 2:
			recieve_Main_List();
			break;

			/*
			 * At this case there is 3 attempts to enter the pass correct
			 * If the pass not correct the buzzer will turn on
			 */
		case 3:
			/*Receive the pass from MCU1*/
			recieve_Pass();
			/*check if the receive pass matching with the saved one or not */
			pass_with_eeprom();
			/*send the check of passwords */
			UART_sendByte(checkPass);
			/*check if the user try the 3 attempts or not */
			if (checkPass == 0) {
				counter++;
				g_step=3;
				/*the user run out the range (3attempts) so turn on the buzzer  */
				if (counter == 3) {
					counter = 0;
					g_step = 5;
					/*send the step where the code are */
					UART_sendByte(g_step);
					break;
				}
				UART_sendByte(g_step);
				break;
			} else if (checkPass == 1) {
				/*
				 *If the pass is correct then make the counter=0
				 * And turn on the dc_motor to rotate clock wise 15 seconds counted by timer
				 * And wait this step to finish to go to the main list
				 */
				counter = 0;
				matched_State();
				g_step=2;
				break;
			}
			break;

			/*
			 * This case reset the password by entering the old one and change it
			 * There are 3 attempts for entering the old password correct
			 * if the user do not enter the password correct in 3 attempts so it will stop and
			 * the buzzer will turn on 60 seconds counted by timer
			 */
		case 4:
				/*Receive the pass from MCU1*/
				recieve_Pass();
				/*check if the receive pass matching with the saved one or not */
				pass_with_eeprom();
				/*send the check password */
				UART_sendByte(checkPass);
				/*check if the user try the 3 attempts or not */
				if (checkPass == 0) {
					counter++;
					g_step=4;
					/*the user run out the range (3attempts) so turn the buzzer  */
					if (counter == 3) {
						counter = 0;
						g_step = 5;
						UART_sendByte(g_step);
						break;
					}
					/*send the step where the code are */
					UART_sendByte(g_step);
				} else if (checkPass == 1) {
					/*
					 *If the pass is correct then make the counter=0
					 * and then receive the new password from MCU1
					 * and save the new password at eeprom
					 * then return to the main list
					 */
					counter = 0;
					recieve_Pass();
					save_at_eeprom();

				}
			recieve_Main_List();
			break;
			/*
			 * The code will run this case in case the user entered wrong password for 3 times
			 * Turn on the buzzer for 60 seconds counted by timer
			 */
		case 5:
			wrong_Passwords();
			g_step=2;
			break;
		}
	}
}


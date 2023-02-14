/*************************************************************************************************************
 *Module:Timer
 *
 * File Name :timer.c
 *
 *  Description:Source file for timer driver
 *
 *      Author: Doha Eid
 ************************************************************************************************************/
#include<avr/io.h>
#include<avr/interrupt.h>
#include"common_macros.h"
#include"timer.h"
/*************************************************************************************************************
 *                                         Global Variables                                                 *
 ************************************************************************************************************/

/* Global variables to hold the address of the call back function in timer0 */
static volatile void (*g_callBackPtr0)(void) = NULL_PTR;
/* Global variables to hold the address of the call back function in the timer2 */
static volatile void (*g_callBackPtr2)(void) = NULL_PTR;

/************************************************************************************************************
 *                                     Interrupt Service Routines                                          *
 ************************************************************************************************************/
ISR(TIMER0_OVF_vect)
{
	if(g_callBackPtr0 != NULL_PTR)
	{
		/* Call the Call Back function in the app4lication after the edge is detected */
		(*g_callBackPtr0)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}
ISR(TIMER0_COMP_vect)
{
	if(g_callBackPtr0 != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callBackPtr0)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}
ISR(TIMER1_OVF_vect)
{
	if(g_callBackPtr0 != NULL_PTR)
	{
		/* Call the Call Back function in the app4lication after the edge is detected */
		(*g_callBackPtr0)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}
ISR(TIMER1_COMPA_vect)
{
	if(g_callBackPtr0 != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callBackPtr0)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}
ISR(TIMER2_OVF_vect)
{
	if(g_callBackPtr2 != NULL_PTR)
	{
		/* Call the Call Back function in the app4lication after the edge is detected */
		(*g_callBackPtr2)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}
ISR(TIMER2_COMP_vect)
{
	if(g_callBackPtr2 != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callBackPtr2)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}

/*************************************************************************************************************
 *                                         Function Definitions                                           *
 ************************************************************************************************************/
/*
 * Description: Function to set the Call Back function address.
 */
void Timer0_setCallBack(void(*a_ptr)(void))
{
	/* Save the address of the Call back function in a global variable */
	g_callBackPtr0 =a_ptr;
}
/*
 * Description: Function to set the Call Back function address.
 */
void Timer1_setCallBack(void(*b_ptr)(void))
{
	/* Save the address of the Call back function in a global variable */
	g_callBackPtr2 =b_ptr;
}
/*
 * Description: Function to set the Call Back function address.
 */
void Timer2_setCallBack(void(*c_ptr)(void))
{
	/* Save the address of the Call back function in a global variable */
	g_callBackPtr2 =c_ptr;
}
/*
 * Description:
 * Function to Enable Timer0 registers to initialize timer0 driver
 * Choose between overflow mode and compare mode
 * setup the clock select
 */
void Timer_Init(const Timer_ConfigType *config_ptr)
{

switch ((config_ptr->Timer_ID))
{
case Timer0:
if((config_ptr->Mode)==Normal)
	{
	 /*Initialize the Timer */
		TCNT0=config_ptr->TCNT;
	/*
	 * Non-PWM mode FOC0=15
	 * Enable Timer0 Overflow Interrupt
	 */
	SET_BIT(TCCR0,FOC0);
	SET_BIT(TIMSK,TOIE0);
	/*Configure clock select */
	TCCR0=(TCCR0&0XF8)|(config_ptr->Clock_select);

	}
     else if ((config_ptr->Mode)==CTC)
       {
    	 /*Initialize the Timer */
    	  TCNT0=config_ptr->TCNT;
	/*
	 * Non-PWM mode FOC0=1
	 * Enable Timer0 Compare Interrupt
	 * CTC Mode WGM01=1 & WGM00=0
	 */
	SET_BIT(TCCR0,FOC0);
	SET_BIT(TIMSK,OCIE0);
	SET_BIT(TCCR0,WGM01);
	/*Configure clock select */
	TCCR0=(TCCR0 & 0XF8)|(config_ptr->Clock_select);
    /*Setup the Output compare register OCR */
	OCR0=config_ptr->OCR;
    }
     else
    {
	/* Disable Timer0 Overflow Interrupt*/
	CLEAR_BIT(TIMSK,TOIE0);
	/*Disable Timer0 Compare Interrupt*/
	CLEAR_BIT(TIMSK,OCIE0);
       }
   break;
      case Timer1:
   if ((config_ptr->Mode)==Normal)
{
 	  /*Initialize the timer1*/
 		TCNT1=config_ptr->TCNT;
 		/*Non PWM mode */
 		SET_BIT(TCCR1A,FOC1A);
 		SET_BIT(TCCR1A,FOC1B);
 		/*Enable overflow interrupt*/
 		SET_BIT(TIMSK,TOIE1);
 		/*Select the clock*/
 		TCCR1B=(TCCR1B & 0xF8)|(config_ptr->Clock_select);

}
   else if ((config_ptr->Mode)==CTC)
{
 	  /*Initialize the timer1*/
 		TCNT1=config_ptr->TCNT;
	/*Set the compare value */
 		OCR1A=config_ptr->OCR;
 		/* Enable Timer1 Compare A Interrupt */
 		SET_BIT(TIMSK,OCIE1A);
 		/* Configure timer control register TCCR1A
 			 * 1. Disconnect OC1A and OC1B  COM1A1=0 COM1A0=0 COM1B0=0 COM1B1=0
 			 * 2. FOC1A=1 FOC1B=0
 			 * 3. CTC Mode WGM10=0 WGM11=0 (Mode Number 4)
 			 */
 		SET_BIT(TCCR1A,FOC1A);
 		/* Configure timer control register TCCR1B
 			 * 1. CTC Mode WGM12=1 WGM13=0 (Mode Number 4)
 			 */
 		SET_BIT(TCCR1B,WGM12);
 		/*configure the prescaler  */
 		TCCR1B=(TCCR1B & 0xF8)|(config_ptr->Clock_select);
}
   else
   {
	   /* Disable Timer1 Overflow Interrupt*/
	   	CLEAR_BIT(TIMSK,TOIE1);
	   	/*Disable Timer1 Compare Interrupt*/
	   	CLEAR_BIT(TIMSK,OCIE1A);
   }

	break;
      case Timer2:
      if ((config_ptr->Mode)==Normal)
     {
    	  /*Initialize the timer2*/
    		TCNT2=config_ptr->TCNT;
      	/*
      	 * Non-PWM mode FOC2=1
      	 * Enable Timer0 Overflow Interrupt
      	 */
      	SET_BIT(TCCR2,FOC2);
      	SET_BIT(TIMSK,TOIE2);
      	/*Configure clock select */
      	TCCR2=(TCCR2 & 0XF8)|(config_ptr->Clock2_select);
     }
      else if ((config_ptr->Mode)==CTC)
      {
    	  /*Initialize the timer2*/
    	     TCNT2=config_ptr->TCNT;
      	/*
      	 * Non-PWM mode FOC2=1
      	 * Enable Timer2 Compare Interrupt
      	 * CTC Mode WGM21=1 & WGM20=0
      	 */
      	SET_BIT(TCCR2,FOC2);
      	SET_BIT(TIMSK,OCIE2);
      	SET_BIT(TCCR2,WGM21);
      	/*Configure clock select */
      	TCCR2=(TCCR2&0XF8)|(config_ptr->Clock2_select);
          /*Setup the Output compare register OCR */
      	OCR2=config_ptr->OCR;
      }
      else
      {
      	/* Disable Timer2 Overflow Interrupt*/
      	 CLEAR_BIT(TIMSK,TOIE2);
      	/*Disable Timer2 Compare Interrupt*/
      	 CLEAR_BIT(TIMSK,OCIE2);
      }
	}
}



/*
 * Description:
 * Function to Disable Timer0
 */
void Timer_DeInit(const Timer_ConfigType *config_ptr)
{
	/*configure the number of timers*/
		switch((config_ptr->Timer_ID))
		{
		case Timer0:

	/*Clear all timer register*/
	TCCR0=0;
	TCNT0=0;
	/*Disable the interrupt MISK register*/
	CLEAR_BIT(TIMSK,TOIE0);
	CLEAR_BIT(TIMSK,OCIE0);
		break;
       case Timer1 :
	/*Clear all timer register*/
			TCCR1A=0;
			TCNT1=0;
			/*Disable the interrupt MISK register*/
			CLEAR_BIT(TIMSK,TOIE1);
			CLEAR_BIT(TIMSK,OCIE1A);
			break;
        case Timer2 :
		/*Clear all timer register*/
		TCCR2=0;
		TCNT2=0;
		/*Disable the interrupt MISK register*/
		CLEAR_BIT(TIMSK,TOIE2);
		CLEAR_BIT(TIMSK,OCIE2);
		break;

}
}

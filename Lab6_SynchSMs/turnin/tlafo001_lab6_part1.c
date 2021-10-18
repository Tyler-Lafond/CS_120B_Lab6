/*	Author: tlafo001
 *  Partner(s) Name: 
 *	Lab Section: 022
 *	Assignment: Lab # 6  Exercise # 1
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#include "timer.h"
#endif

enum LED_States { LED_SMStart, LED_Change } LED_State;
unsigned char tempB;

void TickLED()
{
	switch(LED_State)
	{
		case LED_SMStart:
			tempB = 0x01;
			LED_State = LED_Change;
			break;
		case LED_Change:
			if (tempB >= 0x04)
			{
				tempB = 0x01;
			}
			else
			{
				tempB = tempB << 1;
			}
			LED_State = LED_Change;
			break;
		default:
			LED_State = LED_SMStart;
			break;
	}

	switch(LED_State)
	{
		case LED_Change:
			PORTB = tempB;
			break;
		default:
			break;
	}
}

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRB = 0xFF; PORTB = 0x00;
	TimerSet(1000);
	TimerOn();
    /* Insert your solution below */
	tempB = 0x00;
    while (1) {
	TickLED();
	while(!TimerFlag);
	TimerFlag = 0;
    }
    return 1;
}

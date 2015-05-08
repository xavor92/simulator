/*
 * pc_interface.c
 *
 *  Created on: 07.05.2015
 *      Author: olli
 */

/*
 *	Includes
 */

#include "pc_interface.h"
#include "uart.h"
#include <avr/interrupt.h>
#include <avr/pgmspace.h>

/*
 *	Defines
 */

#define TCCR0_PRES_64 0x04
#define TCCR0_STOP 0x00
#define ADDRESS 0x4f

/*
 *	Local Functions (Declaration, static)
 */

static PC_Interface_StateTypeDef Status;
static PC_Interface_CommandTypeDef Command;
static unsigned char parameter1;
static unsigned int ms_counter = 0;
/*
 *	Global Functions (Definitions)
 */

void PC_Interface_Receive()
{
	if(Status != State_Receive_Complete)
	{
		unsigned int c = uart_getc();
		if( ! ( c & UART_NO_DATA) )
		{
			uart_putc( c );
			switch (Status) {
				case State_Reset:
					if( c == START_SYMBOL)
						Status = State_Start0;
						ms_counter = 0;
						TCNT2 = 5;
						TCCR2 = TCCR0_PRES_64;
					break;
				case State_Start0:
					if( c == START_SYMBOL)
						Status = State_Start1;
					break;
				case State_Start1:
					if( c == START_SYMBOL)
						Status = State_StartComplete;
					break;
				case State_StartComplete:
					if( c == Command_Who)
					{
						Status = State_Receive_Complete;
						Command = Command_Who;
					} else if (c == Command_CaseInUSe)
					{
						Status = State_CommandReceived;
						Command = Command_CaseInUSe;
					} else if (c == Command_Unlock)
					{
						Status = State_CommandReceived;
						Command = Command_Unlock;
					} else if (c == Command_Locked)
					{
						Status = State_CommandReceived;
						Command = Command_Locked;
					}
					break;
				case State_CommandReceived:
					parameter1 = c;
					Status = State_Receive_Complete;
					TCCR2 = TCCR0_STOP;
					ms_counter = 0;
					break;
				default:
					break;
			}
			//uart_putc(Status);
			//uart_putc(ms_counter >> 8);
			//uart_putc(ms_counter & 0xFF);
		}
	}
}

extern void PC_Interface_CheckTimeout()
{
	if(ms_counter > TIMEOUT)
	{
		if(Status != State_Reset)
		{
			if(Status != State_Receive_Complete)
			{
				TCCR2 = TCCR0_STOP;
				ms_counter = 0;
				Status = State_Reset;
				uart_puts_P("xxx");
			}
		}
	}
}

extern void PC_Interface_Init()
{
	Status = State_Reset;
	TCNT2 = 5;
	TIMSK |= (1 << TOIE2);
}

extern PC_Interface_CommandTypeDef PC_Interface_Perform()
{
	if(Status == State_Receive_Complete)
	{
		TCCR2 = TCCR0_STOP;
		if(Command == Command_Who)
		{
			uart_putc(0);
			uart_putc(3);
			uart_putc(0x1e);
			uart_putc(0x4f);
		} else if (Command == Command_CaseInUSe)
		{
			if(parameter1 == ADDRESS)
			{
				uart_putc(ADDRESS);
				if(IOPopulated)
				{
					uart_putc(1);
				} else {
					uart_putc(0);
				}
			}
		} else if (Command == Command_Unlock)
		{
			if(parameter1 == ADDRESS)
			{
				uart_putc(ADDRESS);
				uart_putc(Command_Unlock);
				IOUnlocked = 1;
			}
		} else if (Command == Command_Locked)
		{
			if(parameter1 == ADDRESS)
			{
				uart_putc(ADDRESS);
				if(IODoorClosed)
				{
					uart_putc(1);
				} else {
					uart_putc(0);
				}
			}
		}
		Status = State_Reset;
	}
	return Command;
}

ISR(TIMER2_OVF_vect)
{
	TCNT2 = 5;
	ms_counter++;
}

/*
 *	Local Functions (Definitions)
 */

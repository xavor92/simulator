/*
 * io.c
 *
 *  Created on: 07.05.2015
 *      Author: olli
 */

/*
 *	Includes
 */

#include "io.h"
#include <util/delay.h>

/*
 *	Defines
 */



/*
 *	Local Functions (Declaration, static)
 */

/*
 *	Global Functions (Definitions)
 */

/**
 * Initialize all IO Ports & Variables
 */
extern void io_init()
{
	DDRD |= ( (1 << L1_PIN) | ( 1 << L2_PIN ) | (1 << L3_PIN ) | (1 << L4_PIN ) | (1 << L5_PIN) | (1 << L6_PIN) );
	DDRB &= ~( (1 << S1_PIN) | (1 << S2_PIN) | (1 << S3_PIN) | (1 << S4_PIN) );
	PORTB |= ( (1 << S1_PIN) | (1 << S2_PIN) | (1 << S3_PIN) | (1 << S4_PIN) );
	IODoorClosed = 1;
	IOPopulated = 1;
	IOUnlocked = 0;
}

extern void io_service()
{
	//todo io kram
	//todo timeout doorlock


	if( __IO_IS_SET(S2_PORT, S2_PIN) && IOUnlocked)
	{
		IOUnlocked = 0;
		IODoorClosed = 0;
	}

	if( __IO_IS_SET(S3_PORT, S3_PIN) && IODoorClosed == 0)
	{
		IODoorClosed = 1;
	}

	if( __IO_IS_SET(S4_PORT, S4_PIN))
	{
		if(IOPopulated)
		{
			IOPopulated = 0;
		} else {
			IOPopulated = 1;
		}
		if(IOPopulated)
		{
			__IO_SET(L5_PORT, L5_PIN);
			__IO_RESET(L6_PORT, L6_PIN);
		} else {
			__IO_RESET(L5_PORT, L5_PIN);
			__IO_SET(L6_PORT, L6_PIN);
		}
		_delay_ms(300);
	}
	if(IOUnlocked)
	{
		__IO_SET(L2_PORT, L2_PIN);
	} else {
		__IO_RESET(L2_PORT, L2_PIN);
	}
	if(IOPopulated)
	{
		__IO_SET(L5_PORT, L5_PIN);
		__IO_RESET(L6_PORT, L6_PIN);
	} else {
		__IO_RESET(L5_PORT, L5_PIN);
		__IO_SET(L6_PORT, L6_PIN);
	}
	if(IODoorClosed)
	{
		__IO_SET(L4_PORT, L4_PIN);
		__IO_RESET(L3_PORT, L3_PIN);
	} else {
		__IO_RESET(L4_PORT, L4_PIN);
		__IO_SET(L3_PORT, L3_PIN);
	}
}

/*
 *	Local Functions (Definitions)
 */

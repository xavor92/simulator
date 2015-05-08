/*
 * main.c
 *
 *  Created on: 07.05.2015
 *      Author: olli
 */

/*
 *	Includes
 */

#include <avr/interrupt.h>
#include <avr/io.h>
#include "uart.h"
#include "io.h"
#include "pc_interface.h"

/*
 *	Defines
 */

#define UART_BAUD_RATE 19200



/*
 *	Local Functions (Declaration, static)
 */

/*
 *	Global Functions (Definitions)
 */

int main()
{
	uart_init(UART_BAUD_SELECT(UART_BAUD_RATE,F_CPU));
	sei();
	PC_Interface_Init();
	io_init();
	__IO_SET(L1_PORT, L1_PIN);
	while(1)
	{
		PC_Interface_CheckTimeout();
		PC_Interface_Receive();
		PC_Interface_Perform();
		io_service();
	}
	return 0;
}

/*
 *	Local Functions (Definitions)
 */

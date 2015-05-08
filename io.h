/*
 * io.h
 *
 *  Created on: 07.05.2015
 *      Author: olli
 */

#ifndef IO_H_
#define IO_H_

/*
 *	Includes
 */

#include <avr/io.h>

/*
 *	Defines
 */

#define S1_PORT PINB
#define S1_PIN PB1
#define S2_PORT PINB
#define S2_PIN PB2
#define S3_PORT PINB
#define S3_PIN PB3
#define S4_PORT PINB
#define S4_PIN PB4

#define L1_PORT PORTD
#define L1_PIN PD2
#define L2_PORT PORTD
#define L2_PIN PD3
#define L3_PORT PORTD
#define L3_PIN PD4
#define L4_PORT PORTD
#define L4_PIN PD5
#define L5_PORT PORTD
#define L5_PIN PD7
#define L6_PORT PORTD
#define L6_PIN PD6

#define __IO_SET(port, pin) (port) |= ( 1 << (pin) )
#define __IO_RESET(port, pin) (port) &= ~(1 << (pin) )
#define __IO_IS_SET(port, pin) ((port) & (1 << (pin))) == 0

unsigned char IODoorClosed, IOPopulated, IOUnlocked;

/*
 *	Global Functions (Declarations, extern)
 */

extern void io_init();
extern void io_service();

#endif /* IO_H_ */

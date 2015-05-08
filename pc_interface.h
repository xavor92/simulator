/*
 * pc_interface.h
 *
 *  Created on: 07.05.2015
 *      Author: olli
 */

#ifndef PC_INTERFACE_H_
#define PC_INTERFACE_H_

/*
 *	Includes
 */

#include "io.h"

/*
 *	Defines
 */

#define TIMEOUT 1000
#define START_SYMBOL '!'

typedef enum {
	State_Reset,
	State_Start0,
	State_Start1,
	State_StartComplete,
	State_CommandReceived,
	State_ParameterReceived,
	State_Receive_Complete,
	State_Timeout,
} PC_Interface_StateTypeDef;

typedef enum {
	Command_Who = 'w',
	Command_CaseInUSe = 'b',
	Command_Unlock = 'u',
	Command_Locked = 'l',
} PC_Interface_CommandTypeDef;

/*
 *	Global Functions (Declarations, extern)
 */

extern void PC_Interface_Receive();
extern void PC_Interface_Init();
extern PC_Interface_CommandTypeDef PC_Interface_Perform();
extern void PC_Interface_CheckTimeout();


#endif /* PC_INTERFACE_H_ */

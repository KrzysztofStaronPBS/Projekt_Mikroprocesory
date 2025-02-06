/*
 * Cmd_Interpreter.h
 *
 *  Created on: Nov 14, 2024
 *      Author: Krzysztof Staroń
 *      		WTIiE, IST sem. III
 *      		Grupa 04, nr albumu: 122426
 */

#ifndef INC_CMDINTERPRETER_H_
#define INC_CMDINTERPRETER_H_

#include "ParseFrame.h"
#include "Receive_Frame.h"
#include "Command.h"
#include <string.h>

void CmdInterpreter(Command_t *);

#endif /* INC_CMDINTERPRETER_H_ */

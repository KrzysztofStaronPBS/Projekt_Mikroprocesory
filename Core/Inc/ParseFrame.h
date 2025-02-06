/*
 * ParseFrame.h
 *
 *  Created on: Jan 30, 2025
 *      Author: Krzysztof
 */

#ifndef INC_PARSEFRAME_H_
#define INC_PARSEFRAME_H_

#include "Frame.h"
#include "Receive_Frame.h"
#include "CmdInterpreter.h"
#include <string.h>


void ParseFrame(Frame_t *);

#endif /* INC_PARSEFRAME_H_ */

/*
 * Command.h
 *
 *  Created on: Nov 14, 2024
 *      Author: Krzysztof Staroń
 *      		WTIiE, IST sem. III
 *      		Grupa 04, nr albumu: 122426
 */

#ifndef INC_COMMAND_H_
#define INC_COMMAND_H_

#define MAX_ARGUMENT_COUNT 2

typedef struct {
	char CommandName[20];
	uint16_t CommandLength;
	uint16_t Argument[MAX_ARGUMENT_COUNT];
	uint8_t Arguments_count;
} Command_t;

#endif /* INC_COMMAND_H_ */

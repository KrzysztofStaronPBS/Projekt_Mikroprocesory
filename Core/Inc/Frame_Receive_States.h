/*
 * Parser_States.h
 *
 *  Created on: Nov 14, 2024
 *      Author: Krzysztof Staroń
 *      		WTIiE, IST sem. III
 *      		Grupa 04, nr albumu: 122426
 */

#ifndef INC_PARSER_STATES_H_
#define INC_PARSER_STATES_H_

typedef enum {
	Wait,
	ReadSender,
	ReadReceiver,
	ReadDataSize,
	ReadData,
	DecodeData,
	ReadChecksum,
	End
} FrameStatus;

#endif /* INC_PARSER_STATES_H_ */

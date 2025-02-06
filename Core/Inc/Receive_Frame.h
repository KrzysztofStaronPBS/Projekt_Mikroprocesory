/*
 * ReceiveFrame.h
 *
 *  Created on: Nov 30, 2024
 *      Author: Krzysztof Staroń
 *      		WTIiE, IST sem. III
 *      		Grupa 04, nr albumu: 122426
 */

#ifndef INC_RECEIVE_FRAME_H_
#define INC_RECEIVE_FRAME_H_

#include "Frame_Receive_States.h"
#include "Frame.h"
#include "ParseFrame.h"

#define FRAME_START_SIGN Ox5B
#define FRAME_END_SIGN 0x5D
#define ENCODING_SIGN 0x2F

#define ENCODED_FRAME_START_SIGN 0x62
#define ENCODED_FRAME_END_SIGN 0x65
#define ENCODED_ENCODING_SIGN 0x63

#define ARGUMENTS_START_CHAR 0x28
#define ARGUMENTS_END_CHAR 0x29
#define ARGUMENTS_NEXT_ARG 0x2C

#define SENDER_LENGTH 2
#define RECEIVER_LENGTH 2
#define DATA_SIZE_LENGTH 2
#define CHECKSUM_LENGTH 5


void ReceiveFrame();

ReceiveStatusCode_t Dec2Byte (char, uint8_t *);
ReceiveStatusCode_t DecodeByte (uint8_t, uint8_t *);
ReceiveStatusCode_t ValidateChecksum (Frame_t );

#endif /* INC_RECEIVE_FRAME_H_ */

/*
 * Frame.h
 *
 *  Created on: Nov 14, 2024
 *      Author: Krzysztof Staroń
 *      		WTIiE, IST sem. III
 *      		Grupa 04, nr albumu: 122426
 */

#ifndef INC_FRAME_H_
#define INC_FRAME_H_

#include <stdio.h>
#include <ctype.h>
#include "CRC_16_ANSI.h"
#include "Cyclic_Buffer.h"
#include "UART_Communication.h"
#include "Command.h"
#include "Frame.h"

#define MIN_FRAME_LENGTH 13
#define MAX_FRAME_LENGTH 77
#define MAX_DATA_LENGTH 64

typedef struct {
	uint16_t Sender;
	uint16_t Receiver;
	uint16_t DataSize;
	uint8_t Data[MAX_DATA_LENGTH];
	uint16_t Checksum;
}Frame_t;

typedef enum {
	DecCorrectChar,
	DecIncorrectChar,
	DecodeCompleted,
	DecodeError,
	ChecksumGood,
	ChecksumError
} ReceiveStatusCode_t;

typedef enum {
	Generate,
	Send
} SendStatusCode_t;


void ReceiveFrame();

void SendStatusFrame(uint8_t);
void SendErrorFrame(uint8_t);
void SendDataFrame(const char*, uint8_t);

#endif /* INC_FRAME_H_ */

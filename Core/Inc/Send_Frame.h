/*
 * Send_Frame.h
 *
 *  Created on: Dec 1, 2024
  *      Author: Krzysztof Staroń
 *      		WTIiE, IST sem. III
 *      		Grupa 04, nr albumu: 122426
 */

#ifndef INC_SEND_FRAME_H_
#define INC_SEND_FRAME_H_

#include "Frame.h"
#include "Receive_Frame.h"

typedef struct {
	char Sender [SENDER_LENGTH];
	char Receiver [RECEIVER_LENGTH];
	char DataSize [DATA_SIZE_LENGTH];
	char Checksum [CHECKSUM_LENGTH];
} FrameToSend_t;

typedef enum {
	Data,
	Status,
	CmdNotFoundError,
	InvalidArgTypeError,
	NoConnectionWithSensorError
} ResponseType_t;

uint8_t SendFrame ();
void SetAnswerForSetCommand(Frame_t);
void Uint2Dec (uint16_t , char *, uint16_t);

#endif /* INC_SEND_FRAME_H_ */

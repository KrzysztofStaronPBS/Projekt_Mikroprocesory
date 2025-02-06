/*
 * Send_Frame.c
 *
 *  Created on: Dec 1, 2024
 *      Author: Krzysztof Staroń
 *      		WTIiE, IST sem. III
 *      		Grupa 04, nr albumu: 122426
 */

#include "Send_Frame.h"

extern static Frame_t ReceivedFrame;

uint8_t SendFrame (ResponseType_t TypeOfResponse)
{
	static Frame_t ResponseFrame;

	ResponseFrame.Sender = ReceivedFrame -> Receiver;
	ResponseFrame.Receiver = ReceivedFrame -> Sender;

	memcpy(ResponseFrame.Data, "TEST", 4);
	ResponseFrame -> DataSize = 4;

	// TODO: dodawanie odpowiednich danych to sekcji danych - switch(ResponseType)
	switch(ResponseType_t)
	{
	case Data:
		// TODO: wysyłanie zażądanych danych
		break;

	case Status:
		SetDone(ResponseFrame);
		break;

	case CmdNotFoundError:
		SetErrorMessage(ResponseFrame, "CMDNOTFOUND");
		break;

	case InvalidArgTypeError:
		SetErrorMessage(ResponseFrame, "INVALIGARGTYPE");
		break;

	case NoConnectionWithSensorError:
		SetErrorMessage(ResponseFrame, "NOCONNECTIONWITHSENSOR");
		break;
	}


	ResponseFrame -> Checksum = Crc16Ansi(ResponseFrame -> Data, ResponseFrame -> DataSize);


	FrameToSend_t ConvertedFrame;

	// konwersja z liczb dziesiętnych na zakodowane dane
	Uint2Dec(ResponseFrame.Sender, ConvertedFrame.Sender, SENDER_LENGTH);
	Uint2Dec(ResponseFrame.Receiver, ConvertedFrame.Receiver, RECEIVER_LENGTH);
	Uint2Dec(ResponseFrame.DataSize, ConvertedFrame.DataSize, DATA_SIZE_LENGTH);
	Uint2Dec(ResponseFrame.Checksum, ConvertedFrame.Checksum, CHECKSUM_LENGTH);

	// wysyłanie ramki
	UartSendText("[");
	UartSendData(ConvertedFrame.Sender, SENDER_LENGTH);
	UartSendData(ConvertedFrame.Receiver, RECEIVER_LENGTH);
	UartSendData(ConvertedFrame.DataSize, DATA_SIZE_LENGTH);
	UartSendData(ResponseFrame.Data, ResponseFrame.DataSize);
	UartSendData(ConvertedFrame.Checksum, CHECKSUM_LENGTH);
	UartSendText("]");
	return 1;
}

void SetRequestedData(Frame_t ResponseFrame, char * Request, uint16_t RequestedData, char * Message)
{

}

void SetDone(Frame_t ResponseFrame)
{
	ResponseFrame.Data = "DONE";
	return;
}

void SetErrorMessage(Frame_t ResponseFrame, char * ErrorCode)
{
	memcpy(ResponseFrame.Data, ErrorCode);
}

void Uint2Dec (uint16_t ToConvert, char * Converted, uint16_t Length)
{
	for (uint16_t i = Length; i > 0;)
	{
		Converted [-- i] = ToConvert % 10 + '0';
		ToConvert /= 10;
	}
}

uint16_t CountMessageLength(char * Message)
{

}

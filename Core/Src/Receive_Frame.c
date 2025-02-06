/*
 * ReceiveFrame.c
 *
 *  Created on: Nov 30, 2024
 *      Author: Krzysztof Staroń
 *      		WTIiE, IST sem. III
 *      		Grupa 04, nr albumu: 122426
 */

#include "Receive_Frame.h"

extern CyclicBuffer_t UartRxCyclicBuffer;

void ReceiveFrame()
{
    static FrameStatus ReadState = Wait;
    static Frame_t ReceivedFrame;
    static uint8_t DataCount = 0;
    static uint8_t ByteIndex = 0;
    uint8_t Tmp = 0;

    while (!IsCyclicBufferEmpty(&UartRxCyclicBuffer))
    {
        uint8_t ReceivedByte;

        __disable_irq();
        GetByteFromCyclicBuffer(&UartRxCyclicBuffer, &ReceivedByte);
        __enable_irq();

    	if (ReceivedByte == FRAME_START_SIGN
    			|| (ReceivedByte == ENCODING_SIGN && ReadState != ReadData)
				|| (ReceivedByte == FRAME_END_SIGN && ReadState != End))
        	{
        		ReadState = Wait;
        	}

        // maszyna stanów
        switch (ReadState)
        {
            case Wait:
                if (ReceivedByte == FRAME_START_SIGN)
                {
                	ReceivedFrame.Sender = 0;
                	ReceivedFrame.Receiver = 0;
                	ReceivedFrame.DataSize = 0;
                    DataCount = 0;
                    ReceivedFrame.Checksum = 0;
                    ByteIndex = 0;
                    ReadState = ReadSender;
                }
                break;

            case ReadSender:
                if (Dec2Byte(ReceivedByte, &Tmp) == DecCorrectChar)
                {
                    ReceivedFrame.Sender = (ReceivedFrame.Sender * 10) + Tmp;
                    ByteIndex++;
                    if (ByteIndex == SENDER_LENGTH)
                    {
                    	ByteIndex = 0;
                        ReadState = ReadReceiver;
                    }
                } else
                {
                    ReadState = Wait;
                }
                break;

            case ReadReceiver:
                if (Dec2Byte(ReceivedByte, &Tmp) == DecCorrectChar)
                {
                    ReceivedFrame.Receiver = (ReceivedFrame.Receiver * 10) + Tmp;
                    ByteIndex++;
                    if (ByteIndex == RECEIVER_LENGTH)
                    {
                    	ByteIndex = 0;
                        ReadState = ReadDataSize;
                    }
                } else
                {
                    ReadState = Wait;
                }
                break;


                // warunek dla datasize 0
            case ReadDataSize:
            	if (ReceivedFrame -> DataSize == 0)
            	{
            		ReadState = ReadChecksum;
            	}

                if (Dec2Byte(ReceivedByte, &Tmp) == DecCorrectChar)
                {
                    ReceivedFrame.DataSize = (ReceivedFrame.DataSize * 10) + Tmp;
                    ByteIndex++;
                    if (ByteIndex == DATA_SIZE_LENGTH)
                    {
                    	ByteIndex = 0;
                        // jeśli przekroczono rozmiar danych
                        if (ReceivedFrame.DataSize > MAX_DATA_LENGTH)
                        {
                            ReadState = Wait;
                        } else
                        {
                            ReadState = ReadData;
                        }
                    }
                } else
                {
                    ReadState = Wait;
                }
                break;

            case ReadData:
                if (ReceivedByte == ENCODING_SIGN)
                {
                    ReadState = DecodeData;
                } else
                {
                    ReceivedFrame.Data[DataCount++] = ReceivedByte;
                    if (DataCount == ReceivedFrame.DataSize)
                    {
                        ReadState = ReadChecksum;
                    }
                }
                break;

            case DecodeData:
                if (DecodeByte(ReceivedByte, &Tmp) == DecodeCompleted)
                {
                    ReceivedFrame.Data[DataCount++] = Tmp;
                    if (DataCount == ReceivedFrame.DataSize)
                    {
                        ReadState = ReadChecksum;
                    }
                } else
                {
                    ReadState = Wait;
                }
                break;

            case ReadChecksum:
                if (Dec2Byte(ReceivedByte, &Tmp) == DecCorrectChar)
                {
                    ReceivedFrame.Checksum = (ReceivedFrame.Checksum * 10) + Tmp;
                    ByteIndex++;
                    if (ByteIndex == CHECKSUM_LENGTH)
                    {
                        ReadState = End;
                    }
                } else
                {
                    ReadState = Wait;
                }
                break;

            case End:
                if (ReceivedByte == FRAME_END_SIGN)
                {
                    if (ValidateChecksum(ReceivedFrame) == ChecksumGood)
                    {
                        // ramka poprawna – parsowanie polecenia
                        ParseFrame(ReceivedFrame);
                    }
                }
                ReadState = Wait;
                break;

            default:
                ReadState = Wait;
                break;
        }
    }
}

ReceiveStatusCode_t Dec2Byte (char Character, uint8_t * ConvertedChar)
{
	if (!(Character >= '0' && Character <= '9'))
	{
		return DecIncorrectChar;
	}
	* ConvertedChar = Character - '0';
	return DecCorrectChar;
}

ReceiveStatusCode_t DecodeByte (uint8_t ByteIn, uint8_t * ByteOut)
{
	switch (ByteIn)
	{
	case ENCODED_FRAME_START_SIGN:
		* ByteOut = FRAME_START_SIGN;
		break;
	case ENCODED_FRAME_END_SIGN:
		* ByteOut = FRAME_END_SIGN;
		break;
	case ENCODED_ENCODING_SIGN:
		* ByteOut = ENCODING_SIGN;
		break;
	default:
		return DecodeError;
	}
	return DecodeCompleted;
}

ReceiveStatusCode_t ValidateChecksum (Frame_t Frame)
{
	uint16_t CalculatedCrc = Crc16Ansi(Frame -> Data, Frame -> DataSize);
	if (CalculatedCrc != Frame -> Checksum)
	{
		return ChecksumError;
	}
	return ChecksumGood;
}

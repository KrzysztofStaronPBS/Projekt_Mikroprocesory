/*
 * ParseFrame.c
 *
 *  Created on: Jan 30, 2025
 *      Author: Krzysztof
 */

#include "ParseFrame.h"


void ParseFrame(Frame_t * Frame)
{
	Command_t Command;
	uint8_t Tmp = 0;
	uint8_t ArgumentCount = 0;

	if (memchr(Frame -> Data, ARGUMENTS_END_CHAR, Frame -> DataSize) == NULL) return;

	while (Frame -> Data[Tmp] != ARGUMENTS_START_CHAR)
	{
		Command.CommandName[Tmp] = Frame -> Data[Tmp];
		Tmp ++;

		if (Tmp == Frame -> DataSize)
		{
			return;
		}
	}
	Command.CommandLength = Tmp;
	Tmp ++;

	if (Frame -> Data[Tmp] == ARGUMENTS_END_CHAR) return;

	while (Frame -> Data[Tmp] != ARGUMENTS_END_CHAR)
	{
		if(Dec2Byte(Frame -> Data[Tmp], Frame -> Data[Tmp]) == DecCorrectChar)
		{
			Command.Argument[ArgumentCount] = Frame -> Data[Tmp];
			Tmp ++;
		} else if (Frame -> Data[Tmp] == ARGUMENTS_NEXT_ARG)
		{
			ArgumentCount ++;
		}

		if (ArgumentCount > MAX_ARGUMENT_COUNT)
		{
			// TODO: ramka z komunikatem błędu o przekroczonej maksymalnej ilości argumentów
			return;
		}
	}

	CmdInterpreter(& Command);
	return;
}

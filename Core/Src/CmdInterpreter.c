/*
 * Cmd_Interpreter.c
 *
 *  Created on: Nov 18, 2024
 *      Author: Krzysztof Staroń
 *      		WTIiE, IST sem. III
 *      		Grupa 04, nr albumu: 122426
 */

#include "CmdInterpreter.h"

uint8_t Compare(Command_t * Command, char * CommandName)
{
	if (Command -> CommandLength == strlen(CommandName))
	{
		if (memcmp(Command -> CommandName, CommandName, Command -> CommandLength) == 0)
		{
			return 1;
		} else {
			return 0;
		}
	} else {
		return 0;
	}
}

void CmdInterpreter(Command_t * Command)
{
	if (Compare(Command, "DISPLAY"))
	{
		if (Command -> Argument[0] == 0)
		{
			// TODO: włączenie wyświetlacza
		} else if (Command -> Argument[0] == 1)
		{
			// TODO: włączenie wyświetlacza
		} else if (Command -> Argument[0] == 2)
		{
			// TODO: reset wyświetlacza
		} else {
			// TODO: ramka z błedem o nieprawidłowym argumencie polecenia
		}
	} else if (Compare(Command,"SETTEMPUNIT"))
	{
		if (Command -> Argument[0] == 1)
		{
			// TODO: ustawienie jednostki temperatury wyświetlanej na Celsjusze
		} else if (Command -> Argument[0] == 2)
		{
			// TODO: ustawienie jednostki temperatury wyświetlanej na Fahrenheity
		} else if (Command -> Argument[0] == 3)
		{
			// TODO: ustawienie jednostki temperatury wyświetlanej na Kelwiny
		} else {
			// TODO: ramka z błedem o nieprawidłowym argumencie polecenia
		}

	} else if (Compare(Command, "GETTEMPUNIT"))
	{
		// TODO: pobieranie aktualnie ustawionej jednostki temperatury powietrza
	} else if (Compare(Command, "SETINTERVAL"))
	{
		if (Command -> Argument[0] > 0 && Command -> Argument[0] <= 99999)
		{
			// TODO: ustawianie interwału czasowego czujnika
		} else {
			// TODO: ramka z nieprawidłową wartością polecenia
		}

	} else if (Compare(Command, "GETINTERVAL"))
	{
		// TODO: pobieranie ustawionego interwału czasowego
	} else if (Compare(Command, "GETCURTEMP"))
	{
		// TODO: pobieranie aktualnej temperatury powietrza
	} else if (Compare(Command, "GETCURHUM"))
	{
		// TODO: pobieranie aktualnej wilgotności powietrza
	} else if (Compare(Command, "GETARCHIVALTEMP"))
	{
		if (Command -> Argument[0] <= 349
				&& Command -> Argument[1] <= 349
				&& Argument[1] - Argument[0] <= 10)
		{
			// TODO: pobieranie wartości archiwalnych temperatury powietrza
		}
	} else if (Compare(Command, "GETARCHIVALHUM"))
	{
		if (Command -> Argument[0] <= 349
				&& Command -> Argument[1] <= 349
				&& Argument[1] - Argument[0] <= 10)
		{
			// TODO: pobieranie wartości archiwalnych wilgotności powietrza
		}
	} else {
		// TODO: ramka z nierozpoznanym poleceniem
	}
}

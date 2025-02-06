/*
 * CRC_16_ANSI.c
 *
 *  Created on: Nov 7, 2024
 *      Author: Krzysztof Staroń
 *      		WTIiE, IST sem. III
 *      		Grupa 04, nr albumu: 122426
 */

#include "CRC_16_ANSI.h"

// funkcja obliczająca cykliczny CRC-16-ANSI
uint16_t Crc16Ansi(uint8_t *Data, uint16_t length)
{
	uint16_t CRC = CRC_INIT;

	for (uint16_t i = 0; i < length; i ++)
	{
		// operacja XOR na początkowym CRC równym 0xFFFF z bieżącym bajcie danych
		CRC ^= Data[i];

		// pętla przetwarzająca 8 bitów w bajcie
		for (uint8_t j = 0; j < 8; j ++)
		{
			// jeśli najmłodszy bit jest równy 1, to jest on przesuwany bitowo w prawo i wykonywany jest XOR z wielomianem
			if (CRC & 0x0001)
			{
				CRC = (CRC >> 1) ^ CRC_POLYNOMIAL;
			// przeciwnym razie bit jest przesuwany w prawo bez modyfikacji
			} else
			{
				CRC >>= 1;
			}
		}
	}
	// zwrócenie obliczonej wartości CRC
	return CRC;
}

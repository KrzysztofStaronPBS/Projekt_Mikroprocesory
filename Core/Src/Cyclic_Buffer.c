/*
 * Cyclic_Buffer.c
 *
 *  Created on: Nov 7, 2024
 *      Author: Krzysztof Staroń
 *      		WTIiE, IST sem. III
 *      		Grupa 04, nr albumu: 122426
 */

#include <stdint.h>
#include "Cyclic_Buffer.h"

uint8_t UartRxCb[(MINIMUM_FRAME_SIZE + 2 * MAXIMUM_DATA_LENGTH) * 11];
uint8_t UartTxCb[(MINIMUM_FRAME_SIZE + 2 * MAXIMUM_DATA_LENGTH)];
uint8_t SensorCb[SENSOR_SIZE];

CyclicBuffer_t UartRxCyclicBuffer;
CyclicBuffer_t UartTxCyclicBuffer;
CyclicBuffer_t SensorCyclicBuffer;


// funkcja inicjalizująca pojedynczy bufor kołowy; tu przypisuję do danego bufora
// wskaźnik na tablicę wcześniej zdefiniowaną oraz długość bufora
// oraz ustawiam wartość Head (Empty) oraz Tail (Busy) na 0
void CyclicBufferInit (CyclicBuffer_t* Cb, uint8_t* Buffer, uint16_t Length)
{
	Cb -> Buffer = Buffer;
	Cb -> Head = 0;
	Cb -> Tail = 0;
	Cb -> Length = Length;
}

// funkcja inicjalizująca wszystkie trzy bufory kołowe
void InitBuffers()
{
	  CyclicBufferInit(&UartRxCyclicBuffer, UartRxCb, (MINIMUM_FRAME_SIZE + 2 * MAXIMUM_DATA_LENGTH) * 11);
	  CyclicBufferInit(&UartTxCyclicBuffer, UartTxCb, MINIMUM_FRAME_SIZE + 2 * MAXIMUM_DATA_LENGTH);
	  CyclicBufferInit(&SensorCyclicBuffer, SensorCb, SENSOR_SIZE);
}

// funkcja sprawdzająca, czy bufor kołowy jest pusty
uint8_t IsCyclicBufferEmpty (CyclicBuffer_t* Cb)
{
	// jeśli pozycja Head i pozycja Tail są takie same, bufor jest pusty
	return Cb -> Head == Cb -> Tail;
}

// funkcja sprawdzająca, czy bufor kołowy jest pełny
uint8_t IsCyclicBufferFull (CyclicBuffer_t* Cb)
{
	// jeśli pozycja Head powiększona o 1 modulo długość bufora jest równa pozycji
	// Tail (czyli pozycja Head jest zaraz przed pozycją Tail, to bufor kołowy jest pełny
	return ((Cb -> Head + 1) % Cb -> Length) == Cb -> Tail;
}


uint8_t GetByteFromCyclicBuffer (CyclicBuffer_t* Cb, uint8_t* Data)
{
	// jeśli bufor, którego mam pobrać bajt, to nie ma czego pobrać z bufora
	if (IsCyclicBufferEmpty(Cb))
	{
		return 0;
	}

	// pobieram dane z pozycji pierwszego zajętego miejsca w tablicy
	// i przesuwam Tail o jedną pozycję do przodu modulo długość bufora
	*Data = Cb -> Buffer[Cb -> Tail];
	Cb -> Tail = (Cb -> Tail + 1) % Cb -> Length;

	return 1;
}

uint8_t PutByteIntoCyclicBuffer (CyclicBuffer_t* Cb, uint8_t Data)
{
	// jesli bufor jest pełen, przesuwam Tail na początek bufora
	if (IsCyclicBufferFull(Cb))
	{
		Cb -> Tail = 0;
	}

	// wstawiam bajt danych na pozycję Head i przesuwam Head
	// o jedną pozycją do przodu modulo długość bufora
	Cb -> Buffer[Cb -> Head] = Data;
	Cb -> Head = (Cb -> Head + 1) % Cb -> Length;

	return 1;
}

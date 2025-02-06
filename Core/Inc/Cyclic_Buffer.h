/*
 * Cyclic_Buffer.h
 *
 *  Created on: Nov 7, 2024
 *      Author: Krzysztof Staroń
 *      		WTIiE, IST sem. III
 *      		Grupa 04, nr albumu: 122426
 */

#ifndef INC_CYCLIC_BUFFER_H_
#define INC_CYCLIC_BUFFER_H_

#include <stdint.h>

// rozmiary buforów kołowych; COMMUNICATION_SIZE jest dla buforów odbioru i wysyłki danych,
// a SENSOR_SIZE jest dla bufora do odbioru danych z czujnika
#define MINIMUM_FRAME_SIZE 16
#define MAXIMUM_DATA_LENGTH 100
#define SENSOR_SIZE 350

// struktura reprezentująca bufor kołowy; tworzę ją jako nowy typ danych,
// aby łatwiej później odnosić się do niej
typedef struct
{
	// wskaźnik na tablicę bufora
	uint8_t* Buffer;

	// pozycja pierwszego wolnego miejsca w tablicy do zapisu znaków
	volatile uint16_t Head;

	// pozycja pierwszego zajętego miejsca w tablicy do odczytu
	volatile uint16_t Tail;

	// długość (rozmiar) bufora kołowego
	volatile uint16_t Length;
} CyclicBuffer_t;

// funkcja inicjalizująca pojedynczy bufor kołowy
void CyclicBufferInit (CyclicBuffer_t*, uint8_t*, uint16_t);

// funkcja inicjalizująca wszystkie trzy bufory kołowe
void InitBuffers();

// funkcja sprawdzająca, czy bufor kołowy jest pusty
uint8_t IsCyclicBufferEmpty (CyclicBuffer_t*);

// funkcja sprawdzająca, czy bufor kołowy jest pełny
uint8_t IsCyclicBufferFull (CyclicBuffer_t*);

// funkcja pobierająca bajt danych z bufora kołowego
uint8_t GetByteFromCyclicBuffer (CyclicBuffer_t*, uint8_t*);

// funkcja umieszczająca bajt danych do bufora kołowego
uint8_t PutByteIntoCyclicBuffer (CyclicBuffer_t*, uint8_t);

#endif /* INC_CYCLIC_BUFFER_H_ */

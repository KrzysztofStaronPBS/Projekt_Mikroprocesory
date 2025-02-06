/*
 * UART_Communication.c
 *
 *  Created on: Nov 7, 2024
 *      Author: Krzysztof Staroń
 *      		WTIiE, IST sem. III
 *      		Grupa 04, nr albumu: 122426
 */


#include "UART_Communication.h"

extern CyclicBuffer_t UartRxCyclicBuffer;
extern CyclicBuffer_t UartTxCyclicBuffer;
extern CyclicBuffer_t SensorCyclicBuffer;

__IO uint8_t IsSendingData = 0;

// zmienne pomocnicze do wstawiania i pobierania bajtów do buforów
uint8_t UartRxTmp;
uint8_t UartTxTmp;

void HAL_UART_RxCpltCallback (UART_HandleTypeDef *huart)
{
	// jeśli instancja nie pochodzi z USART2,
	// to anuluje callback przy odbiorze danych
	if (huart -> Instance != USART2) {
		return;
	}

	// na czas umieszczania danych w buforze kołowym, wyłączam przerwania
	__disable_irq();
	PutByteIntoCyclicBuffer(&UartRxCyclicBuffer, UartRxTmp);
	__enable_irq();

	HAL_UART_Receive_IT(&huart2, &UartRxTmp, 1);
}

void HAL_UART_TxCpltCallback (UART_HandleTypeDef *huart)
{
	if (huart -> Instance != USART2) {
		return;
	}

	// jeśli bufor kołowy jest pusty,
	// to nie ma czego wysyłać i anuluje callback przy wysyłaniu danych
	if (IsCyclicBufferEmpty(&UartTxCyclicBuffer))
	{
		__disable_irq();
		IsSendingData = 0;
		__enable_irq();
		return;
	}

	__disable_irq();
	GetByteFromCyclicBuffer(&UartTxCyclicBuffer, &UartTxTmp);
	__enable_irq();
	HAL_UART_Transmit_IT(&huart2, &UartTxTmp, 1);
}

void UartSendData (uint8_t* DataByte, uint16_t DataLength)
{
	// wstawianie każdego bajtu danych z osobna do bufora kołowego do wysyłania danych
	for (uint16_t i = 0; i < DataLength; i ++)
	{
		__disable_irq();
		PutByteIntoCyclicBuffer(&UartTxCyclicBuffer, DataByte[i]);
		__enable_irq();
	}

	// jeśli trwa wysyłanie danych, nie należy zaczynać kolejnej wysyłki,
	// bo nie ma sensu robić tego drugi raz, bo jak już trwa
	// wysyłanie danych, to i tak wyśle dane z bufora
	__disable_irq();
	if (IsSendingData)
	{
		return;
	}
	__enable_irq();

	IsSendingData = 1;
	__disable_irq();
	GetByteFromCyclicBuffer(&UartTxCyclicBuffer, &UartTxTmp);
	__enable_irq();
	HAL_UART_Transmit_IT(&huart2, &UartTxTmp, 1);
}

// funkcja, która wyzyła ciąg znaków
void UartSendText (const char* Text)
{
	size_t TextLength = strlen(Text);
	UartSendData((uint8_t*) Text, TextLength);
}


// funkcja testowa do sprawdzania poprawności wysłania danych w terminalu Putty
void TestDataReceive()
{
	// póki bufor kołowy odbioru danych jest niepusty,
	// to w trakcie wyłączonych przerwań pobierać bajty z bufora odbioru
	// i tworzę wiadomość do wysłania w terminalu funkcją snprintf i wysyłam ją przez UART_SendText
	while (!IsCyclicBufferEmpty(&UartRxCyclicBuffer))
	{
		uint8_t ReceivedByte;

		__disable_irq();
		GetByteFromCyclicBuffer(&UartRxCyclicBuffer, &ReceivedByte);
		__enable_irq();

		char Message[100];

		snprintf(Message, sizeof(Message), "STM32 odbiór: %c\n\r", (char) ReceivedByte);

		UartSendText(Message);
	}


}

/*
 * UART_Communication.h
 *
 *  Created on: Nov 7, 2024
 *      Author: Krzysztof Staroń
 *      		WTIiE, IST sem. III
 *      		Grupa 04, nr albumu: 122426
 */

#ifndef INC_UART_COMMUNICATION_H_
#define INC_UART_COMMUNICATION_H_

#include "main.h"
#include "usart.h"
#include "Cyclic_Buffer.h"
#include "string.h"
#include "stdio.h"


// funkcja służąca do wysyłania danych w postaci bajtów o podanej ilości
void UartSendData (uint8_t*, uint16_t);

// funkcja, która wyzyła ciąg znaków
void UartSendText (const char*);

// funkcja testowa do wysyłania znaków w terminalu Putty;
// należy wywoływać ją w pętli głównej programu
void TestDataReceive();


#endif /* INC_UART_COMMUNICATION_H_ */

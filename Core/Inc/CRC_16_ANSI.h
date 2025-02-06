/*
 * CRC_16_ANSI.h
 *
 *  Created on: Nov 7, 2024
 *      Author: Krzysztof Staroń
 *      		WTIiE, IST sem. III
 *      		Grupa 04, nr albumu: 122426
 */

#include <stdint.h>

#ifndef INC_CRC_16_ANSI_H_
#define INC_CRC_16_ANSI_H_

#define CRC_POLYNOMIAL 0x8005
#define CRC_INIT 0xFFFF

uint16_t Crc16Ansi(uint8_t *Data, uint16_t length);


#endif /* INC_CRC_16_ANSI_H_ */

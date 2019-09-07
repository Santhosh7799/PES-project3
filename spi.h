/*
 * spi.h
 *
 *  Created on: 04-Dec-2017
 *      Author: Srikant and Santhosh
 */

#ifndef SOURCES_SPI_H_
#define SOURCES_SPI_H_
/* Included libraries */
#include "MKL25Z4.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define SS_HIGH (PTD_BASE_PTR->PSOR = 1)		// Set Slave Select (SS) output Low
#define SS_LOW  (PTD_BASE_PTR->PCOR = 1)		// Set Slave Select (SS) output High
#define DUMMY_BYTE 0xFF							// Dummy Byte used for reading

/**************************************************************************************
* SPI_init
* Initializes the SPI controller
*
* @return - None
**************************************************************************************/
 void SPI_init();

 /**************************************************************************************
 * SPI_read_byte
 * Reads a single byte from the SPI Bus
 *
 * @return - The byte read
 **************************************************************************************/
uint8_t SPI_read_byte();

/**************************************************************************************
* SPI_write_byte
* Sends a single byte on the SPI bus
*
* @param byte - Value of the byte to be written
* @return - Value obtained after writing in the SPI Bus
**************************************************************************************/
void SPI_write_byte(uint8_t byte);


/**************************************************************************************
* SPI_send_packet
* Sends numerous SPI Bytes given a pointer to a byte array and a length of how many
* bytes to send.
*
* @param p - Pointer to the packet start
* @param size - Size of the packet
* @return - None
**************************************************************************************/
void SPI_send_packet(uint8_t * p, size_t length);


/**************************************************************************************
* SPI_flush
* Blocks until SPI transmit buffer has completed transmitting
*
* @return - None
**************************************************************************************/
void SPI_flush();




#endif /* SOURCES_SPI_H_ */

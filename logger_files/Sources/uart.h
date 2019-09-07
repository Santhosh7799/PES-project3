/**************************************************************************
*project3                file: UART.H
*Author: santhosh thummanapalli and srikant gaikwad
*
**************************************************************************/

#ifndef SOURCES_UART_H_
#define SOURCES_UART_H_

#include "circbuf.h"
#include "MKL25Z4.h"
#include <stdio.h>

#define BUFFER_LENGTH 1000
#define OVER_SAMPLING_RATIO 16
#define BAUD_RATE 57600

CircBuf tx_buf,rx_buf;

/**************************************************************************************
* uart_configure
* Configures uart to settings. Needs to be dynamic based on intended BAUD
*
* @param baud_rate - Baud rate for the UART
* @return - None
**************************************************************************************/
void uart_configure();

/**************************************************************************************
* uart_send_byte
* Sends one byte. Blocks until transmission complete
*
* @param - None
 @return - None
*************************************************************************************/
//void uart_send_byte(char c);

/**************************************************************************************
* uart_receive_byte
* Receives one byte. Blocks until byte received.
*
* @param - None
* @return - None
**************************************************************************************/
//char uart_receive_byte();


void uart_send_byte();

void uart_receive_byte();

//void UART0_IRQHandler();

#endif /* SOURCES_UART_H_ */

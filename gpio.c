/*
 * gpio.c
 *
 *  Created on: 04-Dec-2017
 *      Author: Srikant and Gaikwad
 */

#include "gpio.h"

void GPIO_nrf_init(){

	 PORTD_PCR6 = PORT_PCR_MUX(1);			  // Set PTD6 to MUX 1
	 PTD_BASE_PTR->PDDR |= 1<<6;              // Set Port D Pin 6 output direction
	 PTC_BASE_PTR->PSOR = 1<<6;				  // Set Port D Pin 6 high

	 PORTD_PCR0 = PORT_PCR_MUX(0x1);
	 PORTD_PCR1 = PORT_PCR_MUX(0x2);          // Set PTD1 to MUX 2 [SPI0_SCK]
	 PORTD_PCR2 = PORT_PCR_MUX(0x2);          // Set PTD2 to MUX 2 [SPI0_MOSI]
	 PORTD_PCR3 = PORT_PCR_MUX(0x2);          // Set PTD3 to MUX 2 [SPIO_MISO]
}


/*
  * spi.c
 *
 *  Created on: 04-Dec-2017
 *      Author: Srikant and Santhosh
 */

#include "spi.h"
#include"gpio.h"

 void SPI_init(){

	 SIM_SCGC5 |= SIM_SCGC5_PORTD_MASK;                      // Turn on clock to D module
	 SIM_SCGC4 |= SIM_SCGC4_SPI0_MASK;                       // Enable SPI0 clock

	 GPIO_nrf_init();								

	 SPI0_C1 = SPI_C1_MSTR_MASK;        					 

	 SPI0_BR = (SPI_BR_SPPR(0x01) | SPI_BR_SPR(0x00));       
//Set baud rate pre-scale divisor to 3 & set baud rate divisor to 64 for baud rate of 15625 Hz

	 SPI0_C1 |= SPI_C1_SPE_MASK;                             Enable SPI0

 }

 uint8_t SPI_read_byte(){
	 uint8_t byte;
	 while ((SPI0->S & SPI_S_SPRF_MASK) != SPI_S_SPRF_MASK);          
	 byte = SPI0->D;									              
	 return byte;
 }

 void SPI_write_byte(uint8_t byte){
	 while ((SPI0->S & SPI_S_SPTEF_MASK) != SPI_S_SPTEF_MASK);        
	 SPI0->D = byte;							                      
	 //status = SPI_read_byte(byte);
 }

 void SPI_send_packet(uint8_t *p, size_t length){
	for (uint8_t i = 0; i < length; i++) {
	while ((SPI0->S & SPI_S_SPTEF_MASK) != SPI_S_SPTEF_MASK);    
		SPI_write_byte(*p);							
		p++;
	}
 }

 void SPI_flush(){
	 while ((SPI0->S & SPI_S_SPTEF_MASK) != SPI_S_SPTEF_MASK);       
 }


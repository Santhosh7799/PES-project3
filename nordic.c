/* Included libraries */
#include "MKL25Z4.h"
#include "nordic.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

void nrf_read_register(uint8_t reg){
	SPI_write_byte(R_REG | reg); 					
}
void nrf_write_register(uint8_t reg){
	SPI_write_byte(W_REG | reg);					
}

uint8_t nrf_read_status(){
	uint8_t value;
	SS_LOW;											// Make SS line Low
	nrf_read_register(NRF_STATUS_REG);				
	SPI_write_byte(DUMMY_BYTE);				
	SS_HIGH;										// Make SS line High
	return value;
}

void nrf_write_config(uint8_t value){
	SS_LOW;		// Make SS line Low
	nrf_write_register(NRF_CONFIG_REG);		
	SPI_read_byte();
	SPI_write_byte(value); 
	SPI_read_byte();
	SS_HIGH;													
}

uint8_t nrf_read_config(){
	uint8_t value;
	SS_LOW;														
	nrf_read_register(NRF_CONFIG_REG);	
	SPI_read_byte();
	SPI_write_byte(DUMMY_BYTE);							
	value = SPI_read_byte();
	SS_HIGH;										
	return value;
}

uint8_t nrf_read_rf_setup(){
	uint8_t value;
	SS_LOW;														
	nrf_read_register(NRF_RF_SETUP_REG);					
	value = SPI_write_byte(DUMMY_BYTE);						SS_HIGH;										
	return value;
}

void nrf_write_rf_setup(uint8_t byte){
	SS_LOW;											nrf_write_register(NRF_RF_SETUP_REG);					
	SPI_write_byte(byte);								SS_HIGH;													
}

uint8_t nrf_read_rf_ch(){
	uint8_t byte;
	SS_LOW;														
	nrf_read_register(NRF_RF_CH_REG);					
	value = SPI_write_byte(DUMMY_BYTE);					
	SS_HIGH;											return byte;
}
void nrf_write_rf_ch(uint8_t value){
	SS_LOW;										
	nrf_write_register(NRF_RF_CH_REG);						SPI_write_byte(value);							
	SS_HIGH;									
}

uint8_t* nrf_read_TX_ADDR(){
	SS_LOW;											// Make SS line Low
	nrf_read_register(NRF_TX_ADDR);							// Send Read Command for TX_ADDR Register
	for(uint8_t i=0; i<5; i++){
	tx_addr[i] = SPI_write_byte(DUMMY_BYTE);				// Send 5 Dummy Byte
	}
	SS_HIGH;										                   
     return tx_addr;
}

void nrf_write_TX_ADDR(){
	uint8_t p[5] = {0xA,0xB,0xC,0xD,0xE};
	SS_LOW;													    // Make SS line Low
	nrf_write_register(NRF_TX_ADDR);							// Send Write Command for TX_ADDR Register
	SPI_send_packet(p, 5);										// Read 5 bytes
	SS_HIGH;												    // Make SS line High
}

uint8_t nrf_read_fifo_status(){
	uint8_t value;
	SS_LOW;													    // Make SS line Low
	nrf_read_register(NRF_FIFO_STATUS_REG);						// Send Read Command for FIFO_STATUS Register
	value = SPI_write_byte(DUMMY_BYTE);						    // Send Dummy Byte
	SS_HIGH;												    // Make SS line High
	return value;
}

void nrf_flush_tx_fifo(){
	SS_LOW;										
	SPI_write_byte(NRF_FLUSH_TX_FIFO);						SS_HIGH;												    
}

void nrf_flush_rx_fifo(){
	SS_LOW;											// Make SS line Low
	SPI_write_byte(NRF_FLUSH_RX_FIFO);					// Send Read Command for FLUSH_TX_FIFO
	SS_HIGH;												    // Make SS line High
}


/*
 * nordic.h
 *
 *  Created on: 04-Dec-2017
 *      Author: Srikant and Santhosh
 */

#ifndef SOURCES_NORDIC_H_
#define SOURCES_NORDIC_H_

#include "spi.h"

#define R_REG               (0x00)
#define W_REG               (0x20)
#define NRF_STATUS_REG      (0x07)
#define NRF_CONFIG_REG      (0x00)
#define NRF_CONFIG_PRIM_RX  (0x01)
#define NRF_CONFIG_PWR_UP   (0x02)
#define NRF_RF_SETUP_REG    (0x06)
#define NRF_RF_CH_REG       (0x05)
#define NRF_TX_ADDR         (0x10)
#define NRF_FIFO_STATUS_REG (0x17)
#define NRF_FLUSH_TX_FIFO   (0xE1)
#define NRF_FLUSH_RX_FIFO   (0xE2)

uint8_t tx_addr[5];
/**************************************************************************************
* nrf_read_register
* Read the register and return the value
*
* @param reg - Register from where value is read
* @return - None
**************************************************************************************/
void nrf_read_register(uint8_t reg);

/**************************************************************************************
* nrf_write_register
* Write to the given register with the data.
*
* @param reg - Register to write the value
* @return - None
**************************************************************************************/
void nrf_write_register(uint8_t reg);

/**************************************************************************************
* nrf_read_status
* Reads the STATUS register
*
* @return - Value of STATUS register
**************************************************************************************/
uint8_t nrf_read_status();

/**************************************************************************************
* nrf_write_config
* Write to CONFIG register
*
* @param value - Value to be written in CONFIG register
* @return - None
**************************************************************************************/
void nrf_write_config(uint8_t value);

/**************************************************************************************
* nrf_read_config
* Read the CONFIG register
*
* @return - Value of the CONFIG register read
**************************************************************************************/
uint8_t nrf_read_config();

/**************************************************************************************
* nrf_read_rf_setup
* Reads RF_SETUP register
*
* @return - Value of the RF_SETUP register read
**************************************************************************************/
uint8_t nrf_read_rf_setup();

/**************************************************************************************
* nrf_write_rf_setup
* Writes to the RF_SETUP register
*
* @param value - Value to be written to the RF_SETUP register
* @return - None
**************************************************************************************/
void nrf_write_rf_setup(uint8_t value);

/**************************************************************************************
* nrf_read_rf_ch
* Reads RF_CH register
*
* @return - Value of the RF_CH register read
**************************************************************************************/
uint8_t nrf_read_rf_ch();

/**************************************************************************************
* nrf_write_rf_ch
* Writes to the RF_CH register
*
* @return - None
**************************************************************************************/
void nrf_write_rf_ch(uint8_t value);

/**************************************************************************************
* nrf_read_TX_ADDR
* Reads the 8 bytes of the TX_ADDR register
*
* @return - Pointer to the bytes of the TX_ADDR register
**************************************************************************************/
uint8_t* nrf_read_TX_ADDR();

/**************************************************************************************
* nrf_write_TX_ADDR
* Writes the 8 byte TX_ADDR register
*
* @param tx_addr - Pointer to the 8 bytes to be written into the TX_ADDR register
* @return - None
**************************************************************************************/
void nrf_write_TX_ADDR();

/**************************************************************************************
* nrf_read_fifo_status
* Reads FIFO_STATUS register
*
* @return - Value of the FIFO_STATUS register read
**************************************************************************************/
uint8_t nrf_read_fifo_status();

/**************************************************************************************
* nrf_flush_tx_fifo
* Sends the command FLUSH_TX
*
* @return - None
**************************************************************************************/
void nrf_flush_tx_fifo();

/**************************************************************************************
* nrf_flush_rx_fifo
* Sends the command FLUSH_RX
*
* @return - None
**************************************************************************************/
void nrf_flush_rx_fifo();

#endif /* SOURCES_NORDIC_H_ */

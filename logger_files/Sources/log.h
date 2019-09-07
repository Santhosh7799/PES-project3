/**************************************************************************
*project3                file: LOG.H
*Author: santhosh thummanapalli and srikant gaikwad
*This is file contains the header file for log.h 
*
**************************************************************************/

#ifndef SOURCES_LOG_H_
#define SOURCES_LOG_H_

/* Included libraries */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define FRDM
#define DEBUG

typedef struct b_logger_t{

    uint8_t log_ID;            /*Indicator on what the log is*/
    uint8_t log_length;        /*Number of bytes of payload*/
    uint32_t *log_payload;      /*Any associated data that is sent with the log (can vary in size). Dependent on the log ID*/

}b_logger;


#define LOG_RAW_DATA(data, length) (log_raw_data((uint8_t *)data, length))
#define LOG_RAW_STRING(string) (log_raw_string((uint8_t *)string))
#define LOG_RAW_INTR(num) (log_raw_intr(num))
#define LOG_RAW_FLUSH() (log_raw_flush())
//#define LOG_INIT_LOGGER() (log_intialize())
#define LOG_ITEM(log, index, length, payLoad, flag) (create_log_item(log, index, length, (uint32_t*) payLoad)); (log_item(log, flag))


typedef enum logger_t {

    LOGGER_INITIALIZED = 1,
    GPIO_INITIALIZED,
    SYSTEM_INITIALIZED,
    SYSTEM_HALTED,
    LOG_INFO,
    LOG_WARNING,
    LOG_ERROR,
    DATA_RECEIVED,
    DATA_ANALYSIS_STARTED,
    DATA_ALPHA_COUNT,
    DATA_NUMERIC_COUNT,
    DATA_PUNCTUATION_COUNT,
    DATA_MISC_COUNT,
    DATA_ANALYSIS_COMPLETED,
	HEARTBEAT
}logger_e;

typedef enum {

    LOG_SUCCESS,
    LOG_FAILURE,
    LOG_DESTROY_SUCCESSFUL

}log_error;

/**************************************************************************************
* log_raw_data
* Takes a pointer to the data and the number of characters to be sent on the UART.
*
* @param data - Pointer to the data
*        length - Number of bytes to be sent
* @return - If successful, returns an enumeration LOG_SUCCESS else returns LOG_FAILURE
**************************************************************************************/
log_error log_raw_data(uint8_t *data, uint32_t length);

/**************************************************************************************
* log_raw_string
* Takes a pointer input to print bytes on the UART
*
* @param string - Pointer to the data
* @return - If successful, returns an enumeration LOG_SUCCESS else returns LOG_FAILURE
**************************************************************************************/
log_error log_raw_string(uint8_t *string);

/**************************************************************************************
* log_raw_intr
* Logs the raw integer value by converting it from integer to Ascii value on the UART
*
* @param num - 32-bit integer
* @return - If successful, returns an enumeration LOG_SUCCESS else returns LOG_FAILURE
**************************************************************************************/
log_error log_raw_intr(uint32_t num);

/**************************************************************************************
* log_raw_flush
* Flushes out any data present in the tx_buf
*
* @return - If successful, returns an enumeration LOG_SUCCESS else returns LOG_FAILURE
**************************************************************************************/
log_error log_raw_flush();

/**************************************************************************************
* create_log_item
* Creates the structure for the log and assigns the values passed.
*
* @param log - Pointer to the b_logger structure
*        index - Number of Log ID
*        length - Length of the payload
*        payload - Pointer to the payload
* @return - If successful, returns an enumeration LOG_SUCCESS else returns LOG_FAILURE
**************************************************************************************/
log_error create_log_item(b_logger *log, logger_e index, uint8_t length, uint32_t* payLoad);

/**************************************************************************************
* log_raw_data
* Sends the log structure on the UART
*
* @param item - Pointer to the b_logger structure
*        flag - Determine log_raw_data or log_raw_intr function
* @return - If successful, returns an enumeration LOG_SUCCESS else returns LOG_FAILURE
**************************************************************************************/
log_error log_item(b_logger *item, uint8_t flag);

/**************************************************************************************
* destroy_log_item
* Frees the memory allocated for the log
*
* @param item - Pointer to the b_logger structure
* @return - If successful, returns an enumeration LOG_SUCCESS else returns LOG_FAILURE
**************************************************************************************/
log_error destroy_log_item(b_logger *item);

void log_initialize();

#endif /* SOURCES_LOG_H_ */

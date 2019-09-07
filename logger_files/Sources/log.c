/**************************************************************************
*project3                file: LOG.c
*Author: santhosh thummanapalli and srikant gaikwad
*This file contains the binary logger initialization and various other log functions.
*
**************************************************************************/

#include "log.h"
#include "data.h"

#ifdef FRDM
#include "uart.h"
#else
#include <stdio.h>
#include "uart.h"
#endif


log_error log_raw_data(uint8_t *data, uint32_t length){

	#ifdef DEBUG
    	#ifdef FRDM
	if (data == NULL)
	    return LOG_FAILURE;

	for(uint8_t i=0;i<length;i++){
		CB_AddItem(&tx_buf,*(data+i));
		length--;
	}
	/* Enable the tx interrupt when there is data in tx buffer */
	UART0_C2 |= UART0_C2_TIE_MASK;

	#else
        int8_t index;
        for( index=0; index<length; index++){
            printf("%d",*data++);
        }
    	#endif
    	#endif
    	return LOG_SUCCESS;
}

log_error log_raw_string(uint8_t *string){

	#ifdef DEBUG
    	#ifdef FRDM
	if (string == NULL)
	    return LOG_FAILURE;

	uint32_t i=0;

	while(*(string+i) !='\0')
	{
		/* Reads the string till \0 and adds that data to the transmit buffer */
		CB_AddItem(&tx_buf,*(string+i));
		i++;
	}
	/* Enable the tx interrupt when there is data in tx buffer */
	UART0_C2 |= UART0_C2_TIE_MASK;


	#else
        while(*string != '\0'){
            printf("%c",*string);
            string++;
        }
   	#endif
    	#endif
        return LOG_SUCCESS;
}

log_error log_raw_intr(uint32_t num){


	#ifdef DEBUG
	//uint8_t *temp = (uint8_t *)num;

	//uint32_t i=0;
	int8_t string[1000];
	int8_t *temp = string;

	/* Converting Integer to Ascii */
	my_itoa(temp,num,10);


	#ifdef FRDM
	/* transmitting string */
	LOG_RAW_STRING(temp);

	#else
    	printf("%d",num);
    	//printf("\n");

    	#endif
   	#endif
    	return LOG_SUCCESS;
}

log_error log_raw_flush()
{
	#ifdef DEBUG
	#ifdef FRDM
	/* Enable the tx interrupt when there is data in tx buffer */
	UART0_C2 |= UART0_C2_TIE_MASK;

	#else
  	while (CB_IsBufferEmpty(&tx_buf) != CB_Empty)
  	{
    		uint8_t data = 0;
    		CB_RemoveItem(&tx_buf);
    		printf("%d", data);
	}
	#endif
	#endif
	return LOG_SUCCESS;

}

log_error create_log_item(b_logger *log, logger_e index, uint8_t length, uint32_t* payLoad){

	log->log_ID = index;
	log->log_length = length;
	if(length != 0){
		log->log_payload = (uint32_t *)malloc(length * sizeof(uint32_t));
		log->log_payload = payLoad;

	}
	else
		payLoad =0;
		log->log_payload = payLoad;
	return LOG_SUCCESS;
}

log_error log_item(b_logger *item, uint8_t flag){

	if (item == NULL)
	  {
	    LOG_RAW_STRING("\nLog Item is null");
	    return 0;
	  }

	#ifdef DEBUG
	#ifdef FRDM

	LOG_RAW_STRING(" Log ID: ");
	LOG_RAW_INTR(item->log_ID);
	LOG_RAW_STRING(" Log Payload: ");
	if(item->log_length == 0)
		LOG_RAW_INTR(*item->log_payload);
	else{
	//	if(flag == 1){
	//		LOG_RAW_DATA(item->log_payload,item->log_length);
	//	}
	//	else{
			while(item->log_length!=0){
				LOG_RAW_INTR(*item->log_payload);
				item->log_payload++;
				item->log_length--;
			}
	//	}
	}
	#else
	if(flag == 0){
	LOG_RAW_STRING("Log ID: ");
	LOG_RAW_INTR(item->log_ID);
	LOG_RAW_STRING("Log Payload: ");
	LOG_RAW_INTR(0);
	LOG_RAW_FLUSH();
	}
	#endif
	#endif

	return LOG_SUCCESS;

}

log_error destroy_log_item(b_logger *item){

	#ifdef DEBUG
	#ifdef FRDM
	free(item->log_payload);
	free(item);
	#else
	  CB_DestroyBuffer(rx_buf);
	  CB_DestroyBuffer(tx_buf);
	#endif
	#endif
    return LOG_DESTROY_SUCCESSFUL;
}

void log_initialize() {

#ifdef DEBUG
#ifdef FRDM
	uart_configure();
#else
	/* Initialize the Transmit Buffer */
	CB_IntitalizeBuffer(&tx_buf,BUFFER_LENGTH);
	tx_buf.head = tx_buf.buffer;
	tx_buf.tail = tx_buf.buffer;
	tx_buf.count = 0;
	tx_buf.length = BUFFER_LENGTH;

	/* Initialize the Receive Buffer */
	CB_IntitalizeBuffer(&rx_buf,BUFFER_LENGTH);
	rx_buf.head = rx_buf.buffer;
	rx_buf.tail = rx_buf.buffer;
	rx_buf.count = 0;
	rx_buf.length = BUFFER_LENGTH;
#endif
#endif
}

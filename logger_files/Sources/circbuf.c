/**************************************************************************
*project3                file: circbuf.c
*Author: santhosh thummanapalli and srikant gaikwad
*this file contains functions for circular buffer.
*
**************************************************************************/

/*Including header files */
#include "circbuf.h"


/* Allocates a circular buffer structure and the buffer portion  */
CB_e CB_IntitalizeBuffer(CircBuf *buf, uint32_t size){

		buf->buffer = (uint8_t *)malloc(size);

		buf = malloc(sizeof(CircBuf));


		if(buf->buffer != NULL){
			return CB_Buffer_Initialization_Successful;
		}
		else
			return CB_Buffer_Allocation_Failure;
}

/* Frees the circular buffer */
CB_e CB_DestroyBuffer(CircBuf *buf) {

	if(buf->buffer == NULL)
		return CB_Null_Pointer;

	free(buf->buffer);
	buf->head = NULL;
	buf->tail = NULL;
	buf->buffer = NULL;
	buf->length = 0;
	buf->count = 0;

	return CB_Buffer_Destroy_Successful;
}

/* Adds an item to the circular buffer if the buffer is not full. */
CB_e CB_AddItem(CircBuf * buf, uint8_t item) {
	START_CRITICAL();
	if(buf->buffer == NULL)
		return CB_Null_Pointer;

	CB_e eCB;
	eCB = CB_IsBufferFull(buf);

	if(eCB == CB_Full){
	/*	log = (b_logger*)malloc(sizeof(b_logger));
		create_log_item(&log,LOG_WARNING,0,0);
		log_item(&log);*/
		return CB_Full;
	}

	if(buf->head == (buf->buffer)+(buf->length)-1){
		/* if head is at the last position of the buffer then add the item there
	       and then put head at the base address of the buffer */
		buf->head = buf->buffer;
		*buf->head = item;

		return CB_Buffer_Overwrite_Successful;
	}
	else{
		/* otherwise add the item at the location of head and then head++ */
		*buf->head = item;
		buf->head++;
		buf->count++;
		return CB_Buffer_Add_Successful;
	}
	STOP_CRITICAL();
}

/* Removes an item from the circular buffer if the buffer is not empty. If empty, returns an enumeration CB_Empty. */
uint8_t CB_RemoveItem(CircBuf *buf) {
	START_CRITICAL();
	uint8_t item;
	if( buf->buffer == NULL)
		return CB_Null_Pointer;

	CB_e eCB;
	eCB = CB_IsBufferEmpty(buf);

	if(eCB == CB_Empty)
		return CB_Empty;

	if(buf->tail == (( buf->buffer) + ( buf->length)) - 1) {

		item = *(buf->tail);
		*buf->tail = 0;
		buf->tail=buf->buffer;
	}

	else if( buf->head == buf->tail) {

		item = *buf->tail;
		buf->head = buf->buffer;
		buf->tail = buf->buffer;
	}

	else{

		item = *buf->tail;
		buf->tail++;
	}
	buf->count--;
	return item;
	STOP_CRITICAL();
}

/* Allows you to look at the nth item (must be less then count and greater or equal to zero) */
uint8_t CB_BufferPeak(CircBuf *buf, uint8_t n) {

	if(n > buf->count || n < 1)
		return CB_No_Length;

	uint8_t *temp = buf->buffer;
	uint8_t item;

	while(n != 0){
		temp++;
		n--;
	}

	item = *temp;
	return item;
}

/**************************************************************************
*project3                file: circbuf.h
*Author: santhosh thummanapalli and srikant gaikwad
*
**************************************************************************/
#ifndef SOURCES_CIRCBUF_H_
#define SOURCES_CIRCBUF_H_

/* Included libraries */
#include "MKL25Z4.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define START_CRITICAL() 	__disable_irq()
#define STOP_CRITICAL()  	__enable_irq()

/* Defines section */
/* Circular buffer definition from class lecture */
typedef struct CircBuf_t{

    uint8_t *buffer;                        /* Beginning of buffer in memory */
    uint8_t *head;                          /* Pointer to newest */
    uint8_t *tail;                          /* Pointer to oldest */
    size_t length;                          /* Length of the buffer (number of total items) */
    size_t count;                           /* Current no of elements */

}CircBuf;

/* Enumeration for the state of the Circular Buffer */
typedef enum {

    CB_No_Error,                            /* No error case */
    CB_Full,                                /* CB full */
    CB_Not_Full,                            /* CB Not full */
    CB_Empty,                               /* CB Empty */
    CB_Not_Empty,                           /* CB Not Empty */
    CB_Null_Pointer,                        /* Null pointer Error */
    CB_No_Length,                           /* No length specified */
	CB_Buffer_Initialization_Successful,    /* Initialization Successful */
    CB_Buffer_Allocation_Failure,           /* Free storage still disconnected: Allocation failure */
    CB_Buffer_Overwrite_Successful,         /* Overwriting to buffer is successful */
    CB_Buffer_Add_Successful,               /* Item Add Successful */
    CB_Buffer_Remove_Successful,            /* Item Remove Successful */
    CB_Buffer_Destroy_Successful,           /* Buffer freed Successfully */
    CB_Peak_Return_Successful               /* Successful fetch of nth item */

} CB_e;


/* Function prototypes */

/**************************************************************************************
* CB_AddItem
* Adds an item to the circular buffer if the buffer is not full.
* If full, returns an enumeration CB_Full else returns CB_Not_Full.

**************************************************************************************/
CB_e CB_AddItem(CircBuf *buf, uint8_t item);

/**************************************************************************************
* CB_RemoveItem
* Removes an item from the circular buffer if the buffer is not empty.
* If empty, returns an enumeration CB_Empty else returns CB_Not_Empty.
**************************************************************************************/
uint8_t CB_RemoveItem(CircBuf *buf);

/**************************************************************************************
* CB_IsBufferFull
* Checks if the circular buffer is full. Returns an enumeration CB_Full if full,
* otherwise returns CB_Not_Full.

**************************************************************************************/
__STATIC_INLINE CB_e CB_IsBufferFull(CircBuf *buf);

/**************************************************************************************
* CB_IsBufferEmpty
* Checks if the circular buffer is empty. Returns an enumeration CB_Empty if empty,
* otherwise returns CB_Not_Empty.

**************************************************************************************/
__STATIC_INLINE CB_e CB_IsBufferEmpty(CircBuf *buf);

/**************************************************************************************
* CB_BufferPeak
* Allows you to look at the nth item (must be less then count and greater or equal to
* zero)

**************************************************************************************/
uint8_t CB_BufferPeak(CircBuf * buf, uint8_t n);

/**************************************************************************************
* CB_IsBufferEmpty
* Allocates a circular buffer structure and the buffer portion in memory (on the heap)
* given a number of bytes

**************************************************************************************/
CB_e CB_IntitalizeBuffer(CircBuf *buf, uint32_t size);

/**************************************************************************************
* CB_IsBufferEmpty
* Frees the circular buffer from dynamic memory

**************************************************************************************/
CB_e CB_DestroyBuffer(CircBuf *buf);

/* Checks if the circular buffer is full. Returns an enumeration CB_Full if full, otherwise returns CB_Not_Full. */
CB_e CB_IsBufferFull(CircBuf *buf) {

	if(buf->buffer == NULL)
		return CB_Null_Pointer;

    if(buf->length == buf->count)
    	return CB_Full;
    else
    	return CB_Not_Full;
}

/* Checks if the circular buffer is empty. Returns an enumeration CB_Empty if empty, otherwise returns CB_Not_Empty. */
CB_e CB_IsBufferEmpty(CircBuf *buf) {

	if(buf->buffer == NULL)
		return CB_Null_Pointer;

	if(buf->count == 0)
		return CB_Empty;
	else
		return CB_Not_Empty;
}

#endif /* SOURCES_CIRCBUF_H_ */

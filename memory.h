/**************************************************************************
*project3                file: DMA.H
*Author: santhosh thummanapalli and srikant gaikwad
*This is file contains the functions memmove,memcpy,memset and memzero
*
**************************************************************************/


#ifndef __MEMORY_H__
#define __MEMORY_H__

#include <stdint.h>

/**
 * @brief moves data from source pointer data to destination pointer data location
 *
 * This function gets to pointers source and destination pointer and lenght of data to be moved
 * from source to destination location as pointed . It considers the case of overlapping and
 * does not corrupt data
 *
 * @return void
 */
uint8_t * my_memmove(uint8_t * src, uint8_t * dst, size_t length);



/**
 * @brief copies data from source pointer data to destination pointer data location
 *
 * This function gets to pointers source and destination pointer and lenght of data to be copied
 * from source to destination location as pointed . It just copies data from source to pointer without
 * considering the case of overlapping whcih mught result in corruption of data
 *
 * @return void
 */
uint8_t * my_memcpy(uint8_t * src, uint8_t * dst, size_t length);

/**
 * @brief It sets the pointer location with value specified
 *
 * This function gets a pointer source and a value which is to be stored
 *  at the location pointed and same value is stored at number of locations
 * defined by length
 *
 * @return void
*/
uint8_t* my_memset(uint8_t * src, uint8_t length, size_t value);


/**
 * @brief sets the locations with value zero
 *
 * This function gets a pointer source at which loaction zero value is  stored
 *  and same value is stored at number of locations defined by length
 *
 *
 * @return void
*/
uint8_t * my_memzero(uint8_t * src, size_t length);

/**
 * @brief reverses the order of bytes from souce pointer location
 *
 * This function gets a source pointer and it will reverse the order of bytes
 *  for the given length of bytes.
 *
 *
 * @return void
*/
 uint8_t * my_reverse(uint8_t * src, size_t length);


/**
 * @brief reserves the required number of memory locations dynamically
 *
 * This function reserves the required number of memory locations dynamically
 *  and returns pointer if allocated successfully or null pointer instead
 *
 *
 * @return void
*/
int32_t* reserve_words(size_t length);

/**
 * @brief it frees the memory allocated dynamically
 *
 * This function gets the the source pointer and it frees the memory allocated
 *  dynamically which are not been used.
 *
 *
 * @return void
*/
void free_words(int32_t * src);



#endif /* __MEMORY_H__ */










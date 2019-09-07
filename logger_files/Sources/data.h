/**************************************************************************
*project3                file: DATA.H
*Author: santhosh thummanapalli and srikant gaikwad
*
**************************************************************************/

#ifndef SOURCES_DATA_H_
#define SOURCES_DATA_H_

#include <stdint.h>
#include <stdio.h>

#define DATA_ERROR (0)
#define DECIMAL_BASE (10)

/**************************************************************************************
* my_itoa
* Manages signed data. Defined to convert an nteger type standard input data to an
* ASCII string.
*
* @param str - Pointer to store the resultant string
* @param data - Integer value to be converted
* @param base - radix of the Integer (in range 2-36)
* @return - The resultant converted Integer value. Return error code, if unsuccessful
**************************************************************************************/
int8_t * my_itoa(int8_t * str, int32_t data, int32_t base);



/*************************************************************************************
* my_atoi
* Manages signed data. Defined to convert the ASCII value back to its equivalent
* integer value.
*
* @param str - Pointer to a string to be converted to an Integer
* @return - The resultant converted Integer value. Return error code, if unsuccessful
*************************************************************************************/
int32_t my_atoi(int8_t * str);



/*************************************************************************************
* big_to_little32
* Defined to convert the data types in big-Endian representation to its equivalent
* little-Endian representation.
*
* @param data - Pointer to the big-Endian data that needs to be converted
* @param length - Length of bytes to convert
* @return - 0 if conversion is successful, else an error code
*************************************************************************************/
int8_t big_to_little32(uint32_t * data, uint32_t length);



/*************************************************************************************
* little_to_big32
* Defined to convert the data types in little-Endian representation to its equivalent
* big-Endian representation.
*
* @param data - Pointer to the little-Endian data that needs to be converted
* @param length - Length of bytes to convert
* @return - 0 if conversion is successful, else an error code
*************************************************************************************/
int8_t little_to_big32(uint32_t * data, uint32_t length);



/*************************************************************************************
* print_memory
* Defined to print the output hex bytes pointed to a given memory location.
*
* @param start - Pointer to the memory location for the hex output to be printed
* @param length - Length of bytes to print
*************************************************************************************/
void print_memory(uint8_t * start, uint32_t length);



#endif /* SOURCES_DATA_H_ */

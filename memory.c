/**************************************************************************
*project3                file: DMA.H
*Author: santhosh thummanapalli and srikant gaikwad
*This is file contains the functions memmove,memcpy,memset and memzero
*
**************************************************************************/
#include <stdio.h>
#include <stdint.h>
#include "memory.h"
#include <stdlib.h>

#pragma GCC push_options
#pragma GCC optimize ("O3")
/*memory move function*/
uint8_t* my_memmove(uint8_t* src,uint8_t* dst,size_t length)
{
    uint8_t   i ,a , b, c ;
	uint8_t* retn ;
	retn = dst ;
	a = dst - src ;
    if ( length > a )
    {
        b = length-a ;
        for ( c = 0 ; c < b ; c++)
        {
            *(dst+b) = *(dst);
	    dst++;
        }
    }
    for( i =0 ;  i<length ; i++)
    {
            if ( (src+i) != retn )
            *(retn+i) =  *(src + i);
	}
	return (uint8_t*) retn ;
}

#pragma GCC pop_options
/*memory copy function*/
uint8_t* my_memcpy( uint8_t* src, uint8_t* dst , size_t length)
{
	uint8_t   i;
for( i =0 ;  i<length ; i++)
	{
		*(dst+i) =  *(src + i);
	}
	return (uint8_t*)dst ;
}


/*Function to set all memory locations to the require value*/
uint8_t* my_memset(uint8_t* src, uint8_t length, size_t value)
{
	uint8_t i;
	for(i = 0 ; i < length ; i++)
	{
		*(src+i) = value ;
	}

	return (uint8_t*)src;

}


/*Function to set all memory locations to Zero*/

uint8_t* my_memzero(uint8_t* src, size_t length)
{
	for(uint8_t i = 0 ; i < length ; i++)
	{
		*(src+i) = 0 ;
	}

	return (uint8_t*)src;
}

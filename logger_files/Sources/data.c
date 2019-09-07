/**************************************************************************
*project3                file: DATA.C
*Author: santhosh thummanapalli and srikant gaikwad
*
**************************************************************************/

#include <stdio.h>
#include <stdint.h>
#include "data.h"

 int8_t x[32]={0};

int8_t *my_itoa(int8_t *src, int32_t data, int32_t base)
{
    int8_t remainder,length=0,signbit=1;

    if(src == NULL || base<0)               // Check for valid input
        return DATA_ERROR;

    if(data==0 && base==DECIMAL_BASE)       // Check for base == 10 and value of data is 0
    {
        *src++='0';
        length++;
    }
    if(data<0)                              // Check for data < 0
    {
        signbit=-1;
        data = -data;
    }
    if(data>0)                              // Check for data > 0
    {
        while (data!=0)                     // Loop for converting input data to ascii value
        {
            remainder = data % base;        // Calculate the remainder
            *src++ = (remainder>9)?(remainder-10)+'a':(remainder + '0');     // Check if remainder is greater than 9
            length++;
            data = data/base;               // Update number equal to the quotient
        }

    }

    if(signbit < 0)                         // Check for negative numbers
    {
        *src++ = '-';
        length++;
    }
    *src = '\0';

    int8_t *start = src - length;
    int8_t *end = src - 1;
    while(start<end)                        // Loop for reversing the above converted ascii value
    {
        int8_t temp = *start;
        *start++ = *end;
        *end-- = temp;
    }
    return src;
}




int32_t my_atoi(int8_t *str)
{
    int8_t sign = 1;
    uint32_t num=0;

    if(str == NULL)
        return DATA_ERROR;                 // Check for valid input

    if(*str == '-')                        // Check for negative number(first ascii character '-')
    {
        sign = -1;
    }
    while(*str != '\0')                    // Loop till the input ascii value is '\0'(null terminating character)
    {
        if (*str < '0' || *str >'9')       // Check for input ascii value is a alphabet character
            return 0;
        else
        {
            num = num*10;
            num = num + (*str++) - '0';    // Converting input ascii value to integer by subtracting value 48('0') from input

        }
    }
    num = sign*num;
    return num;
}

int8_t big_to_little32(uint32_t *data, uint32_t length)
{
    uint8_t *ptr;
    ptr = (uint8_t *)data;
    uint32_t tempvar;

    if(data == NULL && length<0)
        return DATA_ERROR;                // Check for valid input

    for(uint8_t index=0; index<length; index++)
    {
        tempvar = *ptr;                   // Swapping 1st byte with the 4th byte and 2nd byte with the 3rd byte */
        *ptr=*(ptr+3);
        *(ptr+3) = tempvar;
        tempvar =*(ptr+1);
        *(ptr+1) = *(ptr+2);
        *(ptr+2) = tempvar;
        ptr = ptr+4;
    }
    return *(int8_t *)ptr;
}


int8_t little_to_big32(uint32_t *data, uint32_t length)
{
    uint8_t *ptr;
    ptr = (uint8_t *)data;
    uint32_t tempvar;

    if(data == NULL && length<0)            // Check for valid input
        return DATA_ERROR;

    for(uint8_t index=0; index<length; index++)
    {
        tempvar = *ptr;                     // Swapping 1st byte with the 4th byte and 2nd byte with the 3rd byte
        *ptr=*(ptr+3);
        *(ptr+3) = tempvar;
        tempvar =*(ptr+1);
        *(ptr+1) = *(ptr+2);
        *(ptr+2) = tempvar;
        ptr = ptr+4;
    }
    return *(int8_t *)ptr;
}


void print_memory(uint8_t *start, uint32_t length)
{
    if(start == NULL || length<0)           // Check for valid input
        printf("ERROR");
    for(uint8_t i = 0; i < length; i++)
    {
        printf("%x ",*(start + i));
    }
}


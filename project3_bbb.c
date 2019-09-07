/**************************************************************************
*project3                file: project3_bbb.c
*Author: santhosh thummanapalli and srikant gaikwad
*This is file contains the functions for bbb profiler
*
**************************************************************************/

#include <stdio.h>
#include <stdint.h>
#include "platform.h"
#include "project3_bbb.h"
#include "memory.h"
#include "conversion.h"
#include "debug.h"
#include <sys/time.h>
#define BASE_16 16
#define BASE_10 10

double time_diff(struct timeval x , struct timeval y);
//ptr[0]= 0x12;

double time_diff(struct timeval x , struct timeval y)
{
    double x_ms , y_ms , diff;
     
    x_ms = (double)x.tv_sec*1000000 + (double)x.tv_usec;
    y_ms = (double)y.tv_sec*1000000 + (double)y.tv_usec;
     
    diff = (double)y_ms - (double)x_ms;
     
    return diff;
}

void project1(void)
{
  uint8_t i;
  int8_t failed = 0;
  int8_t results[TESTCOUNT];

  uint8_t * ptra;
  uint8_t * ptrb;

uint8_t * set;
 set = (uint8_t*) reserve_words(10000);
ptra = &set[0];
ptrb = &set[5000];
  results[0] = test_data1();
  results[1] = test_data2();
  results[2] = test_memmove1();
  results[3] = test_memmove2();
  results[4] = test_memmove3();
  results[5] = test_memcpy();
  results[6] = test_memset();
  results[7] = test_reverse();

  // uint8_t j;
     
    struct timeval before , after;
    gettimeofday(&before , NULL);
   
    //Time taking task
    my_memmove(ptra, ptrb, 5000);
   
    gettimeofday(&after , NULL);
 
    printf("Total time elapsed : %.0lf us" , time_diff(before , after) ); 

  for ( i = 0; i < TESTCOUNT; i++)
  {
    failed += results[i];
  }
 // printf("--------------------------------\n");
  //printf("Test Results:\n");
  //printf("  PASSED: %d / %d\n", (TESTCOUNT - failed), TESTCOUNT);
  //printf("  FAILED: %d / %d\n", failed, TESTCOUNT);
 // printf("--------------------------------\n");
}

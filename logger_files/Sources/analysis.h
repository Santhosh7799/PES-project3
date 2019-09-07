/**************************************************************************
*project3                file: ANALYSIS.H
*Author: santhosh thummanapalli and srikant gaikwad
*This is file contains header file for analysis.h
*
**************************************************************************/

#ifndef SOURCES_ANALYSIS_H_
#define SOURCES_ANALYSIS_H_

/* Included libraries */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "circbuf.h"
#include "uart.h"

typedef struct char_analysis
{
  uint32_t alphabet;				/* Store count of Alphabets */
  uint32_t num;					/* Store count of Numbers */
  uint32_t punc;				/* Store count of Punctuations */
  uint32_t misc;				/* Store count of Miscellaneous characters */
} analysis_t;

typedef enum {

	SUCCESS
} analysis_e;

analysis_e analyze_bytes(CircBuf *buf, analysis_t *result, uint8_t numr);


#endif /* SOURCES_ANALYSIS_H_ */

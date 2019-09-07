/**************************************************************************
*project3                file: analysis.c
*Author: santhosh thummanapalli and srikant gaikwad
*Date: DEC 07, 2017
*
**************************************************************************/
/* Including header file containing function definitions used in analysis.c */
#include "analysis.h"


analysis_e analyze_bytes(CircBuf * buf, analysis_t * result, uint8_t numr)
{
  uint8_t num = 0;
  uint8_t alpha = 0;
  uint8_t punc = 0;
  uint8_t misc = 0;


  for(uint8_t i = 0; i < numr; i++)
  {
    uint8_t item = *(buf->buffer+i);

    
    if (item >= 48 && item <= 57)
    {
      num++;                 /* Adding numbers*/
    }

    
    else if (item >= 65 && item <= 90)
    {
      alpha++;              /* Adding upper case letters*/
    }

    
    else if (item >= 97 && item <= 122)
    {
      alpha++;              /* Adding lower case letters*/
    }

    
    else if (item >= 33 && item <= 47)
    {
      punc++;                /* Adding punctuation*/
    }

   
    else
    {
      misc++;              /* Adding miscellaneous characters*/
    }
  }

  /*Set members of results structure*/
  result->alpha = alpha;
  result->num = num;
  result->punc = punc;
  result->misc = misc;

}



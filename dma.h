/**************************************************************************
*project3                file: DMA.H
*Author: santhosh thummanapalli and srikant gaikwad
*This is file is the header file for the dma.c file 
*
**************************************************************************/

#ifndef INCLUDES_DMA_H_
#define INCLUDES_DMA_H_

typedef enum{dma_success, config_error}dma_st;
dma_st memmove_dma(uint8_t *src, uint8_t *dst, uint32_t length);
void memzero_dma(uint8_t *src, uint32_t length);
void DMA0_IRQHandler();

#endif /* INCLUDES_DMA_H_ */

/*****************************************************************************
*Project 3
*Author: santhosh Thummanapalli        and Srikanth gaikwad
* This file has the c modules for dma memmove,memzero and memset and it 
* includes profiling functions to caluculate the time taken for these functions
*
******************************************************************************/
#include"MKL25Z4.h"
#include"dma.h"
#include "string.h"
#include "memory.h"


#define a 10
uint16_t overflow_counts=0;
float time_spent = 0.0;
dma_st memmove_dma(uint8_t *src, uint8_t *dst, uint32_t length)
{
	/*Enabling clock gate for DMA and DMAMUX*/
	SIM_SCGC7 |= SIM_SCGC7_DMA_MASK;
	SIM_SCGC6 |= SIM_SCGC6_DMAMUX_MASK;

	
	DMAMUX0_CHCFG0 &= ~DMAMUX_CHCFG_ENBL_MASK;  /* channel 0 is being disabled before initializing*/
	DMA_DSR_BCR0 |= DMA_DSR_BCR_DONE_MASK;

	
       if(dst<src || dst>(src+length))       /* Giving Source and Destination address and Avoid Overlap*/
       {
	DMA_SAR0 =  src;
	DMA_DAR0 =  dst;
       }

        DMA_DSR_BCR0 |= length;         /* Totoal Number of Bytes to transfer */
	DMA_DCR0 |= DMA_DCR_SINC_MASK;	/* Increase Source Address after every transfer*/
	DMA_DCR0 |= DMA_DCR_SSIZE(1);	/* Transfer Size- 8 ,16, 32 bit*/
	DMA_DCR0 |= DMA_DCR_DINC_MASK;	/* Increase Destination Address after every transfer*/
	DMA_DCR0 |= DMA_DCR_DSIZE(1);	/* Transfer Size- 8,16, 32 bit*/


	DMA_DCR0 |= DMA_DCR_EINT_MASK;	/* Enable DMA Interrupt*/
	NVIC_EnableIRQ(DMA0_IRQn);
	__enable_irq;

	DMAMUX0_CHCFG0 |= DMAMUX_CHCFG_ENBL_MASK; /* Enable channel 0*/

       /***********Start Profiling****************/
	TPM1_SC |= TPM_SC_CMOD(1);		/* Starting Counter*/
        DMA_DCR0 |= DMA_DCR_START_MASK;        /*Start DMA Transfer*/	
}


void memzero_dma(uint8_t *dst, uint32_t length)
{
	uint32_t i=0;
	                                          /* Clock Gate enabled for DMA and DMAMUX*/
		SIM_SCGC7 |= SIM_SCGC7_DMA_MASK;
		SIM_SCGC6 |= SIM_SCGC6_DMAMUX_MASK;

		/* Disabling channel 0 before initializing*/
		DMAMUX0_CHCFG0 &= ~DMAMUX_CHCFG_ENBL_MASK;
		DMA_DSR_BCR0 |= DMA_DSR_BCR_DONE_MASK;
		/* Giving source address as address of 0 and Destination as array on which memzero in being performed*/
		DMA_SAR0 =  &i;
		DMA_DAR0 =  dst;

		DMA_DSR_BCR0 |= length;		        /* Number of Bytes in memzero */
		DMA_DCR0 &= ~DMA_DCR_SINC_MASK;		/* Do not increament source address*/
		DMA_DCR0 |= DMA_DCR_SSIZE(1);		/* 8or 32 bit transfer at a time*/
		DMA_DCR0 |= DMA_DCR_DINC_MASK;		/* Increament destination address after every transfer*/
		DMA_DCR0 |= DMA_DCR_DSIZE(1);		/* 8or 32 bit transfer at a time*/

		DMA_DCR0 |= DMA_DCR_EINT_MASK;		/* Enable DMA Interrupt*/
		NVIC_EnableIRQ(DMA0_IRQn);


		
		DMAMUX0_CHCFG0 |= DMAMUX_CHCFG_ENBL_MASK;  /* Enabling channel 0*/

		TPM1_SC |= TPM_SC_CMOD(1);
		
		DMA_DCR0 |= DMA_DCR_START_MASK;           /*Starting DMA Transfer*/
		
}


void DMA0_IRQHandler()
{ 	
     uint32_t i= DMA_DSR_BCR0;
     // Check source of interupt ; either done bit or CE bit
	if(DMA_DSR_BCR0 == DMA_DSR_BCR_DONE_MASK)
	{
		DMA_DSR_BCR0 |= DMA_DSR_BCR_DONE_MASK;		/* CLear done bit*/
				
	}
	else
	{
		DMA_DSR_BCR0 |= DMA_DSR_BCR_DONE_MASK;			/* Clear done bit and display DMA failure*/

	}
}



void start_profiling(void)
{

  SIM_SCGC6 |= SIM_SCGC6_TPM1_MASK;			/* Enabling TPM1 Clock gate*/
  SIM_SOPT2 |= SIM_SOPT2_TPMSRC(1);			/* Select MCGIRFLL clock 21 Mhz*/

  TPM1_SC=0;						/* Disable Timer*/
  TPM1 -> MOD = 65535;					/*Set Counter for 10 uS*/

  TPM1_SC |= TPM_SC_PS(0);	/* Prescaler divide by 1*/
  TPM1->SC |= 0x80;
  TPM1_SC |= TPM_SC_TOIE_MASK; 	/* Enable Timer Overflow Interrupt*/
  NVIC->ISER[0] |= 0x00040000;

}



//function to stop the timer and print out the clock cycles
void profiler_stop(void)
{
	
    char array[20] = {'\0'};
    uint32_t total_clocks = overflow_counts*65535 + TPM1->CNT;
    time_spent = total_clocks/20.97;	//total time in microseconds, 20.97 MHz clock is being used
 
}


//timer overflow interrupt handler
void TPM1_IRQHandler(void)
{
		overflow_counts++;
		TPM1_SC &= ~TPM_SC_TOF_MASK;	/*clear the tof bit by writing 1*/

}

/* In the main function below, functions are commeneted and uncommented for use based on the requirement*/

int main(){
	int i;
	uint8_t source[a]="ABCI",dest[a];


    __disable_irq();
	//UART0_init();

	start_profiling();			        //calling the profiler function
	__enable_irq();
	//memmove_dma(source,dest,a);		       // Memmove using DMA
	//memzero_dma(source,a);
	TPM1_SC |= TPM_SC_CMOD(1);
	//memmove (source, dest, a);
	my_memmove(source, dest, a);

	//memmove_dma(10);               //function to be profiled
	TPM1->SC = 0x0;                 //stopping the counter
	profiler_stop();                //stop_profiling();

	while(1){

	}
	return 0;
}


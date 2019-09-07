/**************************************************************************
*project3                file: UART.C
*Author: santhosh thummanapalli and srikant gaikwad
*This is file contains the connfiguration functions for UART
**************************************************************************/

#include "uart.h"
#include "circbuf.h"
#include "log.h"

void uart_configure(){

	__disable_irq();
	/* Enabling clock at portA (clock gating) */
	SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK;

	/* Enabling clock gating to UART0 */
	SIM_SCGC4 |= SIM_SCGC4_UART0_MASK;

	/* Source for UART0 is from MCGFLLCLK clock or MCGPLLCLK/2 clock */
	/* This chooses the FLL */
	SIM_SOPT2 |= SIM_SOPT2_UART0SRC(1);

	/* Sets mux to Alternative 2 to enable UART0 on pins to computer */
	PORTA_PCR1 = PORT_PCR_MUX(2);
	PORTA_PCR2 = PORT_PCR_MUX(2);

	/* UART set to 8 bit mode with no parity checking */
	UART0_C1 = 0;

	/* TX and RX disabled for now, change after settings */
	UART0_C2 = 0;

	/* Set baud rate */
	uint16_t baud = (uint16_t) (DEFAULT_SYSTEM_CLOCK/(BAUD_RATE*OVER_SAMPLING_RATIO));

	/* Baud Rate modulo divisor */
	UART0_BDH |= (baud >> 8) & UART0_BDH_SBR_MASK; //0x00
	UART0_BDL = (baud & UART0_BDL_SBR_MASK);

	/* Initialize the Transmit Buffer */
	CB_IntitalizeBuffer(&tx_buf,BUFFER_LENGTH);
	tx_buf.head = tx_buf.buffer;
	tx_buf.tail = tx_buf.buffer;
	tx_buf.count = 0;
	tx_buf.length = BUFFER_LENGTH;

	/* Initialize the Receive Buffer */
	CB_IntitalizeBuffer(&rx_buf,BUFFER_LENGTH);
	rx_buf.head = rx_buf.buffer;
	rx_buf.tail = rx_buf.buffer;
	rx_buf.count = 0;
	rx_buf.length = BUFFER_LENGTH;

	/* Enable Interrupt for UART0, interrupt 12 in vector table */
	NVIC_EnableIRQ(UART0_IRQn);

	/* Enable TX, RX, and RXI (receive interrupt) */
	UART_C2_REG(UART0_BASE_PTR) = (UART_C2_RIE_MASK | UART0_C2_RE_MASK | UART0_C2_TE_MASK);
	__enable_irq();
}

/*void uart_send_byte(char c){
	//Check if transmit data register is empty
	while((UART0_S1 & UART0_S1_TDRE_MASK) == 0);
	//Send the data
	UART0_D = c;
}
char uart_receive_byte(){
	char c;
	// Wait while receive data register is empty
	while((UART0_S1 & UART0_S1_RDRF_MASK)==0);
	// receive the data
	c = UART0_D;
	return c;
}
UART_e uart_send_n_bytes(uint8_t* item, uint32_t length) {
	if(item != NULL && length >UART_NUM_ZERO){
		uint32_t counter;
		for(counter = ZERO; counter < length; counter++){
			uart_send_byte(item + counter);
		}
		}
*/


void UART0_IRQHandler()
{	CB_e error_code = CB_IsBufferEmpty(&tx_buf);

	if((UART0_S1 & UART0_S1_TDRE_MASK) && error_code==CB_Not_Empty)
	{											// If buffer is not empty and TDRE flag is set then transmit the character
			uart_send_byte();
			//UART0_D =  CB_RemoveItem(&tx_buf);
	}
	else if(error_code==CB_Empty)
	{
		UART0_C2 &= ~UART0_C2_TIE_MASK;			// If tx buffer is empty then disable the tx interrupt
	}

	error_code = CB_IsBufferFull(&rx_buf);

	if((UART0_S1 & UART0_S1_RDRF_MASK) && error_code==CB_Not_Full)
	{
														// If buffer is not and RDRF flag is set then recieve the character from UARTD0
		uart_receive_byte();
	}
	else if(error_code==CB_Full)
	{
		UART0_C2 &= ~UART0_C2_RIE_MASK;  		// If rx buffer is full then disable the rx interrupt
	}
}

inline void uart_send_byte(){
	UART0_D =  CB_RemoveItem(&tx_buf);
}

inline void uart_receive_byte(){
	volatile uint8_t da=0;
	da = UART0_D;
	CB_AddItem(&rx_buf,da);
}

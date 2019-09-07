/**************************************************************************
*project3                file: MAIN_LOGGER.C
*Author: santhosh thummanapalli and srikant gaikwad
*This is  main function for logger
*
**************************************************************************/

#include "MKL25Z4.h"
#include "uart.h"
#include "log.h"
#include "analysis.h"
#include "string.h"
#include "rtc.h"


#define FRDM

#define NUM_CHAR_RECV 16

b_logger *log;

int main(void)
{
	CB_e error_code;

	uint8_t char_recv[NUM_CHAR_RECV];
	uint8_t data;
	analysis_t *analysis;
 	char error_message1[100] = "Malloc failed";

	log_initialize();

	log = (b_logger*)malloc(sizeof(b_logger));
	//create_log_item(&log,LOGGER_INITIALIZED,0,0);
	//log_item(&log);

	b_logger *log2 = NULL;

/*	if(log2 == NULL){
		//create_log_item(&log,LOG_ERROR,strlen(error_message1),&error_message1);
		//log_item(&log,1);
		LOG_ITEM(log, LOG_ERROR, strlen(error_message1), &error_message1, 1);
	}*/
	LOG_ITEM(log, LOGGER_INITIALIZED, 0, 0, 0 );

	//clock_config();
	rtc_init();

	while(1)
	{

	}

	//create_log_item(&log,GPIO_INITIALIZED,0,0);
	//log_item(&log);
	LOG_ITEM(log, GPIO_INITIALIZED, 0, 0, 0);

	//log = (b_logger*)malloc(sizeof(b_logger));
	//create_log_item(&log,SYSTEM_INITIALIZED,0,0);
	//log_item(&log);
	LOG_ITEM(log, SYSTEM_INITIALIZED, 0, 0, 0);


	while(1){

		/*if (interrupt){
					LOG_RAW_INTR(seconds);
					interrupt = 0;
				}*/

		error_code = CB_IsBufferEmpty(&rx_buf);
		if(error_code==CB_Not_Empty && rx_buf.count == NUM_CHAR_RECV){

			analysis = (analysis_t *)malloc(sizeof(analysis_t));
			analyze_bytes(&rx_buf, analysis, NUM_CHAR_RECV);

			LOG_ITEM(log, DATA_ANALYSIS_STARTED, 0, 0, 0);

			for(uint8_t i=0; i<16; i++){
				data = CB_RemoveItem(&rx_buf);
				char_recv[i] = data;
			}

			//create_log_item(&log,DATA_RECEIVED,16,&char_recv);
			//log_item(&log);
			LOG_ITEM(log, DATA_RECEIVED, NUM_CHAR_RECV, &char_recv, 1);

			//create_log_item(&log,DATA_ALPHA_COUNT,1,&analysis->alpha);
			//log_item(&log);
			LOG_ITEM(log, DATA_ALPHA_COUNT, 1, &analysis->alpha, 0);

			//create_log_item(&log,DATA_NUMERIC_COUNT,1,&analysis->num);
			//log_item(&log);
			LOG_ITEM(log, DATA_NUMERIC_COUNT, 1, &analysis->num, 0);

			//create_log_item(&log,DATA_PUNCTUATION_COUNT,1,&analysis->punc);
			//log_item(&log);
			LOG_ITEM(log, DATA_PUNCTUATION_COUNT, 1, &analysis->punc, 0);

			//create_log_item(&log,DATA_MISC_COUNT,1,&analysis->misc);
			//log_item(&log);
			LOG_ITEM(log, DATA_MISC_COUNT, 1, &analysis->misc, 0);

			//create_log_item(&log,DATA_ANALYSIS_COMPLETED,0,0);
			//log_item(&log,0);
			LOG_ITEM(log, DATA_ANALYSIS_COMPLETED, 0, 0, 0);
		}
	}

	destroy_log_item(&log);

    /* This for loop should be replaced. By default this loop allows a single stepping. */
	// for (;;) {
    // uart_send_byte('P');
    // x = uart_receive_byte();
    // uart_send_byte(x);
	//}
    return 0;
}

void RTC_Seconds_IRQHandler()
{
	START_CRITICAL();
	uint32_t time = RTC_TSR;
	LOG_ITEM(log, HEARTBEAT, 1, &time, 0);
	time_calc();
	LOG_RAW_STRING(" Date: ");
	LOG_RAW_INTR(myrtc.day);
	LOG_RAW_STRING("/");
	LOG_RAW_INTR(myrtc.month);
	LOG_RAW_STRING("/");
	LOG_RAW_INTR(myrtc.year);
	LOG_RAW_STRING(" Time: ");
	LOG_RAW_INTR(myrtc.hours);
	LOG_RAW_STRING(":");
	LOG_RAW_INTR(myrtc.minutes);
	LOG_RAW_STRING(":");
	LOG_RAW_INTR(myrtc.seconds);
	STOP_CRITICAL();
}

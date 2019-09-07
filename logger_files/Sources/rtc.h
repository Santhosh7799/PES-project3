/**************************************************************************
*project3                file: RTC.H
*Author: santhosh thummanapalli and srikant gaikwad
*
**************************************************************************/

#ifndef SOURCES_RTC_H_
#define SOURCES_RTC_H_

/* Included libraries */
#include "MKL25Z4.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define START_CRITICAL() 	__disable_irq()
#define STOP_CRITICAL()  	__enable_irq()

typedef struct rtc_t {
    uint8_t seconds;
    uint8_t minutes;
    uint8_t hours;
    uint16_t year;
    uint8_t month;
    uint8_t day;
}rtc;

struct rtc_t myrtc;
uint32_t rtc_time;

void rtc_init();

void time_calc(void);


#endif /* SOURCES_RTC_H_ */

/**************************************************************************
*project3                file: RTC.C
*Author: santhosh thummanapalli and srikant gaikwad
*This is file contains the rtc implementation functions
*
**************************************************************************/

#include "rtc.h"

uint32_t timestamp=0;


void rtc_init(){
    //Enabling clock to Port D
    SIM_SCGC5 |= SIM_SCGC5_PORTC_MASK;

    //Provide clock to SPI0
    SIM_SCGC6 |= SIM_SCGC6_RTC_MASK;

    //
    SIM_CLKDIV1 = ( SIM_CLKDIV1_OUTDIV1(0)| SIM_CLKDIV1_OUTDIV4(1) );
    //Enable the internal reference clock. MCGIRCLK is active.
    MCG_C1 |= MCG_C1_IRCLKEN_MASK;
    //Select the slow internal reference clock source.
    MCG_C2 &= ~(MCG_C2_IRCS_MASK);
    //Set PTC1 as RTC_CLKIN and select 32 KHz clock source for the RTC module.
    PORTC_PCR1 |= (PORT_PCR_MUX(0x1));
    SIM_SOPT1 |= SIM_SOPT1_OSC32KSEL(0b10);
    //Set PTC3 as CLKOUT pin and selects the MCGIRCLK clock to output on the CLKOUT pin.
    SIM_SOPT2 |= SIM_SOPT2_CLKOUTSEL(0b100);
    PORTC_PCR3 |= (PORT_PCR_MUX(0x5));

   //Enable software access and interrupts to the RTC module.
    SIM_SCGC6 |= SIM_SCGC6_RTC_MASK;

   //Clear all RTC registers.
    RTC_CR = RTC_CR_SWR_MASK;
    RTC_CR &= ~RTC_CR_SWR_MASK;

   if (RTC_SR & RTC_SR_TIF_MASK){
         RTC_TSR = 0x00000000;
    }
    //Set time compensation parameters. (These parameters can be different for each application)
    RTC_TCR = RTC_TCR_CIR(1) | RTC_TCR_TCR(0xFF);

   RTC_IER |= RTC_IER_TSIE_MASK;

   //Write to Time Seconds Register.
    RTC_TSR = timestamp;



   //Enable time seconds interrupt for the module and enable its irq.
    NVIC_EnableIRQ(RTC_Seconds_IRQn);

    //Enable time counter.
     RTC_SR |= RTC_SR_TCE_MASK;

     myrtc.seconds=0;
     myrtc.minutes=0;
     myrtc.hours=0;
}

void time_calc(void){
    uint32_t years, days ;
    uint8_t leap_years;
    rtc_time = RTC_TSR;

    myrtc.seconds = rtc_time%60;
    rtc_time /= 60;

    myrtc.minutes = rtc_time%60;
    rtc_time /= 60;

    myrtc.hours = rtc_time%24;
    rtc_time /= 24;

    years = rtc_time*4;
    years /= (365*4 +1);                		// Calculate number of years since 1970
    myrtc.year = (1970+years);          		// Update years

    leap_years = years/4;
    years -= leap_years;

    days = leap_years*366 + years*365;
    days = rtc_time - days + 1;             	// Calculate number of days since 1970

    if(myrtc.year%4 == 0){              		// For leap years
        if(days <= 31){
            myrtc.month = 1;            		// January
            myrtc.day = days;
        }
        else if(days <= 60){
            myrtc.month = 2;            		// February
            myrtc.day = days - 31;
        }
        else if(days <= 91){
            myrtc.month = 3;            		// March
            myrtc.day = days - 60;
        }
        else if(days <= 121){
            myrtc.month = 4;            		// April
            myrtc.day = days - 92;
        }
        else if(days <= 152){
            myrtc.month = 5;            		// May
            myrtc.day = days - 121;
        }
        else if(days <= 182){
            myrtc.month = 6;            		// June
            myrtc.day = days - 152;
        }
        else if(days <= 213){
            myrtc.month = 7;            		// July
            myrtc.day = days - 182;
        }
        else if(days <= 244){
            myrtc.month = 8;            		// August
            myrtc.day = days - 213;
        }
        else if(days <= 274){
            myrtc.month = 9;            		// September
            myrtc.day = days - 244;
        }
        else if(days <= 305){
            myrtc.month = 10;            		// October
            myrtc.day = days - 274;
        }
        else if(days <= 335){
            myrtc.month = 11;            		// November
            myrtc.day = days - 305;
        }
        else{
            myrtc.month = 12;            		// December
            myrtc.day = days - 335;
        }
    }
    else if(myrtc.year%4 != 0){              	// For non-leap years
        if(days <= 31){
            myrtc.month = 1;            		// January
            myrtc.day = days;
        }
        else if(days <= 59){
            myrtc.month = 2;            		// February
            myrtc.day = days - 31;
        }
        else if(days <= 90){
            myrtc.month = 3;            		// March
            myrtc.day = days - 59;
        }
        else if(days <= 120){
            myrtc.month = 4;            		// April
            myrtc.day = days - 91;
        }
        else if(days <= 151){
            myrtc.month = 5;            		// May
            myrtc.day = days - 120;
        }
        else if(days <= 181){
            myrtc.month = 6;            		// June
            myrtc.day = days - 151;
        }
        else if(days <= 212){
            myrtc.month = 7;            		// July
            myrtc.day = days - 181;
        }
        else if(days <= 243){
            myrtc.month = 8;            		// August
            myrtc.day = days - 212;
        }
        else if(days <= 273){
            myrtc.month = 9;            		// September
            myrtc.day = days - 243;
        }
        else if(days <= 304){
            myrtc.month = 10;            		// October
            myrtc.day = days - 273;
        }
        else if(days <= 334){
            myrtc.month = 11;            		// November
            myrtc.day = days - 304;
        }
        else{
            myrtc.month = 12;            		// December
            myrtc.day = days - 334;
        }
    }
}


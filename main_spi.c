

#include "fsl_device_registers.h"
#include "MKL25Z4.h"
#include "spi.h"
#include "nordic.h"
#include "gpio.h"
#include<stdio.h>
#include<stdint.h>

int main(void)
{
	uint8_t config;
	uint8_t *txaddress;
	uint8_t status;
	uint8_t rfch;
	uint8_t rfsetup;
	uint8_t fifostatus;
	uint8_t txaddr[5];
	SPI_init();
	while(1)
	{
		nrf_write_config(0x02);
		config=nrf_read_config();
		status=nrf_read_status();
		
	}
	return 0;

}


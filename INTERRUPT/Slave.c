/*
 * SPI_Slave.c
 *
 * Created: 8/22/2020 9:54:40 PM
 * Author : Lenovo
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include "UART.h"

#define DDR_SPI DDRB
#define MISO 3
#define MOSI 2
#define SCK 1
#define SS 0

void SPI_SlaveInit(void);
char SPI_SlaveReceive(void);
int main(void)
{
	USART_Init();
	SPI_SlaveInit();
	serialString("hello");
	uint8_t data;
	while (1)
	{
		//serialString("inside");
		data = SPI_SlaveReceive();
		//serialString("received");
		serialChar(data);
		if(data == '1')
		{
			PORTB |= (1 << 5);
			serialString("SLAVE LED ON");
		}
		else if(data == '0')
		{
			PORTB &= ~(1 << 5);
			serialString("SLAVE LED OFF");
		}
		
	}
}

void SPI_SlaveInit(void)
{
	DDR_SPI = (1 << MISO);
	SPCR = (1 << SPE);
}
char SPI_SlaveReceive(void)
{
	SPDR = 'S';
	while(!(SPSR & (1 << SPIF)));
	return SPDR;
}

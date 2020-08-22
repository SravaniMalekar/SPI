/*
 * Slave.c
 *
 * Created: 8/19/2020 10:57:04 PM
 * Author : Sravani Malekar
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
		if(data == 'A')
		{
			PORTB |= (1 << 5);			
		}
		else if(data == 'O')
		{
			PORTB &= ~(1 << 5);
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

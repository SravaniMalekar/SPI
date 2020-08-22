/*
 * Master.c
 *
 * Created: 8/14/2020 1:07:35 AM
 * Author : Sravani Malekar
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "UART.h"

#define DDR_SPI DDRB 
#define MOSI 3
#define MISO 4
#define SCK 5
#define SS 2

void SPI_MasterInit(void);
void SPI_MasterTransmit(char Data);
void SPI_MasterString(char *str);
char SPI_MasterReceive(void);

int main(void)
{
	USART_Init();
    SPI_MasterInit();
	serialString("hello");
	uint8_t data;
    while (1) 
    {
		//serialString("inside");
		SPI_MasterTransmit('A');
		serialString("sent");
		_delay_ms(1000);
		SPI_MasterTransmit('O');
		_delay_ms(1000);
		
		SPI_MasterString("HEYO");
		_delay_ms(1000);
		data = SPI_MasterReceive();
		serialChar(data);
		serialString("received");
	
    }
}

void SPI_MasterInit(void)
{
	DDR_SPI = (1 << MOSI)|(1 << SCK)|(1 << SS);
	SPCR = (1 << SPE)|(1 << MSTR)|(1 <<SPR0);
}
void SPI_MasterTransmit(char Data)
{
	PORTB &= ~(1 << SS);
	SPDR = Data;
	while(!(SPSR &(1 << SPIF)));
	PORTB |= (1 << SS);
}
void SPI_MasterString(char *str)
{
	while(*str)
	{
		SPI_MasterTransmit(*str++);
	}
	_delay_ms(1000);
}
char SPI_MasterReceive(void)
{
	PORTB &= ~(1 << SS);
	SPDR = 0x00;
	while(!(SPSR &(1 << SPIF)));
	PORTB |= (1 << SS);
	return SPDR;	
}

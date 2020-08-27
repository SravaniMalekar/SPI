/*
 * Master_Interrupts.c
 *
 * Created: 8/22/2020 8:25:02 PM
 * Author : Sravani Malekar
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "UART.h"

#define DDR_SPI DDRB
#define MOSI 3
#define MISO 4
#define SCK 5
#define SS 2
#define button 2
#define DDR_BUTTON DDRD
#define PORT_BUTTON PORTD

/*
void SPI_MasterInit(void);
void SPI_MasterTransmit(char Data);
void SPI_MasterString(char *str);
char SPI_MasterReceive(void);
void Interrupt0_Init(void);
*/

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

void initInterrupt0(void){
	EIMSK |= (1 << INT0);
	EICRA |= (1 << ISC00);
	sei();
}

ISR(INT0_vect)
{
	if(!(PIND & (1 << button)))
	{
		
		SPI_MasterTransmit('1');
		serialString("sent");
	}
	else
	{
		SPI_MasterTransmit('0');
		serialString("sent");
	}
}

	
int main(void)
{
	initInterrupt0();
	USART_Init();
	SPI_MasterInit();

	DDR_BUTTON |=(1 << button);
	PORT_BUTTON |= (1 << button);
	serialString("hello");
	//uint8_t data;
	while (1)
	{
		serialString("inside");

		_delay_ms(1000);

	}
}
}

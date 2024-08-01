
/*
 * SPI.c
 *
 * Created: 31/07/2024 14:27:48
 *  Author: Snake
 */ 
 #include "SPI.h"


void SPI_init()
{	
	
	DDRB |= (1<<DDB4);  //MISO COMO SALIDA
	DDRB &= ~((1<<DDB2) | (1<<DDB3) | (1<<DDB5));   //SS, MOSI, and SCK OUTPUT in master mode

	SPCR &=~ (1<<DORD);
	
	SPCR &=~ (1<<CPOL);
	SPCR &=~ (1<<CPHA);	 
	SPCR |=  (1<<SPR0);
	SPCR &=~ (1<<SPR1);
	SPSR &=~ (1<<SPI2X);
	SPCR &= ~(1<<MSTR);

	SPCR |= (1<<SPE);
}



	


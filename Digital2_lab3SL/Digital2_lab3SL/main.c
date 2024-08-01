/*
 * Digital2_lab3SL.c
 *
 * Created: 31/07/2024 12:44:36
 * Author : Snake
 */ 

#define F_CPU 16000000
#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdlib.h>

/////////////////////////////////////////////
// Librerías Secundarias
/////////////////////////////////////////////
#include "ADC/ADC.h"   // Incluir librería de ADC
#include "SPI/SPI.h"   // Incluir librería SPI

/////////////////////////////////////////////
// Variables
/////////////////////////////////////////////
uint8_t value_1 = 0, value_2 = 0, case_spi = 0;    // Variables de procesamiento

/////////////////////////////////////////////
// Función de configuración (setup)
/////////////////////////////////////////////
void setup(void);
void setup(void){
	cli();  // Apagar interrupciones
	DDRC = 0;  // Puerto C como entrada
	
	SPI_init();
	SPCR |= (1 << SPIE); // Activar interrupción SPI
	
	initADC(); // Iniciar ADC
	
	sei(); // Activar interrupciones
}

/////////////////////////////////////////////
// Función principal (main)
/////////////////////////////////////////////

int main(void)
{
	setup();
	
	while (1)
	{
		ADCSRA |= (1 << ADSC);  // Leer ADC
		_delay_ms(20);   // Retardo para evitar malos procesamientos del ATmega328P
	}
}

/////////////////////////////////////////////
// Interrupción del ADC (ISR(ADC_vect))
/////////////////////////////////////////////

ISR(ADC_vect){
	switch (case_spi){
		case 0:
		ADMUX = (ADMUX & 0xF8) | 0x06; // Seleccionar ADC6 (A6)
		value_1 = ADCH;
		case_spi = 1;
		break;
		
		case 1:
		ADMUX = (ADMUX & 0xF8) | 0x07; // Seleccionar ADC7 (A7)
		value_2 = ADCH;
		case_spi = 0;
		break;
	}
	
	ADCSRA |= (1 << ADIF); // Borrar la bandera de interrupción
}

ISR(SPI_STC_vect){
	uint8_t SPIVALOR = SPDR;
	
	if (SPIVALOR == 1)  // Si el maestro quiere ver el valor de los potenciómetros
	{
		SPDR = value_2;
	}
	
	if (SPIVALOR == 2)  // Si el maestro quiere ver el valor de los potenciómetros
	{
		SPDR = value_1;
	}
}

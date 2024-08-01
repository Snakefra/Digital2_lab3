
/*
 * SPI.h
 *
 * Created: 31/07/2024 14:27:11
 *  Author: Snake
 */ 


#ifndef SPI_H_
#define SPI_H_

#include <avr/io.h>

void SPI_init();
void SPI_tx(uint8_t data);

#endif
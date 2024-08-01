
/*
 * SPI.h
 *
 * Created: 31/07/2024 14:40:15
 *  Author: Snake
 */ 
#ifndef SPI_H_
#define SPI_H_

#include <avr/io.h>

void SPI_init();
void SPI_slaveON(uint8_t slave);
void SPI_slaveOFF(uint8_t slave);
void SPI_tx(uint8_t data);
uint8_t SPI_rx();



#endif
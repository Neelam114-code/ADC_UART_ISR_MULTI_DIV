#include "UART_char.h"
#include <stdio.h>
#include <stdint.h>

extern struct Ringbuf pot_buf;
extern struct Ringbuf sensor_buf;
extern char tx_buf[50];

void GPIOA_USART_Init(){

	GPIOA_MODER &= ~( 3 << 4 );
	GPIOA_MODER &= ~( 3 << 6 );
	//ALTERNATE FUNCTIONamk
	GPIOA_MODER |= (2 << 4);
	GPIOA_MODER |= (2 << 6);

	GPIOA_AFRL	&= ~(0xF << 8);
	GPIOA_AFRL &= ~(0xF << 12);

	GPIOA_AFRL	|= (7 << 8);
	GPIOA_AFRL |= (7 << 12);

}

void USART_Init(void)
{
		// SET BAUD RATE  BASED ON PERIFEREL BUS FREQ AND OVER SAMPLING BY 8 OR 16 AND REQUIERD BAUD RATE
		USART_BRR = 0x0683;
		//BIT LENGTH AND STOPBIT
		USART_CR1 &= ~(1 << 15);	// oversampling by  16
		USART_CR1 |= (1<<7);
		USART_CR1 &= ~(1 << 12);	//M = 0 DATA BITS 8
		USART_CR1 |= (1 << 3);	//TE set for transmit enable
		USART_CR1 |= (1 << 2);	//RE SET for receive enable
		USART_CR1 |= (1 << 13);	//UE  uart enable
		//USART_CR1 |= (1 << 5);
		*((volatile uint32_t *)0xE000E104) |= (1 << 6);//for nvic ISR

}
static uint8_t i = 0;

void USART2_IRQHandler(void){

	if(USART_SR  & (1 << 7)){

		USART_DR = tx_buf[i];
		i = (i +1) % 50;
	}
	else {

	}

}

/*
 * UART_char.h
 *
 *  Created on: Jul 30, 2026
 *      Author: nilam
 */
#include<stdio.h>
#include<stdint.h>

#ifndef UART_CHAR_H_
#define UART_CHAR_H_

#define AHB1_BASE	0x40020000
#define APB1_BASE	0x40000000
#define GPIOA_BASE	0x40020000
#define USART2_BASE	0x40004400

#define RCC_AHB1ENR (*(volatile uint32_t *)(0x40023800 + 0x30))
#define RCC_APB1ENR (*(volatile uint32_t *)(0x40023800 + 0x40))

#define GPIOA_MODER	(*(volatile uint32_t *)(GPIOA_BASE + 0x00))
#define GPIOA_AFRL (*(volatile uint32_t *)(GPIOA_BASE + 0x20))

#define USART_BRR	(*(volatile uint32_t *)(USART2_BASE + 0x08))
#define USART_DR	(*(volatile uint32_t *)(USART2_BASE + 0x04))
#define USART_SR	(*(volatile uint32_t *)(USART2_BASE + 0x00))
#define USART_CR1 	(*(volatile uint32_t *)(USART2_BASE + 0x0C))

//void RCC_USART_Init();
void GPIOA_USART_Init();
void USART2_IRQHandler(void);
void USART_Init();
//void USART_Send_data(char *);
#endif /* UART_CHAR_H_ */

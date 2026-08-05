
#include<stdio.h>
#include<stdint.h>
#include "ADC_multi_DIV.h"
#include "UART_char.h"

struct Ringbuf pot_buf = {0};
struct Ringbuf sensor_buf = {0};

uint8_t p_buf_empty = 0;
uint8_t s_buf_empty = 0;
uint8_t p_buf_full = 0;
uint8_t s_buf_full = 0;

void RCC_Init(void){
	RCC_AHB1ENR |= (1 << 0);
	RCC_APB2ENR |= (1 << 8);
	RCC_APB1ENR |= (1 << 17);
}
void GPIOA_Init(void){
	GPIOA_MODER &= ~(3U << 0);
	GPIOA_MODER |= (3U << 0);
	GPIOA_MODER &= ~(3U << 2);
	GPIOA_MODER |= (3U << 2);
}
void ADC_CH1_CH2_Init(void){

	// SAMPLING BY 15 CYCLE
	ADC_SMPR2 &= ~(7 << 3);
	ADC_SMPR2 |= (1 << 3);
	ADC_SMPR2 &= ~(7 << 6);
	ADC_SMPR2 |= (1 << 6);
	//FOR TWO CONVERSATION
	ADC_SQR1 &= ~(0xF << 20);
	ADC_SQR1 |= (0x1 << 20);
	//FOR SEQUENCE
	ADC_SQR3 &= ~(0x1F << 0);
	ADC_SQR3 |= (0x00 << 0);
	ADC_SQR3 &= ~(0x1F << 5);
	ADC_SQR3 |=	(0x01 << 5);
	ADC_CR1 |= (1 << 8 );
	ADC_CR1 |= (1 << 5);
	//FOR CONTINUOUS MODE
	//ADC_CR2 |= (1 << 1);
	//ENABLE ADC
	ADC_CR2 |= (1 << 0);
	*((volatile uint32_t *)0xE000E100) |= (1 << 18);
	//for(volatile int i = 0; i<=1000; i++);
	//start conversation
	ADC_CR2 |= (1 << 30);

}
static uint8_t channel = 1;

void ADC_IRQHandler(void){

	if(ADC_SR & (1 << 1)){

		if(channel  == 1){
			uint16_t p_data;
			if(pot_buf.head +1 != pot_buf.tail){
			p_data = ADC_DR;
			pot_buf.data[pot_buf.head] = p_data;
			pot_buf.head = (pot_buf.head +1) % 50;
			channel ^= 1;
			}
			else
				p_buf_full = 1;

		}
		else{
			if(sensor_buf.head +1 != sensor_buf.tail){
				uint16_t s_data;
				s_data = ADC_DR;
				sensor_buf.data[sensor_buf.head] = s_data;
				sensor_buf.head = (sensor_buf.head +1) % 50;
				channel ^= 1;
			}
			else s_buf_full =1;
		}

	}
}
/*
void Read_ADC_Data(){

	while (!(ADC_SR & (1 << 1)));
	uint16_t p_data;
	p_data = ADC_DR;
	pot_buf.data[pot_buf.head] = p_data;
	pot_buf.head = (pot_buf.head +1) % 50;
	ADC_SR &= ~(1 << 1);

	while (!(ADC_SR & (1 << 1)));
		uint16_t s_data;
		s_data = ADC_DR;
		sensor_buf.data[sensor_buf.head] = s_data;
		sensor_buf.head = (sensor_buf.head +1) % 50;
		ADC_SR &= ~(1 << 1);
}*/


uint16_t pot_pop_data (struct Ringbuf *pb)	{
	if(pb->head != pb->tail){
	uint16_t p_data = pb->data[pb->tail];
	pb->tail = (pb->tail +1) % 50;
	return p_data;
	}
	else {
			p_buf_empty = 1;
			return 0;
	}
}

uint16_t sensor_pop_data (struct Ringbuf *sb)	{
	if(sb->head != sb->tail){
	uint16_t s_data = sb->data[sb->tail];
	sb->tail = (sb->tail +1) % 50;
	return s_data;
	}
	else {
		s_buf_empty = 1;
		return 0;
	}
}
/*
int is_data_available(RingBuf *rb)	{
	return (rb -> head != rb -> tail);
}
int is_buf_full(RingBuf *rb)	{
	return (((rb->head +1) % buf_size) == rb->tail);
}
*/



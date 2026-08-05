
#include<stdio.h>

#ifndef ADC_MULTI_DIV_H_
#define ADC_MULTI_DIV_H_
struct Ringbuf{
	uint16_t data[50];
	volatile int head;
	volatile int tail;
};
extern struct Ringbuf pot_buf;
extern struct Ringbuf sensor_buf;
#define RCC_BASE 0x40023800
#define RCC_AHB1ENR	(*(volatile uint32_t *)(0x40023800 + 0x30))
#define RCC_APB2ENR	(*(volatile uint32_t *)(0x40023800 + 0x44))
#define GPIOA_BASE	0x40020000
#define GPIOA_MODER (*(volatile uint32_t *)(0x40020000 + 0x00))
#define ADC1_BASE 0x40012000
#define ADC_CR1		(*(volatile uint32_t *)(ADC1_BASE + 0x04))
#define ADC_CR2		(*(volatile uint32_t *)(ADC1_BASE + 0x08))
#define ADC_SR		(*(volatile uint32_t *)(ADC1_BASE + 0x00))
#define ADC_DR		(*(volatile uint32_t *)(ADC1_BASE + 0x4C))
#define ADC_SQR1	(*(volatile uint32_t *)(ADC1_BASE + 0x2C))
#define ADC_SQR3	(*(volatile uint32_t *)(ADC1_BASE + 0x34))
#define ADC_SMPR2	(*(volatile uint32_t *)(ADC1_BASE + 0x10))
void RCC_Init();
void GPIOA_Init();
void ADC_CH1_CH2_Init();
void Read_ADC_Data(void);
uint16_t pot_pop_data (struct Ringbuf *);
uint16_t sensor_pop_data (struct Ringbuf *);

#endif /* ADC1_CH1_H_ */


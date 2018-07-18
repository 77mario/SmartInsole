/*
 * shared_vars.h
 *
 *  Created on: 17 lug 2018
 *      Author: vimat
 */



extern short int timer;
extern int timer_limit;
extern int average_counter;
extern int choice;

extern uint8_t rx_buffer[3];

extern DMA_HandleTypeDef hdma_adc1;
extern ADC_HandleTypeDef hadc1;
extern TIM_HandleTypeDef htim3;
extern UART_HandleTypeDef huart1;

#define RED GPIO_PIN_15
#define GREEN GPIO_PIN_13
#define YELLOW GPIO_PIN_14


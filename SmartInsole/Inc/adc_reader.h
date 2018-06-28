/*
 * adc_reader.h
 *
 *  Created on: 26 giu 2018
 *      Author: mario
 */

#ifndef ADC_READER_H_
#define ADC_READER_H_
#include "stm32f4xx_hal.h"

int adc_read_values(uint16_t* adc_buffer,UART_HandleTypeDef* huart2);
int is_moving(uint16_t x, uint16_t y, uint16_t z);
int get_weight(uint16_t raw_value);
int check_weight(int w1, int w2, int w_back, int is_moving);
#endif /* ADC_READER_H_ */

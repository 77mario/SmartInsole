/*
 * adc_reader.h
 *
 *  Created on: 26 giu 2018
 *      Author: mario
 */

#ifndef ADC_READER_H_
#define ADC_READER_H_
#include "stm32f4xx_hal.h"

void static_read(int counter,UART_HandleTypeDef* huart);
void reset_weight();
int check_accel_static(int x, int y, int z);
int adc_read_values(uint16_t* adc_buffer,UART_HandleTypeDef* huart);
int is_moving(uint16_t x, uint16_t y, uint16_t z);
int get_weight(uint16_t raw_value);
int check_weight(int w1, int w2, int w_back, int is_moving);
#endif /* ADC_READER_H_ */

/*
 * adc_reader.h
 *
 *  Created on: 26 giu 2018
 *      Author: mario
 */

#ifndef ADC_READER_H_
#define ADC_READER_H_
#include "stm32f4xx_hal.h"

void static_read(int counter);
void dynamic_read();
void reset_weight();
int check_accel_static(int x, int y, int z);
int adc_read_values(uint16_t* adc_buffer,UART_HandleTypeDef* huart);
int adc_read_dynamic_values(uint16_t* adc_buffer);
double get_weight(uint16_t raw_value);
void calibrate(uint16_t* adc_buffer);
#endif /* ADC_READER_H_ */

/*
 * adc_reader.h
 *
 *  Created on: 26 giu 2018
 *      Author: mario
 */

#ifndef ADC_READER_H_
#define ADC_READER_H_
#include "stm32f4xx_hal.h"

void adc_read_values(uint16_t* adc_buffer,UART_HandleTypeDef* huart2);

#endif /* ADC_READER_H_ */

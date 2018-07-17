/*
 * ADC1.c
 *
 *  Created on: 17 lug 2018
 *      Author: vimat
 */


void MX_ADC1_Init(void);
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* AdcHandle);
void start_ADC();
void stop_ADC();

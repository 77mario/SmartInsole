/*
 * ADC1.c
 *
 *  Created on: 17 lug 2018
 *      Author: vimat
 */


void MX_ADC1_Init(void);
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* AdcHandle);
void start_ADC1();
void stop_ADC1();
void choice_static();
void choice_dynamic();
void choice_calibrate();
void choice_auto();

void change_to_static();
void change_to_dynamic();
void reset_tim2_counter();

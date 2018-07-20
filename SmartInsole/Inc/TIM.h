/*
 * TIM3.c
 *
 *  Created on: 17 lug 2018
 *      Author: vimat
 */

void MX_TIM2_Init(void);
void MX_TIM3_Init(void);
void MX_TIM4_Init(void);
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);
void start_TIM2();
void stop_TIM2();
void start_TIM3();
void stop_TIM3();
void start_TIM4();
void stop_TIM4();

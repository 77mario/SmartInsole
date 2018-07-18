/*
 * TIM3.c
 *
 *  Created on: 17 lug 2018
 *      Author: vimat
 */

#include "stm32f4xx_hal_tim.h"
#include "TIM3.h"
#include "shared_vars.h"


/* TIM3 init function */
void MX_TIM3_Init(void) {

	TIM_ClockConfigTypeDef sClockSourceConfig;
	TIM_SlaveConfigTypeDef sSlaveConfig;
	TIM_MasterConfigTypeDef sMasterConfig;

	htim3.Instance = TIM3;
	htim3.Init.Prescaler = 15999;
	htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim3.Init.Period = 999;
	htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	if (HAL_TIM_Base_Init(&htim3) != HAL_OK) {
		_Error_Handler(__FILE__, __LINE__);
	}

	sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
	if (HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig) != HAL_OK) {
		_Error_Handler(__FILE__, __LINE__);
	}

	sSlaveConfig.SlaveMode = TIM_SLAVEMODE_TRIGGER;
	sSlaveConfig.InputTrigger = TIM_TS_TI1F_ED;
	sSlaveConfig.TriggerFilter = 0;
	if (HAL_TIM_SlaveConfigSynchronization(&htim3, &sSlaveConfig) != HAL_OK) {
		_Error_Handler(__FILE__, __LINE__);
	}

	sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig)
			!= HAL_OK) {
		_Error_Handler(__FILE__, __LINE__);
	}


	HAL_NVIC_SetPriority(TIM3_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(TIM3_IRQn);

}



void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
	if (htim->Instance == TIM3) {
		timer++;
		if (timer >= timer_limit) {

			stop_ADC();
			set_led(YELLOW);
			reset_led(GREEN);
			reset_led(RED);
			stop_TIM3();
			static_read(average_counter/60);

			//char *msg = "Completo";

			//HAL_UART_Transmit(&huart1, (uint8_t*)msg, strlen(msg), 0xFFFF);

			UART_Receive(rx_buffer, 3);

		}
	}
}

void start_TIM3(){

	HAL_TIM_Base_Start_IT(&htim3);
}

void stop_TIM3(){

	HAL_TIM_Base_Stop_IT(&htim3);
}

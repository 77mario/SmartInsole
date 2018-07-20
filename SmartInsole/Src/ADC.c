/*
 * ADC1.c
 *
 *  Created on: 17 lug 2018
 *      Author: vimat
 */


#include "stm32f4xx_hal.h"
#include "ADC.h"

#include "shared_vars.h"
#define STATIC 1
#define DYNAMIC 0

static uint16_t adc_buffer[6];




/* ADC1 init function */
void MX_ADC1_Init(void) {

	ADC_ChannelConfTypeDef sConfig;

	/**Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion)
	 */
	hadc1.Instance = ADC1;
	hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV2;
	hadc1.Init.Resolution = ADC_RESOLUTION_12B;
	hadc1.Init.ScanConvMode = ENABLE;
	hadc1.Init.ContinuousConvMode = ENABLE;
	hadc1.Init.DiscontinuousConvMode = DISABLE;
	hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
	hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
	hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
	hadc1.Init.NbrOfConversion = 6;
	hadc1.Init.DMAContinuousRequests = ENABLE;
	hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
	if (HAL_ADC_Init(&hadc1) != HAL_OK) {
		_Error_Handler(__FILE__, __LINE__);
	}

	/**Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
	 */
	sConfig.Channel = ADC_CHANNEL_0;
	sConfig.Rank = 1;
	sConfig.SamplingTime = ADC_SAMPLETIME_480CYCLES;
	if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK) {
		_Error_Handler(__FILE__, __LINE__);
	}

	/**Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
	 */
	sConfig.Channel = ADC_CHANNEL_1;
	sConfig.Rank = 2;
	if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK) {
		_Error_Handler(__FILE__, __LINE__);
	}

	/**Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
	 */
	sConfig.Channel = ADC_CHANNEL_4;
	sConfig.Rank = 3;
	if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK) {
		_Error_Handler(__FILE__, __LINE__);
	}

	/**Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
	 */
	sConfig.Channel = ADC_CHANNEL_8;
	sConfig.Rank = 4;
	if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK) {
		_Error_Handler(__FILE__, __LINE__);
	}

	/**Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
	 */
	sConfig.Channel = ADC_CHANNEL_11;
	sConfig.Rank = 5;
	sConfig.SamplingTime = ADC_SAMPLETIME_112CYCLES;
	if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK) {
		_Error_Handler(__FILE__, __LINE__);
	}

	/**Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
	 */
	sConfig.Channel = ADC_CHANNEL_10;
	sConfig.Rank = 6;
	sConfig.SamplingTime = ADC_SAMPLETIME_480CYCLES;
	if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK) {
		_Error_Handler(__FILE__, __LINE__);
	}

}


void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* AdcHandle) {
	if (choice == 1) {
		choice_static();
	}else if(choice == 2){
		choice_dynamic();
	}else if (choice == 3) {
		choice_calibrate();
	}else if (choice == 4){
		choice_auto();
	}
}



void start_ADC1(){
	if (HAL_ADC_Start_DMA(&hadc1, (uint16_t*) &adc_buffer,
							hadc1.Init.NbrOfConversion) != HAL_OK);
}

void stop_ADC1(){

	HAL_ADC_Stop_DMA(&hadc1);
}

void choice_static(){
	average_counter = average_counter + 1;

	if (average_counter % 60 == 1) {
		int result = adc_read_values(&adc_buffer, &huart1);

		if (result == 1) {
			set_led(GREEN);
			reset_led(RED_BACK);
			reset_led(RED_FRONT);
			stop_motor();
		} else {
			set_led(RED_BACK);
			set_led(RED_FRONT);
			activate_motor(0);
			reset_led(GREEN);
		}
	}
}
void choice_dynamic(){
	average_counter = average_counter + 1;

			if (average_counter % 60 == 1) {
				int result = adc_read_dynamic_values(&adc_buffer);
				char msg2[30];
				sprintf(msg2, "RISULTATO : %d \n", result);
				//HAL_UART_Transmit(&huart1, (uint8_t*) msg2, strlen(msg2), HAL_MAX_DELAY);

				if (result == 1) {
					dynamic_read();
					reset_weight();

				} else if (result == 0){
					activate_motor(1);
				}
			}
}

void choice_calibrate(){
	calibrate(&adc_buffer);
	stop_ADC1();

	UART_Receive(rx_buffer, 3);
}
void choice_auto(){
	if(auto_state == DYNAMIC){
		choice_dynamic();
		int r = check_accel_static(adc_buffer[3],adc_buffer[4],adc_buffer[5]);
		if(r == 0){
			reset_tim2_counter();
		}
	} else {
		choice_static();
	}
}

void change_to_static(){
	stop_dynamic();
	reset_tim2_counter();
	start_static();
	auto_state = STATIC;
}
void change_to_dynamic(){
	timer_limit = tim2_counter;
	stop_static();
	start_TIM2();
	reset_tim2_counter();
	start_dynamic();
	auto_state = DYNAMIC;
}
void reset_tim2_counter(){
	tim2_counter = 0;
}

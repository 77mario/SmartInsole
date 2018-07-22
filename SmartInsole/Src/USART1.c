/*
 * USART1.c
 *
 *  Created on: 17 lug 2018
 *      Author: vimat
 */


#include "stm32f4xx_hal.h"
#include "USART1.h"
#include "shared_vars.h"


/* USART1 init function */
void MX_USART1_UART_Init(void) {

	huart1.Instance = USART1;
	huart1.Init.BaudRate = 9600;
	huart1.Init.WordLength = UART_WORDLENGTH_8B;
	huart1.Init.StopBits = UART_STOPBITS_1;
	huart1.Init.Parity = UART_PARITY_NONE;
	huart1.Init.Mode = UART_MODE_TX_RX;
	huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart1.Init.OverSampling = UART_OVERSAMPLING_16;
	if (HAL_UART_Init(&huart1) != HAL_OK) {
		_Error_Handler(__FILE__, __LINE__);
	}

}


void HAL_UART_RxCpltCallback(UART_HandleTypeDef* huart) {
	choice = rx_buffer[0] - '0';
	average_counter = 0;
	timer = 0;
	if (choice == 1) {
		//statica
		 int time = (rx_buffer[1] - '0') * 10 + (rx_buffer[2] - '0');
		 start_static(time);

	}else if (choice == 2){
		//dinamica
		int reset = rx_buffer[2] - '0';
		if (reset == 1){
			stop_dynamic();

		} else {
			start_dynamic();
		}

	}else if (choice == 3) {
		//calibrazione

		start_ADC1();
	} else if (choice == 4){
		//automatica
		int reset = rx_buffer[2] - '0';
				if (reset == 1){
					stop_auto();

				} else {
					start_auto();
				}

	}else {
		UART_Receive();
	}
}

void start_static(int time){
	reset_led(YELLOW);

	timer_limit = time;
	reset_weight();
	if(choice != 4){
		start_TIM3();
		}
	start_ADC1();
}
void start_dynamic(){
	reset_weight();
	start_ADC1();
	reset_led(YELLOW);
	reset_led(GREEN);
	reset_led(RED_BACK);
	reset_led(RED_FRONT);
	UART_Receive();
}
void stop_dynamic(){
	stop_ADC1();
	set_led(YELLOW);
	reset_led(GREEN);
	reset_led(RED_BACK);
	reset_led(RED_FRONT);
	UART_Receive();
}
void start_auto(){
	start_dynamic();
	tim2_counter = 0;
	start_TIM2();
}
void stop_auto(){
	stop_TIM2();
	stop_ADC1();
	set_led(YELLOW);
	reset_led(GREEN);
	reset_led(RED_BACK);
	reset_led(RED_FRONT);
	average_counter = 0;
	UART_Receive( );
}

void UART_Receive(){

	HAL_UART_Receive_IT(&huart1, rx_buffer, 3);
}



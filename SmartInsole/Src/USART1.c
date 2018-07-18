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

		start_ADC();
	} else {
	UART_Receive(rx_buffer, 3);
	}

	//HAL_UART_Transmit(&huart1, (uint8_t*)rx_buffer, sizeof(rx_buffer), 0xFFFF);

}

void start_static(int time){
	reset_led(YELLOW);

	timer_limit = time;
	reset_weight();
	start_TIM3();
	start_ADC();
}
void start_dynamic(){
	reset_weight();
	start_ADC();
	reset_led(YELLOW);
	set_led(GREEN);
	reset_led(RED);
	UART_Receive( rx_buffer, 3);
}
void stop_dynamic(){
	stop_ADC();
	set_led(YELLOW);
	reset_led(GREEN);
	reset_led(RED);
	UART_Receive( rx_buffer, 3);
}

void UART_Receive(uint8_t *pData, uint16_t Size){

	HAL_UART_Receive_IT(&huart1, rx_buffer, 3);
}

void UART_Transmit(uint8_t *msg){
	HAL_UART_Transmit(&huart1, (uint8_t*)msg, strlen(msg), 0xFFFF);
}

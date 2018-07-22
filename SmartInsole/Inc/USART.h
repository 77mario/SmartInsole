/*
 * USART1.c
 *
 *  Created on: 17 lug 2018
 *      Author: vimat
 */

void MX_USART1_UART_Init(void);
void HAL_UART_RxCpltCallback(UART_HandleTypeDef* huart);
void start_static(int time);
void start_dynamic();
void stop_dynamic();
void start_auto();
void stop_auto();
void UART_Receive();
void stop_static();

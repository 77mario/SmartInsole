/*
 * USART1.c
 *
 *  Created on: 17 lug 2018
 *      Author: vimat
 */

void MX_USART1_UART_Init(void);
void HAL_UART_RxCpltCallback(UART_HandleTypeDef* huart);
void UART_Receive(uint8_t *pData, uint16_t Size);

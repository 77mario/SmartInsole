/*
 * adc_reader.c
 *
 *  Created on: 26 giu 2018
 *      Author: mario
 */
#include "adc_reader.h"

void adc_read_values(uint16_t* adc_buffer,UART_HandleTypeDef* huart2){
// TODO
char msg1[1000];

uint16_t flexi_1 = adc_buffer[0];
uint16_t flexi_2 = adc_buffer[1];
uint16_t flexi_3 = adc_buffer[2];
uint16_t x = adc_buffer[3];
uint16_t y = adc_buffer[4];
uint16_t z = adc_buffer[5];

sprintf(msg1, "F1: %d F2:%d F3:%d x: %d y:%d z:%d \r\n", flexi_1,flexi_2,flexi_3,x,y,z);
HAL_UART_Transmit(huart2, (uint8_t*)msg1, strlen(msg1), HAL_MAX_DELAY);

if(x<2100 && x>1900 && y>2000 && y<2200 && z>2400 && z<2500){
	  //HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5,GPIO_PIN_SET);

}
else{
	  //HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5,GPIO_PIN_RESET);

}
char *msg2 = "----------------------------------- \r\n";
HAL_UART_Transmit(&huart2, (uint8_t*) msg2, strlen(msg2), HAL_MAX_DELAY);

}

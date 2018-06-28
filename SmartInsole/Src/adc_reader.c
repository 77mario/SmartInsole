/*
 * adc_reader.c
 *
 *  Created on: 26 giu 2018
 *      Author: mario
 */
#include "adc_reader.h"

double TOL = 5.0;

int adc_read_values(uint16_t* adc_buffer,UART_HandleTypeDef* huart2){
// TODO
	char msg1[1000];

	uint16_t flexi_1 = adc_buffer[0];
	uint16_t flexi_2 = adc_buffer[1];
	uint16_t flexi_3 = adc_buffer[2];
	uint16_t x = adc_buffer[3];
	uint16_t y = adc_buffer[4];
	uint16_t z = adc_buffer[5];

	int w1 = get_weight(flexi_1);
	int w2 = get_weight(flexi_2);
	int w3 = get_weight(flexi_3);

	int result = check_weight(w1, w2, w3, is_moving(x,y,z));

	sprintf(msg1, "F1: %d F2:%d F3:%d W1: %d W2:%d W3:%d x: %d y:%d z:%d R:%d \r\n", flexi_1,flexi_2,flexi_3,w1,w2,w3,x,y,z,result);
	HAL_UART_Transmit(huart2, (uint8_t*)msg1, strlen(msg1), HAL_MAX_DELAY);
	return result;
	//char *msg2 = "----------------------------------- \r\n";
	//HAL_UART_Transmit(&huart2, (uint8_t*) msg2, strlen(msg2), HAL_MAX_DELAY);

}

// 0 = FERMO
// 1 = MOVIMENTO
int is_moving(uint16_t x, uint16_t y, uint16_t z){
	return 0;
}

//y = -15.3846 x + 50.7692 ---- 2 - 3.30
//y = -62.5 x + 136.25
int get_weight(uint16_t raw_value){
	return -28.85*(raw_value*3.3/4095) +95.4;
}

// 0 = PESO SBAGLIATO
// 1 = PESO OK
int check_weight(int w1, int w2, int w_back, int is_moving){
	int w_front = w1+w2;
	int w_tot = w_front + w_back;

	double w_front_perc = w_front*100/w_tot;
	double w_back_perc = w_back*100/w_tot;
	if(is_moving == 0){
		if(w_front_perc + TOL > 50 || w_back_perc + TOL > 60){
			return 0;
		} else {
			return 1;
		}

	} else {
		if(w_front_perc + TOL > 60 || w_back_perc + TOL > 50){
			return 0;
		} else {
			return 1;
		}

	}

}




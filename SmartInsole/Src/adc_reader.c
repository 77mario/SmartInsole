/*
 * adc_reader.c
 *
 *  Created on: 26 giu 2018
 *      Author: mario
 */

#include "adc_reader.h"
#include "shared_vars.h"
#include "utils.h"
static int X_STATIC = 2000;
static int Y_STATIC = 2000;
static int Z_STATIC = 2000;
int MAX_MOV = 110;
static double f1tot = 0.0;
static double f2tot = 0.0;
static double f3tot = 0.0;
static int passo_back = 0;
static int passo_av = 0;

void calibrate(uint16_t* adc_buffer) {
	X_STATIC = adc_buffer[3];
	Y_STATIC = adc_buffer[4];
	Z_STATIC = adc_buffer[5];

}

void static_read(int counter) {

	char msg1[1000];
	f1tot = f1tot / counter;
	f2tot = f2tot / counter;
	f3tot = f3tot / counter;
	int f2perc = f2tot * 100 / (f1tot + f2tot + f3tot);
	int f3perc = f3tot * 100 / (f1tot + f2tot + f3tot);
	int f1perc = 100 - f2perc - f3perc;

	if (f1tot < 0.2 && f2tot < 0.2 && f3tot < 0.2) {
		return;
	}
	sprintf(msg1,
			"{\"code\" : \"1\", \"weight_perc\" : {\"avan_sx\":%d,\"avan_dx\":%d,\"back\":%d}, \"weight_tot\" : %.2f, \"time\": %d}\n",
			f1perc, f2perc, f3perc, (f1tot + f2tot + f3tot), timer_limit);
	HAL_UART_Transmit(&huart1, (uint8_t*) msg1, strlen(msg1), 0xFFFF);

}
void dynamic_read() {

	char msg1[1000];
	int f2perc = f2tot * 100 / (f1tot + f2tot + f3tot);
	int f3perc = f3tot * 100 / (f1tot + f2tot + f3tot);
	int f1perc = 100 - f2perc - f3perc;
	if(f3perc > 40 && f3perc <50){
		set_led(GREEN);
	} else {
		if(f3perc >= 50){
			set_led(RED_BACK);
		} else {
			set_led(RED_FRONT);
		}
		activate_motor(1);

	}
	sprintf(msg1,
			"{\"code\" : \"2\", \"weight_perc\" : {\"avan_sx\":%d,\"avan_dx\":%d,\"back\":%d}}\n",
			f1perc, f2perc, f3perc);
	HAL_UART_Transmit(&huart1, (uint8_t*) msg1, strlen(msg1), 0xFFFF);

}
void reset_weight() {
	f1tot = 0.0;
	f2tot = 0.0;
	f3tot = 0.0;
}
int adc_read_values(uint16_t* adc_buffer, UART_HandleTypeDef* huart) {
// TODO
	char msg1[1000];
	uint16_t flexi_1 = adc_buffer[0];
	uint16_t flexi_2 = adc_buffer[1];
	uint16_t flexi_3 = adc_buffer[2];
	uint16_t x = adc_buffer[3];
	uint16_t y = adc_buffer[4];
	uint16_t z = adc_buffer[5];

	double w1 = get_weight(flexi_1);
	double w2 = get_weight(flexi_2);
	double w3 = get_weight(flexi_3);
	if(w1 == 0.0 && w2 == 0.0 && w3 == 0.0 && choice == 4){
		change_to_dynamic();
	}
	f1tot = f1tot + w1;
	f2tot = f2tot + w2;
	f3tot = f3tot + w3;

	int result = check_accel_static(x, y, z);

	return result;

}
int adc_read_dynamic_values(uint16_t* adc_buffer) {

	uint16_t flexi_1 = adc_buffer[0];
	uint16_t flexi_2 = adc_buffer[1];
	uint16_t flexi_3 = adc_buffer[2];

	double w1 = get_weight(flexi_1);
	double w2 = get_weight(flexi_2);
	double w3 = get_weight(flexi_3);

	if (w3 > 0) {
		passo_back = 1;
		f3tot = get_max(w3, f3tot);
	}
	if ((w2 > 0 || w1 > 0) && passo_back == 1) {
		f2tot = get_max(w2, f2tot);
		f1tot = get_max(w1, f1tot);
		passo_av = 1;
	}
;
	if (passo_av == 1 && passo_back == 1 && w1 == 0 && w2 == 0 && w3 == 0) {
		passo_back = 0;
		passo_av = 0;
		return 1;
	} else if (passo_back == 1 && passo_av == 0 && w3 == 0) {
		passo_back = 0;
		reset_weight();
		return 0;

	}
	reset_led(GREEN);
	reset_led(RED_BACK);
	reset_led(RED_FRONT);
	return -1;
}

// 0 SBAGLIATO
// 1 OK
int check_accel_static(int x, int y, int z) {
	if (       x > X_STATIC + MAX_MOV || x < X_STATIC - MAX_MOV
			|| y > Y_STATIC + MAX_MOV || y < Y_STATIC - MAX_MOV
			|| z > Z_STATIC + MAX_MOV || z < Z_STATIC - MAX_MOV) {
		return 0;
	}
	return 1;
}

double get_weight(uint16_t raw_value) {
	double w;
	double voltage = (raw_value*3.3/4095);
	if (voltage > 1.8) {
		w = 5.57576 - 1.74242 *voltage;
	} else {
		w  = 12.9746 - 5.67797 *voltage;
	}
	if (voltage > 3.10) {
		return 0.0;
	}
	return w;
}




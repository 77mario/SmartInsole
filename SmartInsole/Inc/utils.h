/*
 * utils.c
 *
 *  Created on: 17 lug 2018
 *      Author: vimat
 */


void init_peripherals();
void SystemClock_Config(void) ;
void _Error_Handler(char *file, int line);
void assert_failed(uint8_t* file, uint32_t line);

#define Error_Handler() _Error_Handler(__FILE__, __LINE__)

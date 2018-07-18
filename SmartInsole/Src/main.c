/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************

 */



/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "shared_vars.h"
#include "main.h"
#include "ADC1.h"
#include "DMA.h"
#include "GPIO.h"
#include "TIM3.h"
#include "USART1.h"
#include "utils.h"


/* USER CODE BEGIN Includes */

#include "adc_reader.h"
#include "stm32f4xx_hal_tim.h"

ADC_HandleTypeDef hadc1;
TIM_HandleTypeDef htim3;
UART_HandleTypeDef huart1;
DMA_HandleTypeDef hdma_adc1;

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/
char *msg = "Hello STM32 Lovers! Start Transmitting with UART.\r\n";


short int timer;
int timer_limit;
int average_counter;
int choice = 0;

uint8_t rx_buffer[3];

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/


/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/

/* USER CODE END PFP */

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 *
 * @retval None
 */
int main(void) {


	init_peripherals();

	//HAL_UART_Transmit(&huart1, (uint8_t*)tx_buffer, strlen(tx_buffer), 0xFFFF);
	UART_Receive(rx_buffer, 3);
	set_led(YELLOW);

	/* USER CODE END 2 */

	/* Infinite loop */
	/* USER CODE BEGIN WHILE */
	while (1) {

		/* USER CODE END WHILE */

		/* USER CODE BEGIN 3 */
		//if(HAL_ADC_Start_DMA(&hadc1, (uint16_t*)&adc_buffer, hadc1.Init.NbrOfConversion) != HAL_OK);
//	  HAL_Delay(500);
// HAL_ADC_Stop_DMA(&hadc1);
	}
	/* USER CODE END 3 */

}




/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

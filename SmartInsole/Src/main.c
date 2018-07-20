/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************

 */



/* Includes ------------------------------------------------------------------*/

#include "stm32f4xx_hal.h"
#include "shared_vars.h"
#include "TIM.h"
#include "main.h"
#include "ADC1.h"
#include "DMA.h"
#include "GPIO.h"
#include "USART1.h"
#include "utils.h"


/* USER CODE BEGIN Includes */

#include "adc_reader.h"
#include "stm32f4xx_hal_tim.h"

ADC_HandleTypeDef hadc1;
TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim3;
TIM_HandleTypeDef htim4;
UART_HandleTypeDef huart1;
DMA_HandleTypeDef hdma_adc1;

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/
char *msg = "Hello STM32 Lovers! Start Transmitting with UART.\r\n";


short int timer = 0;
int timer_limit = 0;
int average_counter = 0;
int choice = 0;
int motor_time = 0;
int motor_time_limit = 0;

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
	UART_Receive(rx_buffer, 3);
	set_led(YELLOW);


	while (1) {


	}

}




/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

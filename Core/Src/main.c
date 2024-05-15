/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "spi.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
/* Buffer used for transmission */
uint8_t aTxBuffer[16] = { 0x47 };
//
///* Buffer used for reception */
//UartData TTY;
uint8_t aRxBuffer[16]= { 0, 0, 0, 0,
						 0, 0, 0, 0,
						 0, 0, 0, 0,
						 0, 0, 0, 0 };
//
//uint8_t RxData[32];
//uint8_t *pRxData = &TTY.RxData[0];
//uint8_t TxData[16]= { 34, 35, 36, 37,
//						 34, 35, 36, 37,
//						 34, 35, 36, 37,
//						 34, 35, 36, 37 };

//uint8_t TTY.TxData[16]= { 34, 35, 36, 37,
//						 34, 35, 36, 37,
//						 34, 35, 36, 37,
//						 34, 35, 36, 37 };

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_SPI1_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */
  HAL_GPIO_WritePin( GPIOA, GPIO_PIN_4, 1);
  Running_UART_Comm_Init();
//  if(HAL_UART_Receive_IT (&huart1, NULL,1)!= HAL_OK)
//  {
//    Error_Handler();
//  }
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	  HAL_GPIO_WritePin( GPIOA, GPIO_PIN_4, 0);
	  aTxBuffer[0] = 0x78;
	  if(HAL_SPI_Transmit(&hspi1, aTxBuffer, 1, 1000)!= HAL_OK)
  	  {
 	    Error_Handler();
  	  }
	  HAL_GPIO_WritePin( GPIOA, GPIO_PIN_4, 1);


	  HAL_Delay(2000);
	  HAL_GPIO_WritePin( GPIOA, GPIO_PIN_4, 0);
	  aTxBuffer[0] = 0x47;
	  if(HAL_SPI_TransmitReceive (&hspi1, aTxBuffer, aRxBuffer, 16, 1000)!= HAL_OK)
	  {
		Error_Handler();
	  }
	  HAL_GPIO_WritePin( GPIOA, GPIO_PIN_4, 1);


	  HAL_Delay(2000);

	  HAL_GPIO_WritePin( GPIOA, GPIO_PIN_4, 0);
		aTxBuffer[0] = 0x46;
		aTxBuffer[1] = 0x63;
		aTxBuffer[2] = 0x20;
		aTxBuffer[3] = 0x89;
		aTxBuffer[4] = 0x80;
		aTxBuffer[5] = 0x07;
		aTxBuffer[6] = 0xBC;
	  if(HAL_SPI_Transmit(&hspi1, aTxBuffer, 7, 1000)!= HAL_OK)
		  {
		Error_Handler();
		  }
	  HAL_GPIO_WritePin( GPIOA, GPIO_PIN_4, 1);

	  HAL_Delay(2000);

	  HAL_GPIO_WritePin( GPIOA, GPIO_PIN_4, 0);
		aTxBuffer[0] = 0x47;
		aTxBuffer[1] = 0;
		aTxBuffer[2] = 0;
		aTxBuffer[3] = 0;
		aTxBuffer[4] = 0;
		aTxBuffer[5] = 0;
		aTxBuffer[6] = 0;
	  if(HAL_SPI_TransmitReceive (&hspi1, aTxBuffer, aRxBuffer, 16, 1000)!= HAL_OK)
	  {
		Error_Handler();
	  }
	  HAL_GPIO_WritePin( GPIOA, GPIO_PIN_4, 1);
	  while (1)
	  {
	  HAL_Delay(2000);
	  HAL_GPIO_WritePin( GPIOA, GPIO_PIN_4, 0);
	  aTxBuffer[0] = 0x6C;
	  if(HAL_SPI_Transmit(&hspi1, aTxBuffer, 1, 1000)!= HAL_OK)
  	  {
 	    Error_Handler();
  	  }
	  HAL_GPIO_WritePin( GPIOA, GPIO_PIN_4, 1);


	  HAL_Delay(2000);
		aRxBuffer[0] = 0;
		aRxBuffer[1] = 0;
		aRxBuffer[2] = 0;
		aRxBuffer[3] = 0;
		aRxBuffer[4] = 0;
		aRxBuffer[5] = 0;
		aRxBuffer[6] = 0;
	  HAL_GPIO_WritePin( GPIOA, GPIO_PIN_4, 0);
		aTxBuffer[0] = 0x43;
		aTxBuffer[1] = 0;
		aTxBuffer[2] = 0;
		aTxBuffer[3] = 0;
		aTxBuffer[4] = 0;
		aTxBuffer[5] = 0;
		aTxBuffer[6] = 0;
	  if(HAL_SPI_TransmitReceive (&hspi1, aTxBuffer, aRxBuffer, 6, 1000)!= HAL_OK)
	  {
		Error_Handler();
	  }
	  HAL_GPIO_WritePin( GPIOA, GPIO_PIN_4, 1);


	  HAL_Delay(500);
//	  if(HAL_UART_Transmit(&huart1, (uint8_t *)TxData,16,300)!= HAL_OK)
//	  {
//	    Error_Handler();
//	  }
//	  if(HAL_UART_Transmit_IT (&huart1, (uint8_t *)TxData,16)!= HAL_OK)
//	  {
//	    Error_Handler();
//	  }
//	  char * result = strstr(RxData , "admin" );
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 25;
  RCC_OscInitStruct.PLL.PLLN = 160;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

PUTCHAR_PROTOTYPE
{
  /* Place your implementation of fputc here */
  /* e.g. write a character to the USART1 and Loop until the end of transmission */
	HAL_UART_Transmit(COMM_PARAM_UART, (uint8_t *)&ch, 1, 0xFFFF);

  return ch;
}

/**
  * @brief  Tx Transfer completed callback
  * @param  UartHandle: UART handle.
  * @note   This example shows a simple way to report end of IT Tx transfer, and
  *         you can add your own implementation.
  * @retval None
  */
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *UartHandle)
{
  /* Turn LED1 on: Transfer in transmission process is correct */
	 HAL_GPIO_WritePin( GPIOA, GPIO_PIN_4, 1);
}

/**
  * @brief  Rx Transfer completed callback
  * @param  UartHandle: UART handle
  * @note   This example shows a simple way to report end of IT Rx transfer, and
  *         you can add your own implementation.
  * @retval None
  */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *UartHandle)
{
	Running_UART_Rx_Process();
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

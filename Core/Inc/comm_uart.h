/*
 * comm_uart.h
 *
 *  Created on: Dec 23, 2023
 *      Author: blobby
 */

#ifndef INC_COMM_UART_H_
#define INC_COMM_UART_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
//#include "main.h"

#include "usart.h"

/* USER CODE BEGIN Includes */

#ifndef COMM_PARAM_UART
#define COMM_PARAM_UART    (&huart1)
#endif


typedef enum {
	TTY_RX_CR,
	TTY_RX_DONE,
	TTY_RX_PENDING,
	TTY_TX_DONE
} state_uart_t;



/* End ADS1114 state machine structures */

/**
 * @brief   Named return values
 */
//enum {
//    TTY_RX_CR          	=  0,       	/**< everything was fine */
//	TTY_RX_DONE      	= -1,       	/**< I2C communication failed */
////	ADS101X_I2CBUSY     = -2,       	/**< I2C communication failed */
////    ADS101X_NODEV       = -3,       	/**< no ADS101X device found on the bus */
////    ADS101X_NODATA      = -4        	/**< no data available */
//};

/**
 * @brief   ADS101x/111x input data
 */
typedef struct tty_data {
	state_uart_t RxStatus;
	state_uart_t TxStatus;
	uint8_t RxData[32];
	uint8_t TxData[32];
	uint8_t *pRxData;
	uint8_t *pTxData;
} tty_data_t;
/* USER CODE END Includes */

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

void Running_UART_Rx_Process(void);
void Running_UART_Comm_Init(void);

#endif /* INC_COMM_UART_H_ */

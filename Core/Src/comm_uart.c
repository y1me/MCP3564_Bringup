/*
 * comm_uart.c
 *
 *  Created on: Dec 23, 2023
 *      Author: blobby
 */
#include "comm_uart.h"


tty_data_t UART_data;

void UART_Rx_Process(tty_data_t *data)
{
	if (data->pRxData == NULL) {
		data->pRxData = &data->RxData[0];
	}

	if(HAL_UART_Receive_IT (COMM_PARAM_UART, data->pRxData,1)!= HAL_OK) {
		Error_Handler();
	}

	if (*(data->pRxData-1) == '\r') {
		data->RxStatus = TTY_RX_CR;
	}

	if (data->pRxData > &data->RxData[31]) {
		data->pRxData = &data->RxData[0];
	}
	else {
		*data->pRxData++;
	}
}

void UART_Comm_Init(tty_data_t *data)
{
	data->RxStatus = TTY_RX_PENDING;
	data->pRxData = &data->RxData[0];
	if(HAL_UART_Receive_IT (COMM_PARAM_UART, data->pRxData,1)!= HAL_OK) {
		Error_Handler();
	}
}

void Running_UART_Comm_Init(void)
{
	UART_Comm_Init(&UART_data);
}

void Running_UART_Rx_Process(void)
{
	UART_Rx_Process(&UART_data);
}

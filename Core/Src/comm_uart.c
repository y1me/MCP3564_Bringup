/*
 * comm_uart.c
 *
 *  Created on: Dec 23, 2023
 *      Author: blobby
 */
#include "comm_uart.h"
#include "stdio.h"
#include "string.h"


tty_data_t UART_data;

char comm_arr[NUMBER_OF_COMMAND][MAX_COMMAND_SIZE];
char *pcomm_arr = &comm_arr[0];

void funcB1();
void funcAzA();

stringcase_t cases [] =
{ { "B1", funcB1 }
, { "AzA", funcAzA }
};

void myswitch( char* token ) {
  for( stringcase_t* pCase = cases
     ; pCase != cases + sizeof( cases ) / sizeof( cases[0] )
     ; pCase++ )
  {
    if( 0 == strcmp( pCase->string, token ) ) {
       (*pCase->func)();
       break;
    }
  }

}

void UART_Clear_Rx_Buffer(tty_data_t *data)
{
	for (int i = 0; i < UART_BUFF_RX_SIZE; ++i)
	  {
		data->RxData[i] = 0;
	  }
}

void UART_Rx_Process(tty_data_t *data)
{
	if (data->pRxData == NULL) {
		data->pRxData = &data->RxData[0];
	}

	if(HAL_UART_Receive_IT (COMM_PARAM_UART, data->pRxData,1)!= HAL_OK) {
		Error_Handler();
	}

	if (*(data->pRxData-1) == '\r') {
		printf("Hello World\n\r");
		data->RxStatus = TTY_RX_CR;
	}
	else {

		if (data->pRxData > &data->RxData[31]) {
			data->pRxData = &data->RxData[0];
		}
		else {
			*data->pRxData++;
		}
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

void Receive_UART_Rx_Command(tty_data_t *data)
{
	if (data->RxStatus == TTY_RX_CR)
	{
		data->RxStatus = TTY_RX_DONE;
		strncpy( pcomm_arr, data->RxData,(data->pRxData - &data->RxData[0])-1);
		pcomm_arr += MAX_COMMAND_SIZE;
		data->pRxData = &data->RxData[0];
		*data->pRxData = 0;
	}

}

void Process_UART_Rx_Command(void)
{
	Receive_UART_Rx_Command(&UART_data);
}

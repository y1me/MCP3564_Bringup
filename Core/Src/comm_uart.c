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
Command_data_t COMMAND_data;

void funcB1() {
	printf("Valid Command B1 executed\n\r");
}
void funcAzA(){
	printf("Valid Command AzA executed\n\r");
}

stringcase_t cases [] =
{ { "B1", funcB1 }
, { "AzA", funcAzA }
};

void COMMAND_Process( Command_data_t *Cdata ) {
	for( stringcase_t* pCase = cases
	 ; pCase != cases + sizeof( cases ) / sizeof( cases[0] )
	 ; pCase++ )
	{
		if( 0 == strcmp( pCase->string, Cdata->pCommandToProcess ) ) {
		   (*pCase->func)();
		   break;
		}
	}
	if (Cdata->pCommandToProcess == &Cdata->comm_arr[31] && &Cdata->comm_arr[31] != Cdata->pCommandToStore) {
		for(int idx=0; idx<MAX_COMMAND_SIZE;idx++) {
			*Cdata->pCommandToProcess = '\0';
			*Cdata->pCommandToProcess++;
		}
		Cdata->pCommandToProcess = &Cdata->comm_arr[0];
	}
	else if (Cdata->pCommandToProcess != Cdata->pCommandToStore) {
		for(int idx=0; idx<MAX_COMMAND_SIZE;idx++) {
			*Cdata->pCommandToProcess = '\0';
			*Cdata->pCommandToProcess++;
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

	if (*data->pRxData == '\r') {
		printf("Command received\n\r");
		data->RxStatus = TTY_RX_CR;
		Process_UART_Rx_Command();
	}
	else {

		if (data->pRxData > &data->RxData[31]) {
			data->pRxData = &data->RxData[0];
		}
		else {
			*data->pRxData++;
		}
	}

	if(HAL_UART_Receive_IT (COMM_PARAM_UART, data->pRxData,1)!= HAL_OK) {
		Error_Handler();
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

void COMMAND_Data_Init(Command_data_t *data)
{
	data->CommandStatus = COMMAND_EMPTY;
	data->pCommandToStore = &data->comm_arr[0];
	data->pCommandToProcess = &data->comm_arr[0];

}

void Running_UART_Comm_Init(void)
{
	UART_Comm_Init(&UART_data);
	COMMAND_Data_Init(&COMMAND_data);
}

void Running_UART_Rx_Process(void)
{
	UART_Rx_Process(&UART_data);
}

void Running_COMMAND_Process(void)
{
	COMMAND_Process(&COMMAND_data);
}

void Receive_UART_Rx_Command(tty_data_t *data, Command_data_t *Cdata)
{
	if (data->RxStatus == TTY_RX_CR){
		strncpy( Cdata->pCommandToStore, data->RxData,(data->pRxData - &data->RxData[0]));
		if (Cdata->pCommandToStore == &Cdata->comm_arr[31]) {
			Cdata->pCommandToStore = &Cdata->comm_arr[0];
		}
		else {
			Cdata->pCommandToStore += MAX_COMMAND_SIZE;
		}
		data->pRxData = &data->RxData[0];
		*data->pRxData = 0;
		data->RxStatus = TTY_RX_DONE;
	}

}

void Process_UART_Rx_Command(void)
{
	Receive_UART_Rx_Command(&UART_data, &COMMAND_data);
}

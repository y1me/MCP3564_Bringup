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

void funcB1(const char *arg) {
	printf("Valid Command B1 executed\n");
	printf("%s\n", arg);

}
void funcAzA(const char *arg){
	printf("Valid Command AzA executed\n");
	printf("%s\n",arg);
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
		   (*pCase->func)(Cdata->pArgToProcess);
		   break;
		}
	}
	if (Cdata->pCommandToProcess == &Cdata->comm_array[31] && &Cdata->comm_array[31] != Cdata->pCommandToStore) {
		for(int idx=0; idx<MAX_COMMAND_SIZE;idx++) {
			*Cdata->pCommandToProcess = '\0';
			*Cdata->pCommandToProcess++;
			*Cdata->pArgToProcess = '\0';
			*Cdata->pArgToProcess++;
		}
		Cdata->pCommandToProcess = &Cdata->comm_array[0];
		Cdata->pArgToProcess = &Cdata->arg_array[0];
	}
	else if (Cdata->pCommandToProcess != Cdata->pCommandToStore) {
		for(int idx=0; idx<MAX_COMMAND_SIZE;idx++) {
			*Cdata->pCommandToProcess = '\0';
			*Cdata->pCommandToProcess++;
			*Cdata->pArgToProcess = '\0';
			*Cdata->pArgToProcess++;
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
	data->pCommandToStore = &data->comm_array[0];
	data->pCommandToProcess = &data->comm_array[0];
	data->pArgToStore = &data->arg_array[0];
	data->pArgToProcess = &data->arg_array[0];

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
	char *token;
	if (data->RxStatus == TTY_RX_CR){
		*data->pRxData = NULL;
		token = strtok(&data->RxData[0]," ");
		//token =
		strncpy( Cdata->pCommandToStore, token, MAX_COMMAND_SIZE);
		token = strtok(NULL," ");
		strncpy( Cdata->pArgToStore, token, MAX_COMMAND_SIZE);
		data->pRxData = &data->RxData[0];
		for(int idx=0; idx<MAX_COMMAND_SIZE;idx++) {
			*data->pRxData = '\0';
			*data->pRxData++;
		}
		if (Cdata->pCommandToStore == &Cdata->comm_array[31]) {
			Cdata->pCommandToStore = &Cdata->comm_array[0];
			Cdata->pArgToStore = &Cdata->arg_array[0];
		}
		else {
			Cdata->pCommandToStore += MAX_COMMAND_SIZE;
			Cdata->pArgToStore += MAX_COMMAND_SIZE;
		}
		data->pRxData = &data->RxData[0];
		data->RxStatus = TTY_RX_DONE;
	}

}

void Process_UART_Rx_Command(void)
{
	Receive_UART_Rx_Command(&UART_data, &COMMAND_data);
}

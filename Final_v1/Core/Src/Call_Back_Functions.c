/*
 * Call_Back_Functions.c
 *
 *  Created on: Mar 3, 2024
 *      Author: nours
 */
#include "main.h"
#include "stm32f4xx_hal.h"
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "Call_Back_Functions.h"
#include "App_Tasks.h"
#include "Buzzer.h"
#include "LCD_I2C.h"


extern TaskHandle_t Handle_Car_Control;
extern TaskHandle_t Handle_Esp_Periodic;
extern TaskHandle_t Handle_Send_ESP_Status;
extern TaskHandle_t Handle_Recieve_ESP_Status;

extern UART_HandleTypeDef huart3;

extern UART_HandleTypeDef huart6;
extern UART_HandleTypeDef huart4;

extern volatile char Received_Char_Bluetooth;
extern volatile char Received_Char_ESP;


uint32_t edges_counter = 0;



/*Func will Called if there is a char Recieved,Then give notify to specific task
 *  it will switch to the task control car */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	//static portBASE_TYPE xHigherPriorityTaskWoken;

	if(huart->Instance == USART3)
	{

		/*Give the Notification to the CarControl task*/
		xTaskNotifyFromISR(Handle_Car_Control,NULL,eNoAction,NULL);
		HAL_UART_Receive_IT(&huart3, &Received_Char_Bluetooth, 1);
		//portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
	}
	else if(huart->Instance == USART6)
	{
		xTaskNotifyFromISR(Handle_Recieve_ESP_Status, NULL,eNoAction,NULL);

		HAL_UART_Receive_IT(&huart6, (uint8_t *)&Received_Char_ESP, 1);



	}
}


/*Interrupt come every rising edge*/
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
	if (htim->Instance == TIM2 && (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1 || htim->Channel == HAL_TIM_ACTIVE_CHANNEL_2))
	{
		edges_counter++;
	}
}


void CallBack_TimerLCDBuzzer(TimerHandle_t xTimer)
{
	/*Stopping the buzzer*/
	Buzzer_voidStop();

	/*Clearing the LCD*/
	LCD_voidClearDisplay();
}


/*********************************************Application_Hook*************************************************************/
void vApplicationIdleHook(void)
{
	/*The processor will go to sleep in the IDLE Task*/
	HAL_PWR_EnterSLEEPMode(PWR_MAINREGULATOR_ON, PWR_SLEEPENTRY_WFI);

}

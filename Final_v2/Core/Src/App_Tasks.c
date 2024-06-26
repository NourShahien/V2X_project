
/*
 * App_Tasks.c
 *
 *  Created on: Feb 29, 2024
 *      Author: nours
 */

#include "main.h"
#include "stm32f4xx_hal.h"
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "App_Tasks.h"
#include "Car_Control.h"
#include "Buzzer.h"
#include "LCD_I2C.h"
#include "NMEA.h"
#include "UartRingbuffer.h"
#include "GPS.h"
#include "Warning_Functions.h"
#include "Call_Back_Functions.h"

/*                                         TaskHandle                                            */
extern TaskHandle_t Handle_Car_Control;
extern TaskHandle_t Handle_Esp_Periodic;
extern TaskHandle_t Handle_Send_ESP_Status;
extern TaskHandle_t Handle_Recieve_ESP_Status;
extern TimerHandle_t Handle_Timer_LCDBuzzer;

/*                                                                                               */


extern UART_HandleTypeDef huart6;
extern UART_HandleTypeDef huart3;
extern UART_HandleTypeDef huart4;

extern GPS_Data_t GPS_Data;
extern uint16_t Global_Speed;

extern volatile char Received_Char_Bluetooth;
extern volatile char Received_Char_ESP;

uint8_t  Global_GPS_Speed_Completetion= 0;
uint8_t Tx_ESP_Buffer[30];
uint8_t ESP_Status_Buffer[3];


void TASK_GPS(void *Parameters)
{
	uint8_t Decode_Error_Code;
	while(1)
	{
		/*Update the GPS Data*/
		Decode_Error_Code = GPS_uint8DecodeGGAData();
		if(Decode_Error_Code==Decode_Success)
		{
			/*Update the completetion flag to activate the sendESP_Periodic task*/
			if(Global_GPS_Speed_Completetion==Nothing_Completed)
			{
				Global_GPS_Speed_Completetion=Half_Completed_GPS;

			}
			else if(Global_GPS_Speed_Completetion==Half_Completed_Speed)
			{
				Global_GPS_Speed_Completetion=Nothing_Completed;
				/*Activate the ESPTask*/
				xTaskNotify(Handle_Esp_Periodic,0,eNoAction);
			}
			/*Stopping the task for 400ms to free the processor*/
			vTaskDelay(pdMS_TO_TICKS(1000));
		}
		else if(Decode_Error_Code==Decode_Failed)
		{

			/*Do nothing*/
		}


	}


}


void Task_ControlCar(void *Parameters)
{
	while(1)
	{
		/*Task will be in Blocked State Waiting for RxCallback Function to Notify it*/
		xTaskNotifyWait((uint32_t)NULL,(uint32_t)NULL,0,portMAX_DELAY);
		switch(Received_Char_Bluetooth)
		{
		case 'F':
			Car_Move_Forward_High_Speed();
			break;
		case 'B':
			Car_Move_Backward();
			break;
		case 'V':
			/*if char recieved 'S' then Notify The Task_Esp That There is Hard Brake*/
			Car_Stop();
			//xTaskNotify(Handle_Send_ESP_Status,0,eNoAction);
			break;
		case 'R':
			Car_Rotate_Right();
			break;
		case 'L':
			Car_Rotate_Left();
			break;
		}

	}


}


void Task_SendEspPeriodic(void *Parameters)
{
	BaseType_t Notify_Status;
	uint32_t Local_uint32NotificationValue;
	while(1)
	{
		/*Task will be in Blocked State Waiting for GPS_Task To Notify it*/
		Notify_Status = xTaskNotifyWait(NULL, NULL, &Local_uint32NotificationValue, portMAX_DELAY);
		if(Notify_Status == pdTRUE)
		{
			/*Assign GPS and Speed Data to Transmission Buffer*/
			GPSSPEED_voidBuildMsg(&Tx_ESP_Buffer, GPS_Data.Longitude, GPS_Data.Latitude, Global_Speed);

			/*Transmit the Buffer*/
			HAL_UART_Transmit(&huart4, Tx_ESP_Buffer, sizeof(Tx_ESP_Buffer), 1500);
		}
		else
		{
			/*Do nothing*/
		}

	}


}


//void Task_SendEsp_Status(void *Parameters)
//{
//	BaseType_t Notify_Status;
//	uint32_t Local_uint32NotificationValue;
//	ESP_Status_Buffer[0] = '%';
//	ESP_Status_Buffer[1] = '0';
//	ESP_Status_Buffer[2] = '!';
//
//
//	while(1)
//	{
//		Notify_Status = xTaskNotifyWait(NULL, NULL, &Local_uint32NotificationValue, portMAX_DELAY);
//		if(Notify_Status == pdTRUE)
//		{
//			switch(Local_uint32NotificationValue)
//			{
//			case Hard_Brake_Notification:
//				/*Send Message to ESP That Hard Brake occur*/
//				HAL_UART_Transmit(&huart2, ESP_Status_Buffer,sizeof(ESP_Status_Buffer), 500);
//				break;
//			}
//
//
//		}
//
//	}
//
//}


void Task_Recieve_Status_Esp(void *Parameters)
{

	BaseType_t Notify_Status;
	uint32_t Local_uint32NotificationValue;

	while(1)
	{
		/*Task will be in Blocked State Waiting for RxCallback Function to Notify it*/
		Notify_Status = xTaskNotifyWait((uint32_t)NULL,(uint32_t)NULL,&Local_uint32NotificationValue, portMAX_DELAY);
		if(Notify_Status == pdTRUE)
		{

			switch(Received_Char_ESP)
			{
			case 'B':

				Car_Stop();

				/*Display The Warning Message on LCD to The Driver and the Alerting Sound of the Buzzer*/
				Hard_Brake_Warning();

				/*Start the timer to stop the buzzer and clear LCD after period of specified time*/
				xTimerStart(Handle_Timer_LCDBuzzer,1000);

				break;
			}
		}

	}

}

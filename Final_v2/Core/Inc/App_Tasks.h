/*
 * App_Tasks.h
 *
 *  Created on: Feb 29, 2024
 *      Author: nours
 */

#ifndef INC_APP_TASKS_H_
#define INC_APP_TASKS_H_
#include "main.h"
#include "FreeRTOS.h"
#include "task.h"

void Task_ControlCar(void *Parameters);
void Task_SpeedCalculation(void *Parameters);
void TASK_GPS(void *Parameters);
void Task_SendEspPeriodic(void *Parameters);
void Task_SendEsp_Status(void *Parameters);
void Task_Recieve_Status_Esp(void *Parameters);

/***************************************Task Priorities*************************************************/
#define Task_GPS_Priority						2
#define Task_Control_Car_Priority				2
#define Task_Send_ESP_Periodic_Priority			2
//#define Task_Send_ESP_Status_Priority			3
#define Task_Recieve_ESP_Priority				3
/***************************************Private Macros*************************************************/
#define Nothing_Completed                      0
#define Half_Completed_Speed                   1
#define Half_Completed_GPS                     2
/******************************************************************************************************/
#define Hard_Brake_Notification					0





#endif /* INC_APP_TASKS_H_ */

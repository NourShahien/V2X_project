/*
 * CalculateSpeed.c
 *
 *  Created on: Mar 3, 2024
 *      Author: nours
 */
#include "stm32f4xx_hal.h"
#include "CalculateSpeed.h"


extern uint32_t edges_counter;

float Calculate_Car_Speed()
{
	float Local_uint16Speed;
	Local_uint16Speed = (edges_counter * 360 /50) * 2 * 3.14 * 0.03;
	edges_counter=0;
	return Local_uint16Speed;
}

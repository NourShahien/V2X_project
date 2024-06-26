/*
 * Warning_Functions.c
 *
 *  Created on: Mar 8, 2024
 *      Author: nours
 */
#include "stm32f4xx_hal.h"
#include "Warning_Functions.h"
#include "Buzzer.h"
#include "LCD_I2C.h"

static void LCD_Print_WarningSign(void);






void Hard_Brake_Warning(void)
{
	/*Show a Warning Sign to The Driver*/
	LCD_Print_WarningSign();

	/*Show a Warning Message To The Driver*/
	LCD_voidSetPositionXY(1, 0);
	LCD_voidSendString("Brake!!!");
	Buzzer_voidHighSound();

}

void Traffic_Condition_Warning(void)
{
	Buzzer_voidHighSound();
	/*Show a Warning Sign to The Driver*/
	LCD_Print_WarningSign();

	/*Show a Warning Message To The Driver*/
	LCD_voidSetPositionXY(1,0);
	LCD_voidSendString("Warning");

	LCD_voidSetPositionXY(2,0);
	LCD_voidSendString("High Congestion");
}



static void LCD_Print_WarningSign(void)
{
	/*Saving the elemetents of each block of the LCD in multiple arrays to be sent to the special charachter function*/

	uint8_t LCD_R1_C16_Array[8] =
	{
			0b00000100,
			0b00001010,
			0b00010001,
			0b00000000,
			0b00000000,
			0b00001110,
			0b00001110,
			0b00001110
	};

	uint8_t LCD_R1_C17_Array[8] =
	{
			0b00000000,
			0b00000000,
			0b00000000,
			0b00010000,
			0b00001000,
			0b00000100,
			0b00000010,
			0b00000001
	};
	uint8_t LCD_R1_C15_Array[8] =
	{
			0b00000000,
			0b00000000,
			0b00000000,
			0b00000001,
			0b00000010,
			0b00000100,
			0b00001000,
			0b00010000
	};

	uint8_t LCD_R2_C14_Array[8] =
	{
			0b00000010,
			0b00000100,
			0b00001000,
			0b00010000,
			0b00000000,
			0b00000000,
			0b00000000,
			0b00011111
	};

	uint8_t LCD_R2_C18_Array[8] =
	{
			0b00001000,
			0b00000100,
			0b00000010,
			0b00000001,
			0b00000000,
			0b00000000,
			0b00000000,
			0b00011111
	};
	uint8_t LCD_R2_C13_Array[8] =
	{
			0b00000000,
			0b00000000,
			0b00000000,
			0b00000000,
			0b00000001,
			0b00000010,
			0b00000100,
			0b00011111
	};
	uint8_t LCD_R2_C19_Array[8] =
	{
			0b00000000,
			0b00000000,
			0b00000000,
			0b00010000,
			0b00001000,
			0b00000100,
			0b00000010,
			0b00011111
	};
	uint8_t LCD_R2_C15_Array[8] =
	{
			0b00000000,
			0b00000000,
			0b00000000,
			0b00000000,
			0b00000000,
			0b00000000,
			0b00000000,
			0b00011111
	};
	uint8_t LCD_R2_C17_Array[8] =
	{
			0b00000000,
			0b00000000,
			0b00000000,
			0b00000000,
			0b00000000,
			0b00000000,
			0b00000000,
			0b00011111
	};
	uint8_t LCD_R2_C16_Array[8] =
	{
			0b00001110,
			0b00001110,
			0b00001110,
			0b00000000,
			0b00000100,
			0b00000000,
			0b00000000,
			0b00011111
	};


	LCD_voidDrawSpecialCharachter(&LCD_R1_C15_Array, 0, 1, 15);
	LCD_voidDrawSpecialCharachter(&LCD_R1_C16_Array, 1, 1, 16);
	LCD_voidDrawSpecialCharachter(&LCD_R1_C17_Array, 2, 1, 17);

	LCD_voidDrawSpecialCharachter(&LCD_R2_C14_Array, 3, 2, 14);
	LCD_voidDrawSpecialCharachter(&LCD_R2_C15_Array, 4, 2, 15);
	LCD_voidDrawSpecialCharachter(&LCD_R2_C16_Array, 5, 2, 16);
	LCD_voidDrawSpecialCharachter(&LCD_R2_C17_Array, 6, 2, 17);
	LCD_voidDrawSpecialCharachter(&LCD_R2_C18_Array, 7, 2, 18);




}


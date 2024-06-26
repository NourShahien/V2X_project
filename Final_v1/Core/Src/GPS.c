/*
 * GPS.c
 *
 *  Created on: Dec 6, 2023
 *      Author: nours
 */


#include "main.h"
#include "stm32f4xx_hal.h"
#include "GPS.h"
#include "LCD_I2C.h"
#include "UartRingbuffer.h"
#include "NMEA.h"
#include <math.h>


#define  Valid_Data      2
#define  unValid_Data    1

GPS_Data_t GPS_Data;




GPSSTRUCT GPS_NMEA_DATA;

/*Buffer Which Contains The Undecoded GGA Data*/
uint8_t GGA[100];
/*GGA Flag to Check Data is Valid or Not*/
uint8_t flagGGA = 0;

/*flag to Check Data is decoded Successful or not*/
uint8_t flag_GPS;
extern UART_HandleTypeDef huart1;





void GPS_voidInit(void)
{
	/*Initialize Ring Buffer*/
	Ringbuf_init();
	HAL_Delay(500);

	/*Initialize LCD*/
	LCD_voidInit();

	/*Write on LCD That GPS Still Initializing*/
	LCD_voidSetPositionXY(0, 0);
	LCD_voidSendString("Waiting For GPS");

	/*Wait till GGA Data is Valid*/
	while(flagGGA != Valid_Data)
	{
		if(Wait_for("GGA") == 1)
		{
			Copy_upto("*", GGA);
			if(decodeGGA(GGA, &GPS_NMEA_DATA.ggastruct) == 0)
			{
				flagGGA = Valid_Data;  //indicate the Data is Valid
			}
			else
			{
				flagGGA = unValid_Data; //indicate the Data is InValid
			}
		}
	}


	/*Clear LCD and Tell User To Start The Project*/
	LCD_voidClearDisplay();
	LCD_voidSetPositionXY(0,4);
	LCD_voidSendString("GPS is Done");
	LCD_voidSetPositionXY(1,4);
	LCD_voidSendString("Start Project");
	/*Clearing the Flag*/
	flagGGA = 0;
	HAL_Delay(2000);
	LCD_voidClearDisplay();


}


/*
 *
 */
uint8_t GPS_uint8DecodeGGAData(void)
{
	uint8_t Local_uint8ErrorCode = 0;


	if(Wait_for("GGA") == 1)
	{
		Copy_upto("*", GGA);
		if(decodeGGA(GGA, &GPS_NMEA_DATA.ggastruct) == 0)
		{
			flagGGA = Valid_Data;  //indicate the Data is Valid
		}
		else
		{
			flagGGA = unValid_Data; //indicate the Data is InValid
		}
	}

	if(flagGGA == Valid_Data)
	{
		Local_uint8ErrorCode = Decode_Success;

		GPS_Data.Latitude    =    GPS_doubleLongLat_Calculation(GPS_NMEA_DATA.ggastruct.lcation.latitude);
		GPS_Data.Longitude   =    GPS_doubleLongLat_Calculation(GPS_NMEA_DATA.ggastruct.lcation.longitude);
		GPS_Data.East_West   =    GPS_NMEA_DATA.ggastruct.lcation.EW;
		GPS_Data.North_South =    GPS_NMEA_DATA.ggastruct.lcation.NS;

	}
	else
	{
		Local_uint8ErrorCode = Decode_Failed;


	}

	return Local_uint8ErrorCode;
}


void GPS_voidLCD_Data_Display(void)
{
	/*Clearing the lcd to send the needed data*/
	LCD_voidClearDisplay();

	/*Sending the data in this pattern:  */

	//Latitude sending
	LCD_voidSetPositionXY(0,0);
	LCD_voidSendString("Lat: ");
	LCD_voidSetPositionXY(0,6);
	LCD_voidWriteNum(GPS_Data.Latitude);

	//longitude sending
	LCD_voidSetPositionXY(1,0);
	LCD_voidSendString("Long: ");
	LCD_voidSetPositionXY(1,6);
	LCD_voidWriteNum(GPS_Data.Longitude);

	// E/W sending
	LCD_voidSetPositionXY(2,0);
	LCD_voidSendString("E/W: ");
	LCD_voidSetPositionXY(2,6);
	LCD_voidSendCharachter(GPS_Data.East_West);

	// N/S Sending
	LCD_voidSetPositionXY(2,10);
	LCD_voidSendString("N/S: ");
	LCD_voidSetPositionXY(2,16);
	LCD_voidSendCharachter(GPS_Data.North_South);


}

double GPS_doubleLongLat_Calculation(double lat)
{
	uint8_t intValue ;
	double fraction;
	intValue = lat; //intValue = 31 instead of 31.39049
	fraction = lat - intValue; // fraction = 0.39049
	fraction = (double) ((fraction * 100.0) / 60.0) ; //fraction = (39.049)/60 = 0.6532

	return (double) (intValue + fraction); // return value = 31 + 0.6532 = 31.6532
}


/*
 * GPS.h
 *
 *  Created on: Dec 6, 2023
 *      Author: nours
 */

#ifndef INC_GPS_H_
#define INC_GPS_H_

void GPS_voidInit(void);
uint8_t GPS_uint8DecodeGGAData(void);
void GPS_voidLCD_Data_Display(void);
double GPS_doubleLongLat_Calculation(double lat);


typedef struct
{
	double Latitude;
	double Longitude;
	uint8_t East_West;
	uint8_t North_South;
}GPS_Data_t;

//GPS_Data_t GPS_Data;


#define  Decode_Success  1
#define  Decode_Failed   2

#endif /* INC_GPS_H_ */

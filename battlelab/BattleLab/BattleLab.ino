/*
 Name:		BattleLab.ino
 Created:	5/3/2018 2:51:51 PM
 Author:	Andrei
*/

#include <Sabertooth.h>
#include <QTRSensors.h>
#define NUMBER_OF_SENSORS   1      // number of sensors used
#define TIMEOUT       2500		  // waits for 2500 microseconds for sensor outputs to go low
#define LINE_EMITTER_PIN   9     // emitter is controlled by digital pin 9
#define OMRON1 2 //presence sensor 1
#define OMRON2 2 //presence sensor 2
#define OMRON3 2 //presence sensor 3
#define OMRON4 2 //presence sensor 4
#define OMRON5 2 //presence sensor 5
#define OMRON6 2 //presence sensor 6
#define OMRON7 2 //presence sensor 7	
#define maxLineTime 900
#define whiteThreshold 700
//the pins for the white line sensors
unsigned char linePins[2] = { 9,10 };
//times for each line sensor
bool whiteFlagLeft, whiteFlagRight;
int lineSensors[2], seeWhite, Start = 1;
int readWhite();

Sabertooth ST(128);




void setup()
{
	pinMode(OMRON1, INPUT);
	pinMode(OMRON2, INPUT);
	pinMode(OMRON3, INPUT);
	pinMode(OMRON4, INPUT);
	pinMode(OMRON5, INPUT);
	pinMode(OMRON6, INPUT);
	pinMode(OMRON7, INPUT);
	Serial.begin(9600);
	SabertoothTXPinSerial.begin(9600);
	ST.autobaud();
	ST.motor(1, 0);
	ST.motor(2, 0);
}


void loop()
{
	if (Start)//start/stop check
	{
		seeWhite = readWhite();
		if (seeWhite)
		{
			ST.motor(1, 0);
			ST.motor(2, 0);
			whiteFlag//left right 
		}
		Serial.println(); // uncomment this line if you are using raw values
		delay(250);
	}
}

int readWhite()
{
		for (int i = 0; i < NUMBER_OF_SENSORS; i++)
		{
			lineSensors[i] = maxLineTime;
			pinMode(linePins[i], OUTPUT);
			digitalWrite(linePins[i], HIGH);
		}
		delayMicroseconds(10);              // charge lines for 10 us
		for (int i = 0; i < NUMBER_OF_SENSORS; i++)
			pinMode(linePins[i], INPUT);
		unsigned long startTime = micros();
		while (micros() - startTime < maxLineTime)
		{
			unsigned int time = micros() - startTime;
			for (int i = 0; i < NUMBER_OF_SENSORS; i++)
				if (digitalRead(linePins[i]) == LOW && time < lineSensors[i])
					lineSensors[i] = time;
		}
		//left righ or none
		if (lineSensors[0] <= whiteThreshold)
			return 1;//1 for left
		if (lineSensors[1] <= whiteThreshold)
			return 2;//2 for right
		return 0;//0 for none
	}

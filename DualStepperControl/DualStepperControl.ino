/**
 * Assuming that stepper drivers like DRV8843 are used and microsteps and enable pin are active.
 * So only pins required are STEP and possibly DIR
 */

#include "Arduino.h"

#include "../libs/my_util.h"
#include "StepperPWM.h"

#define STEP1	3
#define STEP2	10



void setup()
{
	Serial.begin(115200);
	Serial.println("---START---");
	Serial.println(("Data format: speed1,speed2. e.g.: 200,200"));
}

int t1 = 200; bool lastState1 = false;
int t2 = 200; bool lastState2 = false;

void loop()
{
	if (Serial.available())
	{
		String recvStr = Serial.readString();

		// parsing recvString
		int speed1 = to_int(getStringPartByNr(recvStr, ',', 0));
		int speed2 = to_int(getStringPartByNr(recvStr, ',', 1));

		// print recv values as debugging data
		Serial.println("RECEIVED: " + to_string(speed1) + "," + to_string(speed2));

		// transfer vars to globals
		t1 = speed1;
		t2 = speed2;
	}

	static int lastMicros1 = micros();
	if(micros() - lastMicros1 > t1)
	{
		lastMicros1 = micros();

	}


}

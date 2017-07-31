#include <Arduino.h>

#include "DRV8834.h"
#include "../libs/my_util.h"

// Motor steps per revolution. Most steppers are 200 steps or 1.8 degrees/step
#define MOTOR_STEPS 200

// All the wires needed for full functionality
#define DIR 	8
#define STEP 	9
#define M0 		10
#define M1 		11
#define ENBL 	13

//DRV8834 stepper(MOTOR_STEPS, DIR, STEP, ENBL);
DRV8834 stepper(MOTOR_STEPS, DIR, STEP, ENBL, M0, M1);	//microsteps enabled

void setup()
{
	Serial.begin(115200);
	Serial.println("---STARTED---");
	stepper.begin(50, 1);
}

int speed = 0;
void loop()
{

	//Grab speed from serial port
	if(Serial.available())
	{
		speed = to_int(Serial.readString());
		if(speed == 0)
		{
			Serial.println("BRAKE");
			stepper.disable();
			//digitalWrite(ENBL, LOW);
		}
		else
		{
			Serial.println("New speed: " + to_string(speed));
			stepper.setRPM(speed);
			stepper.enable();
			//digitalWrite(ENBL, HIGH);
		}
	}
	stepper.move(1);

}




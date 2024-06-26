#pragma config(Sensor, in1,    lightSensor,    sensorReflection)
#pragma config(Sensor, in2,    lineFollower,   sensorLineFollower)
#pragma config(Sensor, dgtl1,  bumpSwitch,     sensorTouch)
#pragma config(Motor,  port1,           flashlight,    tmotorVexFlashlight, openLoop, reversed)
#pragma config(Motor,  port2,           servo,         tmotorServoStandard, openLoop)
#pragma config(Motor,  port3,           openMotor,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           sortMotor,     tmotorServoStandard, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

void open(); //function declaration for carousel dispensing one marble at a time
void openSort(); //funcion declaration for light sensor door

task main()
{
	//line threshold
	int lineThresh = 1800; //constant threshold for line follower. If its under this value, it is a wood marble.

	//Light value Threshold
	int lightThresholdLow= 55; //constant low threshold for plastic marbles
	int lightThresholdHigh = 140; //constant max threshold for a colored marble

	//Servo Positions
	int pos1 = -50; //wood servo position
	int pos2 = 50; //plastic servo position
	int pos3 = 110; //colored servo position
	int pos4 = -110; //metal servo position

	turnFlashlightOn(flashlight, 150); //turns the flashlight on
	
	untilBump(bumpSwitch) //wait until the bump switch is pressed to start the program
	
	while(true){

		bool isLight = false; //declaration for plastic marble boolean 
		bool isMedium = false; //declaration for colored marble boolean
		bool isWood = false; //declaration for wood marble declaration

		setServo(sortMotor, 25); //sets door to position 25 at the start of eachiteration

		open(); //call to open function, which spins the carousel to dispense a marble

		wait(2); //wait to allow vex parts to get new values


		if(SensorValue(lineFollower) < lineThresh){ //if the line follower value is less than the constant, it is a wood marble
			setServo(servo, pos1); // set the servo to constant pos1
		}
		else if(SensorValue(lightSensor) < lightThresholdLow){//else, if the light sensor value is less than the low constant, it is a plastic marble
			setServo(servo, pos2); // sets the servo to constant pos2
		}
		else if(SensorValue(lightSensor) < lightThresholdHigh){  //if light sensor value is less than the high constant and greater than the low constant, it is a colored marble
			setServo(servo, pos3); // sets the servo to constant pos3
		}
		else{
			setServo(servo, pos4); // otherwise, its a metal marble and sets the servo to constant pos4
		}
		openSort(); //calls the openSort method, which opens the servo door to allow the marble to fall into the cup
	}

}

void open(){
	startMotor(openMotor, 15); // starts the motor openMotor with a power of 15
	wait(0.65); // wait to allow the motor to complete roughly a quarter revolution
	stopMotor(openMotor); //stop the motor to prevent further marbles from being dispensed
}

void openSort(){
	setServo(sortMotor, -127); // sets the servo to position -127 to move the marble back and give it momentum to roll into the cup
	wait(1); // allow the marble to come back forward
	setServo(sortMotor, 25); //close the door to stop the next marble
}

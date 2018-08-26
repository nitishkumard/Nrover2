#ifndef NRover2IntelligentMover_H
#define NRover2IntelligentMover_H

#include <Arduino.h>
#include "NRover2Mover.h" 
#include "NRover2MagneticSensor.h" 
#include "NRover2UltraSoundSensor.h"

class NRover2IntelligentMover { 
public:
	NRover2IntelligentMover(HardwareSerial*);
	NRover2IntelligentMover(HardwareSerial*, NRover2Mover, NRover2MagneticSensor, NRover2UltraSoundSensor);
	~NRover2IntelligentMover();  
	void start();
	void printSensorDetails();  	
	void printStatus();
	int move(int direction);
	void avoidFrontObstruction();
	int turn(int degree);
	int turnToAngle(int shouldBeAngle);
	int adjustAngleValue(int angle);
};

#endif
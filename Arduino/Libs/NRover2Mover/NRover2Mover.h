#ifndef NRover2Mover_H
#define NRover2Mover_H

#include <Arduino.h>

class NRover2Mover { 
public:

	NRover2Mover(HardwareSerial*);
	~NRover2Mover();  
	void start();
	void printSensorDetails();  	
	void printStatus();
	int move(int speed);
	int turn(int degree);
	void actuateRearMotors(int inByte);
	void actuateFrontMotors(int inByte);
};

#endif
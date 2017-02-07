#ifndef NRover2UltraSoundSensor_H
#define NRover2UltraSoundSensor_H

#include <Arduino.h>

class NRover2UltraSoundSensor { 
public:

	NRover2UltraSoundSensor(HardwareSerial*);
	~NRover2UltraSoundSensor();  
	void start();
	void printSensorDetails();  	
	void printStatus();
	int getDistance();
};

#endif
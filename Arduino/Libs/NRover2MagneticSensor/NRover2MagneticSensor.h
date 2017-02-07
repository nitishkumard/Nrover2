#ifndef NRover2MagneticSensor_H
#define NRover2MagneticSensor_H

#include <Arduino.h>

class NRover2MagneticSensor { 
public:

	NRover2MagneticSensor(HardwareSerial*);
	~NRover2MagneticSensor();  
	void start();
	void printSensorDetails();  	
	void printStatus();
	float getHeadingAngle();
};

#endif
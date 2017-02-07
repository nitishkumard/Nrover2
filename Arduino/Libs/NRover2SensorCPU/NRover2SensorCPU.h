#ifndef NRover2SensorCPU_H
#define NRover2SensorCPU_H

#include <Arduino.h>

class NRover2SensorCPU { 
public:
	NRover2SensorCPU(HardwareSerial*);
	~NRover2SensorCPU();  
	void start();
	void printSensorDetails();  	
	void printStatus();
};

#endif
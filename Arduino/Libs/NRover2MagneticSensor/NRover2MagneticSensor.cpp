#include "NRover2MagneticSensor.h" //include the declaration for this class

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_HMC5883_U.h>

/* Assign a unique ID to this sensor at the same time */
Adafruit_HMC5883_Unified mag = Adafruit_HMC5883_Unified(12345);
extern HardwareSerial* printer;

//<<constructor>> 
NRover2MagneticSensor::NRover2MagneticSensor(HardwareSerial* print)
{
	printer = print;
}

//<<destructor>>
NRover2MagneticSensor::~NRover2MagneticSensor(){/*nothing to destruct*/}

void NRover2MagneticSensor::start(void)
{ 
	//Initialize Magnetic Sensor
	printer->println("Initializing Sensor : HMC5883 Magnetometer"); printer->println("");
  	if(!mag.begin())
  	{
    		/* There was a problem detecting the HMC5883 ... check your connections */
	    	printer->println("Ooops, no HMC5883 detected ... Check your wiring!");
    		while(1);
  	}
}


void NRover2MagneticSensor::printSensorDetails(void)
{
  	sensor_t sensor;
  	mag.getSensor(&sensor);
  	printer->println("------------------------------------");
  	printer->print  ("Sensor:       "); printer->println(sensor.name);
  	printer->print  ("Driver Ver:   "); printer->println(sensor.version);
  	printer->print  ("Unique ID:    "); printer->println(sensor.sensor_id);
  	printer->print  ("Max Value:    "); printer->print(sensor.max_value); printer->println(" uT");
  	printer->print  ("Min Value:    "); printer->print(sensor.min_value); printer->println(" uT");
  	printer->print  ("Resolution:   "); printer->print(sensor.resolution); printer->println(" uT");  
  	printer->println("------------------------------------");
  	printer->println("");
  	delay(500);
}

void NRover2MagneticSensor::printStatus(void)
{
  	/* Get a new sensor event */ 
  	sensors_event_t event; 
  	mag.getEvent(&event);
  	printer->println("------------------------------------");
  	/* Display the results (magnetic vector values are in micro-Tesla (uT)) */
  	printer->print("X: "); printer->print(event.magnetic.x); printer->print("  ");
  	printer->print("Y: "); printer->print(event.magnetic.y); printer->print("  ");
  	printer->print("Z: "); printer->print(event.magnetic.z); printer->print("  ");printer->println("uT");
	printer->print("Heading (degrees): "); printer->println(getHeadingAngle());
  	printer->println("------------------------------------");
}

float NRover2MagneticSensor::getHeadingAngle(void)
{
  	/* Get a new sensor event */ 
  	sensors_event_t event; 
  	mag.getEvent(&event);

	float heading = atan2(event.magnetic.y, event.magnetic.x);

	//Degree adjustments for magnetic inclination
  	float declinationAngle = -0.017;
  	heading += declinationAngle;
  	if(heading < 0)
    		heading += 2*PI;
	if(heading > 2*PI)
    		heading -= 2*PI;
	// Convert radians to degrees for readability.
  	float headingDegrees = heading * 180/M_PI;

	return headingDegrees;
}
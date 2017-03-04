#include "NRover2Mover.h" //include the declaration for this class

extern HardwareSerial* printer;

// defines pins numbers
const int trigPin = 44;
const int echoPin = 45;

// defines variables
long duration;
int distance;

//<<constructor>> 
NRover2Mover::NRover2Mover(HardwareSerial* print)
{
	printer = print;
}

//<<destructor>>
NRover2Mover::~NRover2Mover()
{
	/*nothing to destruct*/
}

void NRover2Mover::start(void)
{
	pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
	pinMode(echoPin, INPUT); // Sets the echoPin as an Input
	Serial.begin(9600); // Starts the serial communication
}


void NRover2Mover::printSensorDetails(void)
{
  	printer->println("------------------------------------");
  	printer->print  ("Output:       "); printer->println("Ultra Sound Sensor : ");
	printer->print  ("Output on Pins:       "); printer->println("Trigger : 44 & Echo : 45");
  	//printer->print  ("Driver Ver:   "); printer->println(sensor.version : HC-SR04);
  	//printer->print  ("Unique ID:    "); printer->println(sensor.sensor_id);
  	//printer->print  ("Max Value:    "); printer->print(sensor.max_value); printer->println(" uT");
  	//printer->print  ("Min Value:    "); printer->print(sensor.min_value); printer->println(" uT");
  	//printer->print  ("Resolution:   "); printer->print(sensor.resolution); printer->println(" uT");  
  	printer->println("------------------------------------");
  	printer->println("");
  	delay(500);
}

void NRover2Mover::printStatus(void)
{
  	printer->println("------------------------------------");
  	/* Display the results (Ultra sound distance values are in centi-meter (cm)) */  	
	printer->print("Distance from next Obstacle (cm): "); printer->println(getDistance());
  	printer->println("------------------------------------");
}

int NRover2Mover::move(int speed)
{
	// Sets the trigPin on HIGH state for 10 micro seconds
	digitalWrite(trigPin, HIGH);
	delayMicroseconds(10);
	digitalWrite(trigPin, LOW);
	// Reads the echoPin, returns the sound wave travel time in microseconds
	duration = pulseIn(echoPin, HIGH);
	// Calculating the distance
	distance= duration*0.034/2;
	// Prints the distance on the Serial Monitor
	return distance;
}

int NRover2Mover::turn(int angle)
{
	// Sets the trigPin on HIGH state for 10 micro seconds
	digitalWrite(trigPin, HIGH);
	delayMicroseconds(10);
	digitalWrite(trigPin, LOW);
	// Reads the echoPin, returns the sound wave travel time in microseconds
	duration = pulseIn(echoPin, HIGH);
	// Calculating the distance
	distance= duration*0.034/2;
	// Prints the distance on the Serial Monitor
	return distance;
}
#include <NRover2UltraSoundSensor.h>
#include <NRover2MagneticSensor.h>
#include <NRover2SensorCPU.h>

NRover2SensorCPU sensorCPU = NRover2SensorCPU(&Serial);
NRover2UltraSoundSensor ultrasoundSensor = NRover2UltraSoundSensor(&Serial);//initialize an instance of the class
NRover2MagneticSensor magneticSensor = NRover2MagneticSensor(&Serial);//initialize an instance of the class

void setup()
{ /*nothing to setup*/
  Serial.begin(9600);
  sensorCPU = NRover2SensorCPU(&Serial);
  magneticSensor = NRover2MagneticSensor(&Serial);
  ultrasoundSensor = NRover2UltraSoundSensor(&Serial);

  sensorCPU.printSensorDetails();
  ultrasoundSensor.printSensorDetails();
  magneticSensor.printSensorDetails();

  sensorCPU.start();
  ultrasoundSensor.start();
  magneticSensor.start();

  sensorCPU.start();
  ultrasoundSensor.printStatus();
  magneticSensor.printStatus();
}

void loop()
{ 
  Serial.print("Next obstacle in (cm): "); Serial.println(ultrasoundSensor.getDistance());  
  Serial.print("Heading (degrees): "); Serial.println(magneticSensor.getHeadingAngle());  
  delay(1000);
}

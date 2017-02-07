#include <NRover2UltraSoundSensor.h>

NRover2UltraSoundSensor ultrasoundSensor = NRover2UltraSoundSensor(&Serial);//initialize an instance of the class

void setup()
{ /*nothing to setup*/
  Serial.begin(9600);
  ultrasoundSensor = NRover2UltraSoundSensor(&Serial);
  ultrasoundSensor.printSensorDetails();
  ultrasoundSensor.start();
}

void loop()
{
  ultrasoundSensor.printStatus();
  Serial.print("Next obstacle in (cm): "); Serial.println(ultrasoundSensor.getDistance());
  delay(1000);
}
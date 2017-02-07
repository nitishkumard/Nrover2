#include <NRover2MagneticSensor.h>

NRover2MagneticSensor magneticSensor = NRover2MagneticSensor(&Serial);//initialize an instance of the class

void setup()
{ /*nothing to setup*/
  Serial.begin(9600);
  magneticSensor = NRover2MagneticSensor(&Serial);
  magneticSensor.printSensorDetails();
  magneticSensor.start();
}

void loop()
{
  magneticSensor.printStatus();
  Serial.print("Heading (degrees): "); Serial.println(magneticSensor.getHeadingAngle());
  delay(1000);
}
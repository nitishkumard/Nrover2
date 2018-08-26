#include <Adafruit_Sensor.h>
#include <Adafruit_HMC5883_U.h>

#include <NRover2UltraSoundSensor.h>
#include <NRover2MagneticSensor.h>
#include <NRover2SensorCPU.h>
#include <NRover2Mover.h>
#include <NRover2IntelligentMover.h>

NRover2SensorCPU sensorCPU = NRover2SensorCPU(&Serial);
NRover2UltraSoundSensor ultrasoundSensor = NRover2UltraSoundSensor(&Serial);//initialize an instance of the class
NRover2MagneticSensor magneticSensor = NRover2MagneticSensor(&Serial);//initialize an instance of the class
NRover2Mover mover = NRover2Mover(&Serial);
NRover2IntelligentMover iMover = NRover2IntelligentMover(&Serial);

boolean isDebug = false;

void setup()
{
  Serial.begin(9600);

  // Instantiating objects
  sensorCPU = NRover2SensorCPU(&Serial);
  magneticSensor = NRover2MagneticSensor(&Serial);
  ultrasoundSensor = NRover2UltraSoundSensor(&Serial);
  mover = NRover2Mover(&Serial);
  iMover = NRover2IntelligentMover(&Serial, mover, magneticSensor, ultrasoundSensor);

  // Printing sensor details
  sensorCPU.printSensorDetails();
  ultrasoundSensor.printSensorDetails();
  magneticSensor.printSensorDetails();

  // Starting components : Phase 1
  sensorCPU.start();
  ultrasoundSensor.start();
  magneticSensor.start();
  mover.start();

  // Starting components : Phase 2
  sensorCPU.start();

  // Running test run during setup
  ultrasoundSensor.printStatus();
  magneticSensor.printStatus();
}

void loop()
{
  // Printing sensor details for debugging
  int nextObstacleDistance = ultrasoundSensor.getDistance();
  Serial.print("Next obstacle in (cm): ");Serial.println(ultrasoundSensor.getDistance());
  int headingAngle = magneticSensor.getHeadingAngle();
  Serial.print("Heading (degrees):");Serial.println(headingAngle);

  isDebug = false;

  // Core logic
  if (!isDebug)
  {
    if (nextObstacleDistance < 10)
    {
      iMover.turn(180);
      delay(500);
    }
    else if (nextObstacleDistance < 25)
    {      
      iMover.move('3');
    }
  }
  
  if (isDebug)
  {
    iMover.turn(60);
    Serial.println("Waiting One Second");
    delay(2000);
        iMover.turn(150);
    Serial.println("Waiting One Second");
    delay(2000);
            iMover.turn(230);
    Serial.println("Waiting One Second");
    delay(2000);
                iMover.turn(340);
    Serial.println("Waiting One Second");
    delay(2000);
  }
}

void checkMotors()
{
  mover.actuateFrontMotors('1');
  delay(1000);
  mover.actuateFrontMotors('2');
  delay(1000);
  mover.actuateFrontMotors('3');
  delay(1000);
  mover.actuateFrontMotors('4');
  delay(1000);
  mover.actuateFrontMotors('5');
  delay(1000);
  mover.actuateFrontMotors('6');
  delay(1000);
  mover.actuateRearMotors('1');
  delay(1000);
  mover.actuateRearMotors('2');
  delay(1000);
  mover.actuateFrontMotors('3');
  delay(1000);
  mover.actuateRearMotors('4');
  delay(1000);
  mover.actuateRearMotors('5');
  delay(1000);
  mover.actuateRearMotors('6');
  delay(1000);
}




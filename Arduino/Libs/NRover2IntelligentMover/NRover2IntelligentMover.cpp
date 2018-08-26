#include "NRover2IntelligentMover.h" 
#include "NRover2Mover.h" 
#include "NRover2MagneticSensor.h" 
#include "NRover2UltraSoundSensor.h"

extern HardwareSerial* printer;

int calculatedAngularVelocity; // Angle(degree) per second
int angularVelocityCurrentSampleNo = 0;
int obstructionMinDistance = 15; // Hardcoded for now (cm)

NRover2Mover mover2 = NRover2Mover(&Serial);
NRover2MagneticSensor magneticSensor2 = NRover2MagneticSensor(&Serial);
NRover2UltraSoundSensor ultrasoundSensor2 = NRover2UltraSoundSensor(&Serial);

//<<constructor>> 
NRover2IntelligentMover::NRover2IntelligentMover(HardwareSerial* print)
{
	printer = print;
}
NRover2IntelligentMover::NRover2IntelligentMover(HardwareSerial* print, NRover2Mover pmover2, NRover2MagneticSensor pmagneticSensor2, NRover2UltraSoundSensor pUltrasoundSensor2)
{
	printer = print;
	mover2 = pmover2;
	magneticSensor2 = pmagneticSensor2;
	ultrasoundSensor2 = pUltrasoundSensor2;
}

//<<destructor>>
NRover2IntelligentMover::~NRover2IntelligentMover()
{
	/*nothing to destruct*/
}

void NRover2IntelligentMover::start(void)
{
	mover2 = NRover2Mover(&Serial);
	magneticSensor2 = NRover2MagneticSensor(&Serial);
}


void NRover2IntelligentMover::printSensorDetails(void)
{
  	printer->println("------------------------------------");
  	printer->print  ("Output:       "); printer->println("Intellijent mover2 : ");
	printer->print  ("Movement statistics (calculatedAngularVelocity):       "); printer->println(calculatedAngularVelocity);
  	//printer->print  ("Driver Ver:   "); printer->println(sensor.version : HC-SR04);
  	//printer->print  ("Unique ID:    "); printer->println(sensor.sensor_id);
  	//printer->print  ("Max Value:    "); printer->print(sensor.max_value); printer->println(" uT");
  	//printer->print  ("Min Value:    "); printer->print(sensor.min_value); printer->println(" uT");
  	//printer->print  ("Resolution:   "); printer->print(sensor.resolution); printer->println(" uT");  
  	printer->println("------------------------------------");
  	printer->println("");
  	delay(500);
}

void NRover2IntelligentMover::printStatus(void)
{
  	printer->println("------------------------------------");
  	printer->println("------------------------------------");
}

int NRover2IntelligentMover::move(int direction)
{
	int timeInMillis = 1000; // Hardcoded for now	
	int recheckDurationInMillis = 50;
	int nextObstacleDistance = ultrasoundSensor2.getDistance();
	if(nextObstacleDistance<obstructionMinDistance && direction==1)
	{
		//Trying to move forward on obstruction
		return 0;
	}
	else if(nextObstacleDistance<obstructionMinDistance && direction==3)
	{
		// Reversing on obstruction
		mover2.move(direction);
		delay(10);
		mover2.move('2');
		return 0;
	}
	mover2.move(direction);
	for (int i=0;i<timeInMillis/recheckDurationInMillis;i++)
	{				
		delay(recheckDurationInMillis);
		nextObstacleDistance = ultrasoundSensor2.getDistance();
		if(nextObstacleDistance<obstructionMinDistance && direction==1)
		{
			// moving forward without obstruction and then struck obstruction
			delay(500);
			avoidFrontObstruction();
			mover2.move(direction);
		}
	}
	mover2.move('2');
	return 0;
}

void NRover2IntelligentMover::avoidFrontObstruction()
{
	turnToAngle(90);
	int nextObstacleDistance = ultrasoundSensor2.getDistance();
	if(nextObstacleDistance<obstructionMinDistance)
	{
		delay(500);
		avoidFrontObstruction();
	}
}

int NRover2IntelligentMover::turn(int angle)
{
	int currentAngle = magneticSensor2.getHeadingAngle();
	int shouldBeAngle = currentAngle+angle;
	
	shouldBeAngle = adjustAngleValue(shouldBeAngle);

	turnToAngle(shouldBeAngle);	
	return 1;
}

int NRover2IntelligentMover::turnToAngle(int shouldBeAngle)
{
	int angleTolerance = 15;
	int currentAngle = magneticSensor2.getHeadingAngle();
	int angleToTurn = shouldBeAngle - currentAngle;
	
	angleToTurn = adjustAngleValue(angleToTurn);
	
	if(angleToTurn<angleTolerance || angleToTurn>(360-angleTolerance)) 
	{
		//Free Spin
		mover2.actuateRearMotors('5');
		mover2.actuateRearMotors('2');			
		mover2.actuateFrontMotors('5');
		mover2.actuateFrontMotors('2');
		Serial.print("Moved to direction (degrees): ");Serial.println(shouldBeAngle);		
		return 1;
	}	
		
	if(angleToTurn>270)
	{	
		mover2.actuateRearMotors('6');
		mover2.actuateRearMotors('1');
		//Free Spin
		mover2.actuateFrontMotors('5');
		mover2.actuateFrontMotors('2');
	}		
	else if(angleToTurn>=180)
	{
		mover2.actuateRearMotors('6');
		mover2.actuateFrontMotors('6');
		mover2.actuateRearMotors('1');
		mover2.actuateFrontMotors('1');		

	}		
	else if(angleToTurn>90)
	{
		mover2.actuateRearMotors('4');
		mover2.actuateFrontMotors('4');
		mover2.actuateRearMotors('3');
		mover2.actuateFrontMotors('3');				
	}
	else
	{
		mover2.actuateRearMotors('4');
		mover2.actuateRearMotors('3');
		//Free Spin
		mover2.actuateFrontMotors('5');
		mover2.actuateFrontMotors('2');		
	}


	int newHeadingAngle = magneticSensor2.getHeadingAngle();
	Serial.print("Current Angle (degrees): ");Serial.print(newHeadingAngle);
	Serial.print("Should be (degrees): ");Serial.println(shouldBeAngle);
	
	int newAngle = shouldBeAngle - newHeadingAngle;	
	Serial.print("So Next Turn (degrees): ");Serial.println(newAngle);
	
	newAngle = adjustAngleValue(newAngle);
	if(!newAngle<angleTolerance || !newAngle>(360-angleTolerance)) 
	{
		turnToAngle(shouldBeAngle);	
	}
	return 1;
}

int NRover2IntelligentMover::adjustAngleValue(int angle)
{
	if(angle>360)
		angle = angle - 360;	
	else if(angle<0)
		angle = 360 + angle;
	
	if(angle>360||angle<0)
		return adjustAngleValue(angle);
	
	return angle;
		
}
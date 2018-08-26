#include "NRover2Mover.h" //include the declaration for this class

extern HardwareSerial* printer;


// 1 -Motor 1 Left
// 2 -Motor 1 Stop
// 3 -Motor 1 Right
// 4 -Motor 2 Left
// 5 -Motor 2 Stop
// 6 -Motor 2 Right


// Rear Motor 1
int dir1PinA = 53;
int dir2PinA = 52;
int speedPinA = 2; // Needs to be a PWM pin to be able to control motor speed
// Rear Motor 2
int dir1PinB = 51;
int dir2PinB = 50;
int speedPinB = 3; // Needs to be a PWM pin to be able to control motor speed
// Front Motor 1
int dir1PinD = 49;
int dir2PinD = 48;
int speedPinD = 4; // Needs to be a PWM pin to be able to control motor speed
// Front Motor 2
int dir1PinC = 47;
int dir2PinC = 46;
int speedPinC = 5; // Needs to be a PWM pin to be able to control motor speed

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
	//Define L298N Dual H-Bridge Motor Controller Pins
	pinMode(dir1PinA,OUTPUT);
	pinMode(dir2PinA,OUTPUT);
	pinMode(speedPinA,OUTPUT);
	pinMode(dir1PinB,OUTPUT);
	pinMode(dir2PinB,OUTPUT);
	pinMode(speedPinB,OUTPUT);
	pinMode(dir1PinC,OUTPUT);
	pinMode(dir2PinC,OUTPUT);
	pinMode(speedPinC,OUTPUT);
	pinMode(dir1PinD,OUTPUT);
	pinMode(dir2PinD,OUTPUT);
	pinMode(speedPinD,OUTPUT);	
}


void NRover2Mover::printSensorDetails(void)
{
  	printer->println("------------------------------------");
  	printer->print  ("Output:       "); printer->println("Rear Motor Driver : ");
  	printer->print  ("Output:       "); printer->println("Front Motor Driver : "); 	
  	printer->println("------------------------------------");
  	printer->println("");
  	delay(500);
}

void NRover2Mover::printStatus(void)
{
  	printer->println("------------------------------------");
  	printer->println("------------------------------------");
}

int NRover2Mover::move(int direction)
{
	switch (direction) 
	{
      // Forward
      case '1':
		actuateRearMotors('1');
		actuateRearMotors('4');	
		actuateFrontMotors('1');
		actuateFrontMotors('4');
        break;
	  // Free Spin
      case '2':
		actuateRearMotors('5');
		actuateRearMotors('2');	
		actuateFrontMotors('5');
		actuateFrontMotors('2');
        break;		
	  // Reverse
      case '3':
		actuateRearMotors('6');
		actuateRearMotors('3');	
		actuateFrontMotors('6');
		actuateFrontMotors('3');
        break;
	}
}

int NRover2Mover::turn(int angle)
{
	Serial.println("Turning"+angle);
	if(angle<5);
	if(angle<180)
	{
		actuateRearMotors('1');
		actuateRearMotors('6');
	}
	else
	{
		actuateRearMotors('3');
		actuateRearMotors('4');
	}
}

void NRover2Mover::actuateRearMotors(int inByte)
{
    switch (inByte) 
	{
      //______________Motor 1______________

      case '1': // Motor 1 Forward
        analogWrite(speedPinA, 255);//Sets speed variable via PWM
        digitalWrite(dir1PinA, LOW);
        digitalWrite(dir2PinA, HIGH);
        Serial.println("Motor 1 Forward"); // Prints out “Motor 1 Forward” on the serial monitor
        break;

      case '2': // Motor 1 Stop (Freespin)
        analogWrite(speedPinA, 0);
        digitalWrite(dir2PinA, LOW);
        digitalWrite(dir1PinA, HIGH);
        Serial.println("Motor 1 Stop");
        break;

      case '3': // Motor 1 Reverse
        analogWrite(speedPinA, 255);
        digitalWrite(dir1PinA, HIGH);
        digitalWrite(dir2PinA, LOW);
        Serial.println("Motor 1 Reverse");
        break;

      //______________Motor 2______________

      case '4': // Motor 2 Forward
        analogWrite(speedPinB, 255);
        digitalWrite(dir1PinB, LOW);
        digitalWrite(dir2PinB, HIGH);
        Serial.println("Motor 2 Forward");
        break;

      case '5': // Motor 1 Stop (Freespin)7j 
        analogWrite(speedPinB, 0);
        digitalWrite(dir1PinB, LOW);
        digitalWrite(dir2PinB, HIGH);
        Serial.println("Motor 2 Stop");
        break;

      case '6': // Motor 2 Reverse
        analogWrite(speedPinB, 255);
        digitalWrite(dir1PinB, HIGH);
        digitalWrite(dir2PinB, LOW);
        Serial.println("Motor 2 Reverse");
        break;

      default:
        // turn all the connections off if an unmapped key is pressed:
        for (int thisPin = 2; thisPin < 11; thisPin++) {
          digitalWrite(thisPin, LOW);
        }
    }
}

void NRover2Mover::actuateFrontMotors(int inByte)
{
    switch (inByte) 
	{
      //______________Motor 3______________

      case '1': // Motor 3 Forward
        analogWrite(speedPinC, 255);//Sets speed variable via PWM
        digitalWrite(dir1PinC, LOW);
        digitalWrite(dir2PinC, HIGH);
        Serial.println("Motor 3 Forward"); 
        break;

      case '2': // Motor 3 Stop (Freespin)
        analogWrite(speedPinC, 0);
        digitalWrite(dir2PinC, LOW);
        digitalWrite(dir1PinC, HIGH);
        Serial.println("Motor 3 Stop");
        break;

      case '3': // Motor 3 Reverse
        analogWrite(speedPinC, 255);
        digitalWrite(dir1PinC, HIGH);
        digitalWrite(dir2PinC, LOW);
        Serial.println("Motor 3 Reverse");
        break;

      //______________Motor 4______________

      case '4': // Motor 2 Forward
        analogWrite(speedPinD, 255);
        digitalWrite(dir2PinD, LOW);
        digitalWrite(dir1PinD, HIGH);
        Serial.println("Motor 4 Forward");
        break;

      case '5': // Motor 1 Stop (Freespin)
        analogWrite(speedPinD, 0);
        digitalWrite(dir2PinD, LOW);
        digitalWrite(dir1PinD, HIGH);
        Serial.println("Motor 4 Stop");
        break;

      case '6': // Motor 2 Reverse
        analogWrite(speedPinD, 255);
        digitalWrite(dir2PinD, HIGH);
        digitalWrite(dir1PinD, LOW);
        Serial.println("Motor 4 Reverse");
        break;

      default:
        // turn all the connections off if an unmapped key is pressed:
        for (int thisPin = 2; thisPin < 11; thisPin++) {
          digitalWrite(thisPin, LOW);
        }
    }
}
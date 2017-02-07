#include "NRover2SensorCPU.h" //include the declaration for this class

HardwareSerial* printer;

//<<constructor>> 
NRover2SensorCPU::NRover2SensorCPU(HardwareSerial* print)
{
	printer = print;
}

//<<destructor>>
NRover2SensorCPU::~NRover2SensorCPU()
{
	/*nothing to destruct*/
}

void NRover2SensorCPU::start(void)
{

}


void NRover2SensorCPU::printSensorDetails(void)
{

}

void NRover2SensorCPU::printStatus(void)
{

}


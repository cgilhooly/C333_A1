#include "Pump.h"

Pump::Pump(CRendezvous* r, string dp_name, string pipe_name, string semaphore_name, FuelTankMonitor* ftm) 
{
	Rendezvous = r;
	PumpDataPool = new CDataPool(dp_name, 1024);
	PumpStatusPtr = (PumpStatusStruct *) (PumpDataPool->LinkDataPool());
	PipeFromCustomer = new CTypedPipe<CustomerInfoStruct>(pipe_name, 1024);
	//PipeMutex = new CMutex(pipe_name);
	Monitor = ftm;
	string CSemaphoreName = semaphore_name + "CS";
	string PSemaphoreName = semaphore_name + "PS";
	CS = new CSemaphore(CSemaphoreName, 1);
	PS = new CSemaphore(CSemaphoreName, 0);
}

int Pump::main()
{
	printf("arriving at rendevous \n");
	Rendezvous->Wait();
	printf("go\n");
	PipeFromCustomer->Read(InfoReceived); // pump put to sleep if no info is read
	printf("got info from first customer\n");
	PumpStatusPtr->CI = *InfoReceived;
	//PumpStatusPtr->ReadyToFuel = false;

	//ready for next customer
	return 0;
}

Pump::~Pump() 
{
	delete PumpDataPool;
	delete PipeFromCustomer;
	//delete PipeMutex;
	delete CS;
	delete PS;
}
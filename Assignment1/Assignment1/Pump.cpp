#include "Pump.h"

Pump::Pump(CRendezvous* r, string dp_name, string pipe_name, FuelTankMonitor* ftm) 
{
	Rendezvous = r;
	PumpDataPool = new CDataPool(dp_name, 1024);
	PumpStatusPtr = (PumpStatusStruct *) (PumpDataPool->LinkDataPool());
	PipeFromCustomer = new CTypedPipe<CustomerInfoStruct>(pipe_name, 1024);
	PipeMutex = new CMutex(pipe_name, 1);
	Monitor = ftm;
}

int Pump::main()
{
	printf("arriving at rendevous \n");
	Rendezvous->Wait();
	printf("go\n");
	PipeMutex->Wait();
	PipeFromCustomer->Read(InfoReceived);
	PumpStatusPtr->CI = *InfoReceived;
	PumpStatusPtr->ReadyToFuel = false;



	PipeMutex->Signal();
	return 0;
}
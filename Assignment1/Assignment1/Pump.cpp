#include "Pump.h"

Pump::Pump(CRendezvous* r, string dp_name, string pipe_name, FuelTankMonitor* ftm) 
{
	Rendezvous = r;
	PumpDataPool = new CDataPool(dp_name, 1024);
	PipeFromCustomer = new CTypedPipe<CustomerInfoStruct>(pipe_name, 1024);
	Monitor = ftm;
}

int Pump::main()
{
	printf("arriving at rendevous \n");
	Rendezvous->Wait();
	printf("go\n");
	return 0;
}
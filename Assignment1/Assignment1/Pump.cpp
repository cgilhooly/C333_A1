#include "Pump.h"

Pump::Pump(CRendezvous* r, int pump_num) 
{
	Rendezvous = r;
	PumpDataPool = new CDataPool("PumpStatus" + to_string(pump_num), sizeof(PumpStatusStruct));
	PumpStatusPtr = (PumpStatusStruct *) (PumpDataPool->LinkDataPool());
	PipeFromCustomer = new CTypedPipe<CustomerInfoStruct>("Pipe"+ to_string(pump_num), 1);
	//PipeMutex = new CMutex(pipe_name);
	string CSemaphoreName = "Pump" + to_string(pump_num) + "CS";
	string PSemaphoreName = "Pump" + to_string(pump_num) + "PS";
	CS = new CSemaphore(CSemaphoreName, 1);
	PS = new CSemaphore(CSemaphoreName, 0);
}

int Pump::main()
{
	FuelTankMonitor Monitor = FuelTankMonitor("Monitor");
	//printf("arriving at rendevous \n");
	//Rendezvous->Wait();
	//printf("go\n");
	CustomerInfoStruct x;
	while(true) {
			PipeFromCustomer->Read(&x); // pump put to sleep if no info is read
			printf("customer1 info at pump: %s \n", x.Name.c_str());
	//		CS->Wait();
	//		PumpStatusPtr->CI = *InfoReceived; // write to datapool
	//		PS->Signal();
	//		printf("pump waiting for permission to proceed...\n");
	//		//wait for permission to start filling
	//		while (Monitor->GetPumpStatus(1) == false) {}
	//		printf("pump 1 ready to fuel!\n");
	//		Monitor->SetPumpNotReady(1);
	//		Sleep(5000);
	//		printf("pump1 finished pumping \n");
	//		printf("pump1 ready for next customer \n");
	}
	
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
#include "rt.h"
//#include "Customer.h"
#include "Pump.h"


//THIS IS GSC
// signal pump authorized to go on command
int main() 
{
	// initialize monitor
	FuelTankMonitor Monitor = FuelTankMonitor("Monitor");
	Monitor.Init(MAX_VOLUME, MAX_VOLUME, MAX_VOLUME, MAX_VOLUME);

	// create pump process
	CProcess p1("D:\\Visual_Studio_Project\\C++\\CPEN333 Labs\\Assignment1\\Assignment1\\Debug\\PumpsProcess.exe",	// pathlist to child program executable				
			NORMAL_PRIORITY_CLASS,			// priority
			OWN_WINDOW,						// process has its own window					
			ACTIVE							// process is active immediately
	);
	// create datapool and link to dp
	CDataPool PumpStatus1("PumpStatus1", sizeof(PumpStatusStruct));
	CDataPool PumpStatus2("PumpStatus2", sizeof(PumpStatusStruct));
	CDataPool PumpStatus3("PumpStatus3", sizeof(PumpStatusStruct));
	CDataPool PumpStatus4("PumpStatus4", sizeof(PumpStatusStruct));

	PumpStatusStruct* PumpStatus1Data = (PumpStatusStruct*) PumpStatus1.LinkDataPool();
	PumpStatusStruct* PumpStatus2Data = (PumpStatusStruct*) PumpStatus2.LinkDataPool();
	PumpStatusStruct* PumpStatus3Data = (PumpStatusStruct*) PumpStatus3.LinkDataPool();
	PumpStatusStruct* PumpStatus4Data = (PumpStatusStruct*) PumpStatus4.LinkDataPool();

	//semaphore for multiple producer(pumps) and single consumer(gsc)
	CSemaphore Pump1PS("Pump1PS", 0); // producer busy
	CSemaphore Pump1CS("Pump1CS", 1); // consumer free
	CSemaphore Pump2PS("Pump2PS", 0); // producer busy
	CSemaphore Pump2CS("Pump2CS", 1); // consumer free
	CSemaphore Pump3PS("Pump3PS", 0); // producer busy
	CSemaphore Pump3CS("Pump3CS", 1); // consumer free
	CSemaphore Pump4PS("Pump4PS", 0); // producer busy
	CSemaphore Pump4CS("Pump4CS", 1); // consumer free

	while (true) 
	{
		if (Pump1PS.Read() > 0) 
		{
			Pump1PS.Wait();
			// consume data from PumpStatusData1
			// wait for gsc to say go
			printf("pump1 data consumed\n");
			CSemaphore S("Pump1Authorized", 0, 1);
			S.Signal();
			//while (Monitor.GetPumpStatus(1) == false) 
			//{
			//	// waiting for permission to start fueling
			//}
			printf("pump1 can start fueling\\n");
			
			// update monitor to allow pump to go
			Pump1CS.Signal();
		}

		if (Pump2PS.Read() > 0) 
		{
			Pump2PS.Wait();
			printf("pump2 data consumed\n");
			printf("pump2 can start fueling\n");
			Pump2CS.Signal();
		}

		if (Pump3PS.Read() > 0) 
		{
			Pump3PS.Wait();
			Pump3CS.Signal();
		}

		if (Pump4PS.Read() > 0) 
		{
			Pump4PS.Wait();
			Pump4CS.Signal();
		}
		
	}
	p1.WaitForProcess();
	getchar();
	return 0;
}
#include "rt.h"
//#include "Customer.h"
#include "Pump.h"
FuelTankMonitor Monitor = FuelTankMonitor("Monitor");

UINT __stdcall newthread(void *args) {
	CSemaphore s1("mutex1", 1);
	char chars[3];
	CSemaphore S1("Pump1Authorized", 0, 1);
	CSemaphore S2("Pump2Authorized", 0, 1);
	CSemaphore S3("Pump3Authorized", 0, 1);
	CSemaphore S4("Pump3Authorized", 0, 1);

	while(true) {
		MOVE_CURSOR(0, 0);
		scanf("%s", chars);
		MOVE_CURSOR(0, 0);
		printf("          ");
		MOVE_CURSOR(0, 1);

		printf("chars = %s         ", chars);
		fflush(stdout);

		//GSC commands- add a third line to print out the effect of the command the user has input
		

		switch (chars[0]) {
			case 'O':
				if (chars[1] == 'S'); {
					fopen("example.csv", "r"); //need to print list
				} 
				break;
			case 'P':
				switch (chars[1]) {
					case '1':
						S1.Signal();
						break;
					case '2':
						S2.Signal();
						break;
					case '3':
						S3.Signal();
						break;
					case '4':;
						S4.Signal();
						break;
				}
				break;
			case 'R':
				if (chars[1] = 'T');
					Monitor.Refill();
				break;
		}

		MOVE_CURSOR(0, 0);
		chars[0] = 0;
		chars[1] = 0;
		chars[2] = 0;
	}
	return 0;
}

//THIS IS GSC
// signal pump authorized to go on command
int main() 
{
	CThread new1(newthread, ACTIVE, NULL); // thread for reading keyboard
	// initialize monitor
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
			//printf("pump1 data consumed\n");
			//CSemaphore S("Pump1Authorized", 0, 1);
			//S.Signal();
			//while (Monitor.GetPumpStatus(1) == false) 
			//{
			//	// waiting for permission to start fueling
			//}
			//printf("pump1 can start fueling\\n");
			
			// update monitor to allow pump to go
			Pump1CS.Signal();
		}

		if (Pump2PS.Read() > 0) 
		{
			Pump2PS.Wait();
			//printf("pump2 data consumed\n");
			//printf("pump2 can start fueling\n");
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
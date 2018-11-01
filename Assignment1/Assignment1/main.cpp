#include "rt.h"
//#include "Customer.h"
#include "Pump.h"

UINT __stdcall UpdatePumpStatusThread(void *args) 
{
	CRendezvous* R = (CRendezvous*)args;
	printf("arriving at rendevous \n");
	R->Wait();
	printf("go\n");

	// read tank
	//update pump stats
	return 0;
}


int main() 
{
	CRendezvous Rendezvous("Rend", 5);
	FuelTankMonitor Monitor = FuelTankMonitor(MAX_VOLUME, MAX_VOLUME, MAX_VOLUME, MAX_VOLUME);
	string PipeName1 = "Pipe1";
	string PipeName2 = "Pipe2";
	string PipeName3 = "Pipe3";
	string PipeName4 = "Pipe4";
	Pump P1 (&Rendezvous, "PumpStatus1", PipeName1, &Monitor);
	Pump P2 (&Rendezvous, "PumpStatus2", PipeName2, &Monitor);
	Pump P3 (&Rendezvous, "PumpStatus3", PipeName3, &Monitor);
	Pump P4 (&Rendezvous, "PumpStatus4", PipeName4, &Monitor);
	CThread UpdatePumpStatus(UpdatePumpStatusThread, SUSPENDED, &Rendezvous);

	P1.Resume();
	P2.Resume();
	Sleep(1000);
	P3.Resume();
	P4.Resume();
	UpdatePumpStatus.Resume();

	getchar();
	return 0;
}
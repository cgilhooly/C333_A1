#include "rt.h"
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
	FuelTankMonitor Monitor = FuelTankMonitor("Monitor");

	CRendezvous Rendezvous("Rend", 5);

	string PipeName1 = "Pipe1";
	string PipeName2 = "Pipe2";
	string PipeName3 = "Pipe3";
	string PipeName4 = "Pipe4";

	Pump P1 (&Rendezvous, "PumpStatus1", PipeName1, "Pump1",  &Monitor);
	Pump P2 (&Rendezvous, "PumpStatus2", PipeName2, "Pump2", &Monitor);
	Pump P3 (&Rendezvous, "PumpStatus3", PipeName3, "Pump3", &Monitor);
	Pump P4 (&Rendezvous, "PumpStatus4", PipeName4, "Pump4", &Monitor);
	CThread UpdatePumpStatus(UpdatePumpStatusThread, SUSPENDED, &Rendezvous);

	P1.Resume();
	P2.Resume();
	P3.Resume();
	P4.Resume();
	UpdatePumpStatus.Resume();
	printf("volume of eco is %f \n", Monitor.ReadVolume(Economy));
	getchar();
}
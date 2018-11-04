#include "rt.h"
#include "Pump.h"
#include "Customer.h"


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
	CRendezvous Rendezvous("Rend", 2);

	string PipeName1 = "Pipe1";
	string PipeName2 = "Pipe2";
	string PipeName3 = "Pipe3";
	string PipeName4 = "Pipe4";

	Pump P1 (&Rendezvous, 1);
	Pump P2 (&Rendezvous, 2);
	//Pump P3 (&Rendezvous, "PumpStatus3", PipeName3, "Pump3", &Monitor);
	//Pump P4 (&Rendezvous, "PumpStatus4", PipeName4, "Pump4", &Monitor);
//	CThread UpdatePumpStatus(UpdatePumpStatusThread, SUSPENDED, &Rendezvous);

	
	// create 5 customer for pump 1
	Customer c1 = Customer("customer1", Economy, 111, 10, PipeName1);
	Customer c2 = Customer("cus2", Economy, 222, 10, PipeName2);
	Customer c3 = Customer("cus3", Economy, 222, 10, PipeName1);
	Customer c4 = Customer("cus4", Economy, 222, 10, PipeName1);
	Customer c5 = Customer("cus5", Economy, 222, 10, PipeName1);
	c1.Resume();
	c2.Resume();
	c3.Resume();
	/*c4.Resume();
	c5.Resume();
*/

	P1.Resume();
	P2.Resume();
	//P3.Resume();
	//P4.Resume();
	//UpdatePumpStatus.Resume();

	P1.WaitForThread();
	/*P2.WaitForThread();
	P3.WaitForThread();
	P4.WaitForThread();*/
	c1.WaitForThread();
	/*c2.WaitForThread();
	c3.WaitForThread();
	c4.WaitForThread();
	c5.WaitForThread();*/
	getchar();
	return 0;
}
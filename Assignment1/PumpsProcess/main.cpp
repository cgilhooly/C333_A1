#include "rt.h"
#include "Pump.h"
#include "Customer.h"
//#include <string>
using namespace std;

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
	Pump P3 (&Rendezvous, 3);
	Pump P4 (&Rendezvous, 4);
//	CThread UpdatePumpStatus(UpdatePumpStatusThread, SUSPENDED, &Rendezvous);

	
	// create 5 customer for pump 1
	
	Customer* CustomerList[40];
	for (int i = 0; i < 10; i++) 
	{
		string n = "Customer" + to_string(i);
		CustomerList[i] = new Customer(n, Economy,222, 20, PipeName1);
	}
	for (int i = 10; i < 20; i++) 
	{
		string name = "customer" + to_string(i);
		CustomerList[i] = new Customer(name, Economy, 32, 20, PipeName2);
	}
	for (int i = 20; i < 30; i++) 
	{
		string name = "customer" + to_string(i);
		CustomerList[i] = new Customer(name, Economy, 5, 20, PipeName3);
	}
	for (int i = 30; i < 40; i++) 
	{
		string name = "customer" + to_string(i);
		CustomerList[i] = new Customer(name, Economy,435, 20, PipeName4);
	}

	for (int i = 0; i < 40; i++) 
	{
		CustomerList[i]->Resume();
	}

	P1.Resume();
	P2.Resume();
	P3.Resume();
	P4.Resume();
	//UpdatePumpStatus.Resume();

	P1.WaitForThread();
	P2.WaitForThread();
	P3.WaitForThread();
	P4.WaitForThread();
	for (int i = 0; i < 40; i++) 
	{
		CustomerList[i]->WaitForThread();
	}
	getchar();
	return 0;
}
#pragma once
#include "rt.h"
#include "Customer.h"
typedef struct PumpStatusStruct PumpStatus;

struct PumpStatusStruct {
	CustomerInfoStruct CI;
	//bool ReadyToFuel;
};

class Pump : public ActiveClass
{
private:
	CMutex* WindowMutex;
	CDataPool *PumpDataPool;
	PumpStatusStruct *PumpStatusPtr;
	CustomerInfoStruct InfoReceived;
	CTypedPipe<CustomerInfoStruct>* PipeFromCustomer;
	CRendezvous *Rendezvous;
	//CMutex *PipeMutex;
	CSemaphore* CS;
	CSemaphore* PS;
	int PumpNum = 0;
	string FormatPumpStatusMessage(CustomerInfoStruct D);
	void PrintToWindow(string s);
	FuelTankMonitor* Monitor;
public:
	Pump(CRendezvous* r, int pump_num);
	int main();
	void Withdraw(FuelType type);
	~Pump();
};
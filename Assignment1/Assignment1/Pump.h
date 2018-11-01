#pragma once
#include "rt.h"
#include "Customer.h"
typedef struct PumpStatusStruct PumpStatus;

struct PumpStatusStruct {
	CustomerInfoStruct CI;
	bool ReadyToFuel;
};

class Pump : public ActiveClass
{
	CDataPool *PumpDataPool;
	PumpStatusStruct *PumpStatusPtr;
	CTypedPipe<CustomerInfoStruct>* PipeFromCustomer;
	FuelTankMonitor* Monitor;
	CRendezvous *Rendezvous;
public:
	Pump(CRendezvous* r, string dp_name, string pipe_name, FuelTankMonitor* ftm);
	int main();
};
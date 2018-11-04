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
	CDataPool *PumpDataPool;
	PumpStatusStruct *PumpStatusPtr;
	CustomerInfoStruct *InfoReceived;
	CTypedPipe<CustomerInfoStruct>* PipeFromCustomer;
	CRendezvous *Rendezvous;
	//CMutex *PipeMutex;
	CSemaphore* CS;
	CSemaphore* PS;
public:
	Pump(CRendezvous* r, int pump_num);
	int main();
	~Pump();
};
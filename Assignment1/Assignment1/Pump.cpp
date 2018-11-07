#include "Pump.h"
#include "FuelTankMonitor.h"

Pump::Pump(CRendezvous* r, int pump_num) 
{
	PumpNum = pump_num;
	Rendezvous = r;
	PumpDataPool = new CDataPool("PumpStatus" + to_string(pump_num), sizeof(PumpStatusStruct));
	PumpStatusPtr = (PumpStatusStruct *) (PumpDataPool->LinkDataPool());
	PipeFromCustomer = new CTypedPipe<CustomerInfoStruct>("Pipe"+ to_string(pump_num), 1);
	string CSemaphoreName = "Pump" + to_string(pump_num) + "CS";
	string PSemaphoreName = "Pump" + to_string(pump_num) + "PS";
	CS = new CSemaphore(CSemaphoreName, 1);
	PS = new CSemaphore(PSemaphoreName, 0);
	WindowMutex = new CMutex("WindowMutex");
	Monitor = new FuelTankMonitor("Monitor");
}

int Pump::main()
{
	//printf("arriving at rendevous \n");
	//Rendezvous->Wait();
	//printf("go\n");
	int c = 0;
	while(true) {

		string s = "Pump" + to_string(PumpNum) + "Entry";
		CSemaphore Entry(s, 0, 1);
		Entry.Signal();// allow next customer to entry

		PipeFromCustomer->Read(&InfoReceived); // pump put to sleep if no info is read
		PrintToWindow(FormatPumpStatusMessage(InfoReceived));
		CS->Wait();
		PumpStatusPtr->CI = InfoReceived; // write to datapool
		PS->Signal();

		while (Monitor->GetPumpStatus(PumpNum) == false) {}// waiting for gsc permission

		string PumpReady = "Pump" + to_string(PumpNum) + "Ready";
		CSemaphore Ready(PumpReady, 0, 1);
		Ready.Signal();


		string StartStr = "Pump" + to_string(PumpNum) + "Start";
		CSemaphore Start(StartStr, 0, 1);
		Start.Wait();
		int withdraw_count = InfoReceived.Amount / 0.5;
		for (int i = 0; i < withdraw_count; i++) 
		{
			Monitor->Withdraw(InfoReceived.TypeOfGas);
			Sleep(1000);
		}

		string ReturnStr = "Pump" + to_string(PumpNum) + "ReturnHose";
		CSemaphore Return(ReturnStr, 0, 1);
		Return.Wait();

		string FinishStr = "Pump" + to_string(PumpNum) + "Finish";
		CSemaphore Finish(FinishStr, 0, 1);
		Finish.Signal(); // wait for customer to return hose and leave
		MOVE_CURSOR(0, 25);
		printf("pump init %d \n", c);
		fflush(stdout);
		c++;
		Monitor->SetPumpNotReady(1); // pump is not ready for next customer

	}
	
	//ready for next customer
	return 0;
}
string Pump::FormatPumpStatusMessage(CustomerInfoStruct D) 
{
	string str1 = "Pump" + to_string(PumpNum) + "\n";
	string str2 = "Customer Name: " + D.Name + "\n";
	string str3 = "Customer Card Number: " + to_string(D.CardNum) + "\n";
	string str4 = "Fuel Grade: " + FuelTankMonitor::FuelTypeToString(D.TypeOfGas) + "\n";
	string str5 = "Amount: " + to_string(D.Amount) + "\n";
	string result = str2 + str3 + str4 + str5;
	return result;
}

void Pump::Withdraw(FuelType type) 
{
	Monitor->Withdraw(type);
}

void Pump::PrintToWindow(string s) 
{
	int start_y = 5 * (PumpNum - 1);
	WindowMutex->Wait();
	MOVE_CURSOR(0, start_y);
	for (int i = 0; i < 5; i++) {
		for (int i = 0; i < 30; i++) {
			printf(" ");
		}
		printf("\n");
		fflush(stdout);
	}
	MOVE_CURSOR(0, start_y);
	printf("%s \n", s.c_str());
	fflush(stdout);
	MOVE_CURSOR(0, 0);
	WindowMutex->Signal();
}

Pump::~Pump() 
{
	delete PumpDataPool;
	delete PipeFromCustomer;
	//delete PipeMutex;
	delete CS;
	delete PS;
	delete WindowMutex;
	delete Monitor;
}
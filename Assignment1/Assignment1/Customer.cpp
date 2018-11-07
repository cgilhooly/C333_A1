#include "Customer.h"

Customer::Customer(string Name, FuelType type_of_gas, int card_num, float amount, int pipe_num)
{
	CustomerInfo.Name = Name;
	CustomerInfo.TypeOfGas = type_of_gas;
	CustomerInfo.CardNum = card_num;
	CustomerInfo.Amount = amount;
	if (CustomerInfo.Amount > 70) 
	{
		CustomerInfo.Amount = 70;
	}
	CustomerInfo.PipeNum = pipe_num;
	string pipe_name = "Pipe" + to_string(pipe_num);
	Pipe = new CTypedPipe<CustomerInfoStruct>(pipe_name, 1);
	PipeMutex = new CMutex(pipe_name);
}
void Customer::TestPipe() 
{
	//CTypedPipe<CustomerInfoStruct> P(, 1024);
	//CustomerInfoStruct i;
	//P.Read(&i);
	//printf("I read name %d from the pipe\n", i);
}

int Customer::main() 
{
	string s = "Pump" + to_string(CustomerInfo.PipeNum) + "Entry";
	CSemaphore Entry(s, 0, 1);
	Entry.Wait();
	//arriving in line
	//printf("%s is waiting in line \n", CustomerInfo.Name.c_str());
	PipeMutex->Wait();
	//printf("%s is swiping credit card info for verification \n", CustomerInfo.Name.c_str());
	Pipe->Write(&CustomerInfo); // put to sleep if no space to write
	PipeMutex->Signal();
	// customer waiting for attendant to response
	string PumpReadyStr = "Pump" + to_string(CustomerInfo.PipeNum) + "Ready";
	CSemaphore Ready(PumpReadyStr, 0, 1);
	Ready.Wait();

	// customer selecting fuelgrade and start fueling
	string StartStr = "Pump" + to_string(CustomerInfo.PipeNum) + "Start";
	CSemaphore Start(StartStr, 0, 1);
	Start.Signal();

	// customer returning hose
	string ReturnHoseStr = "Pump" + to_string(CustomerInfo.PipeNum) + "ReturnHose";
	CSemaphore Return(ReturnHoseStr, 0, 1);
	Return.Signal();
	
	// customer leaving
	string FinishStr = "Pump" + to_string(CustomerInfo.PipeNum) + "Finish";
	CSemaphore Finish(FinishStr, 0, 1);
	Finish.Wait();
	return 0;
}

Customer::~Customer() 
{
	delete PipeMutex;
}
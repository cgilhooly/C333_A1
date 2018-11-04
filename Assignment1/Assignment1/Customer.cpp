#include "Customer.h"
#include <string>

Customer::Customer(string Name, FuelType type_of_gas, int card_num, float amount, string pipe_name)
{
	CustomerInfo.Name = Name;
	CustomerInfo.TypeOfGas = type_of_gas;
	CustomerInfo.CardNum = card_num;
	CustomerInfo.Amount = amount;
	CustomerInfo.PipeName = pipe_name;
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
	//arriving in line
		printf("customer running\n");
		//PipeMutex->Wait();
		// swipe credit card
		Pipe->Write(&CustomerInfo); // put to sleep if no space to write
		//PipeMutex->Signal();
	return 0;
}

Customer::~Customer() 
{
	delete PipeMutex;
}
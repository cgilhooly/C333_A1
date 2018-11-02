#include "Customer.h"
#include <string>

Customer::Customer(string Name, FuelType type_of_gas, int card_num, float amount, string pipe_name)
{
	CustomerInfo.Name = Name;
	CustomerInfo.TypeOfGas = type_of_gas;
	CustomerInfo.CardNum = card_num;
	CustomerInfo.Amount = amount;
	CustomerInfo.PipeName = pipe_name;
	Pipe = new CTypedPipe<CustomerInfoStruct>(pipe_name, 1024);
	Pipe->Write(&CustomerInfo);
	PipeMutex = new CMutex(pipe_name, 0);
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
	PipeMutex->Wait();
	//send info through pipe
	PipeMutex->Signal();
	return 0;
}

Customer::~Customer() 
{
	delete PipeMutex;
}
#include "Customer.h"

Customer::Customer(int num) 
{
	int n = num;
	Customer::TestNum = num;
	Pipe = new CTypedPipe<int>("Pipe1", 1024);
	Pipe->Write(&n);
}

Customer::Customer(string Name, FuelType type_of_gas, int card_num, float amount, int pump_num)
{
	CustomerInfo.Name = Name;
	CustomerInfo.TypeOfGas = type_of_gas;
	CustomerInfo.CardNum = card_num;
	CustomerInfo.Amount = amount;
	CustomerInfo.PumpNum = pump_num;
}
void Customer::TestPipe() 
{
	CTypedPipe<int> P("Pipe1", 1024);
	int i;
	P.Read(&i);
	printf("I read %d from the pipe\n", i);
}
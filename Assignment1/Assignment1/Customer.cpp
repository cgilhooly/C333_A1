#include "Customer.h"
#include <string>

Customer::Customer(string Name, FuelType type_of_gas, int card_num, float amount, int pump_num)
{
	CustomerInfo.Name = Name;
	CustomerInfo.TypeOfGas = type_of_gas;
	CustomerInfo.CardNum = card_num;
	CustomerInfo.Amount = amount;
	CustomerInfo.PumpNum = pump_num;
	string s = "Pipe" + to_string(pump_num);
	Pipe = new CTypedPipe<CustomerInfoStruct>(s, 1024);
	Pipe->Write(&CustomerInfo);
}
void Customer::TestPipe() 
{
	string s = "Pipe" + to_string(CustomerInfo.PumpNum);
	CTypedPipe<CustomerInfoStruct> P(s, 1024);
	CustomerInfoStruct i;
	P.Read(&i);
	printf("I read name %d from the pipe\n", i);
}
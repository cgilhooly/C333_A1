#pragma once
#include "rt.h"
#include "FuelTankMonitor.h"
using namespace std;
typedef struct CustomerInfoStruct CustomerInfoStruct;
struct CustomerInfoStruct
{
	string Name;
	FuelType TypeOfGas;
	int CardNum;
	float Amount;
	int PipeNum;
};

class Customer : public ActiveClass {
	CTypedPipe<CustomerInfoStruct>* Pipe;
	CMutex* PipeMutex;
	int TestNum;
	CustomerInfoStruct CustomerInfo;

public:
	Customer(string Name, FuelType type_of_gas, int card_num, float amount, int pipe_num);
	int main();
	~Customer();
};
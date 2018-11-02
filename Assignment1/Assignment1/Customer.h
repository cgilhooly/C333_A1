#pragma once
#include "rt.h"
#include <iostream>
#include "FuelTankMonitor.h"
using namespace std;
typedef struct CustomerInfoStruct CustomerInfoStruct;
struct CustomerInfoStruct
{
	string Name;
	FuelType TypeOfGas;
	int CardNum;
	float Amount;
	string PipeName;
};

class Customer : public ActiveClass {
	CTypedPipe<CustomerInfoStruct>* Pipe;
	CMutex* PipeMutex;
	int TestNum;
	CustomerInfoStruct CustomerInfo;

public:
	Customer(string Name, FuelType type_of_gas, int card_num, float amount, string pump_name);
	void TestPipe();
	int main();
	~Customer();
};
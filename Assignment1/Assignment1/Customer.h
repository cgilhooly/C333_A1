#pragma once
#include "rt.h"
#include <iostream>
#include "FuelTank.h"
using namespace std;
typedef struct CustomerInfoStruct CustomerInfoStruct;
struct CustomerInfoStruct
{
	string Name;
	FuelType TypeOfGas;
	int CardNum;
	float Amount;
	int PumpNum;
};

class Customer {
	CTypedPipe<CustomerInfoStruct>* Pipe;
	int TestNum;
	CustomerInfoStruct CustomerInfo;
public:
	Customer(string Name, FuelType type_of_gas, int card_num, float amount, int pump_num);
	void TestPipe();
};
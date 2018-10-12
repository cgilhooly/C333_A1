#pragma once
#include "rt.h"
#include <stdio.h>
#include "FuelTank.h"
typedef struct CustomerInfo CustomerInfoStruct;
struct CustomerInfo 
{
	string Name;
	FuelType TypeOfGas;
	int CardNum;
	float Amount;
	int PumpNum;
};

class Customer {
	CTypedPipe<int>*	Pipe;
	int TestNum;
	CustomerInfoStruct CustomerInfo;
public:
	Customer(int num);
	Customer(string Name, FuelType type_of_gas, int card_num, float amount, int pump_num);
	void TestPipe();
};
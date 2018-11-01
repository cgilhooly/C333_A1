#include "FuelTankMonitor.h"
#include <iostream>
using namespace std;
FuelTankMonitor::FuelTankMonitor(double eco_v, double reg_v, double ext_v, double pre_v) 
{
	EconomyDataPool = new CDataPool("FuelTypeDP", sizeof(FuelTankStruct));
	RegularDataPool = new CDataPool("FuelTypeDP", sizeof(FuelTankStruct));
	ExtraDataPool = new CDataPool("FuelTypeDP", sizeof(FuelTankStruct));
	PremiumDataPool = new CDataPool("FuelTypeDP", sizeof(FuelTankStruct));
	EconomyPtr = (FuelTankStruct *)(EconomyDataPool->LinkDataPool());
	RegularPtr = (FuelTankStruct *)(RegularDataPool->LinkDataPool());
	ExtraPtr = (FuelTankStruct *)(ExtraDataPool->LinkDataPool());
	PremiumPtr  = (FuelTankStruct *)(PremiumDataPool->LinkDataPool());
	EcoMutex = new CMutex("EcoMutex", 1);
	RegMutex = new CMutex("RegMutex", 1);
	ExtMutex = new CMutex("ExtMutex", 1);
	PreMutex = new CMutex("PreMutex", 1);

	EcoMutex->Wait();
	EconomyPtr ->Volume = eco_v;
	EcoMutex->Signal();

	RegMutex->Wait();
	RegularPtr ->Volume = reg_v;
	RegMutex->Signal();

	ExtMutex->Wait();
	ExtraPtr ->Volume = ext_v;
	ExtMutex->Signal();

	PreMutex->Wait();
	PremiumPtr->Volume = pre_v;
	PreMutex->Signal();
	
	
}
FuelTankMonitor::~FuelTankMonitor() 
{
	delete EconomyDataPool;
	delete RegularDataPool;
	delete ExtraDataPool;
	delete PremiumDataPool;
	delete EconomyPtr;
	delete RegularPtr;
	delete ExtraPtr;
	delete PremiumPtr;
	delete EcoMutex;
	delete RegMutex;
	delete ExtMutex;
	delete PreMutex;
}
void FuelTankMonitor::Refill() {
	EcoMutex->Wait();
	EconomyPtr->Volume = MAX_VOLUME;
	EcoMutex->Signal();

	RegMutex->Wait();
	RegularPtr->Volume = MAX_VOLUME;
	RegMutex->Signal();

	ExtMutex->Wait();
	ExtraPtr->Volume = MAX_VOLUME;
	ExtMutex->Signal();

	PreMutex->Wait();
	PremiumPtr->Volume = MAX_VOLUME;
	PreMutex->Signal();
}

void FuelTankMonitor::Withdraw(FuelType Type) {
	switch (Type) 
	{
		case Economy:
			EcoMutex->Wait();
			EconomyPtr->Volume -= 0.5;
			EcoMutex->Signal();
			break;
		case Regular:
			RegMutex->Wait();
			RegularPtr->Volume -= 0.5;
			RegMutex->Signal();
			break;
		case Extra:
			ExtMutex->Wait();
			ExtraPtr->Volume -= 0.5;
			ExtMutex->Signal();
			break;
		case Premium:
			PreMutex->Wait();
			PremiumPtr->Volume -= 0.5;
			PreMutex->Signal();
			break;
	}
}

double FuelTankMonitor::ReadVolume(FuelType Type) {
	double val;
	switch (Type) 
	{
		case Economy:
			EcoMutex->Wait();
			val = EconomyPtr->Volume;
			EcoMutex->Signal();
			return val;
			break;
		case Regular:
			RegMutex->Wait();
			val = RegularPtr->Volume;
			RegMutex->Signal();
			return val;
			break;
		case Extra:
			ExtMutex->Wait();
		    val = ExtraPtr->Volume;
			ExtMutex->Signal();
			return val;
			break;
		case Premium:
			PreMutex->Wait();
			val = PremiumPtr->Volume;
			PreMutex->Signal();
			return val;
			break;
	}
}

double FuelTankMonitor::ReadTotal() 
{
	double sum = EconomyPtr->Volume + RegularPtr->Volume + ExtraPtr->Volume + PremiumPtr->Volume;
	return sum;
}
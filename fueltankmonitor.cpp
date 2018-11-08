#include "FuelTankMonitor.h"
#include <iostream>
using namespace std;
FuelTankMonitor::FuelTankMonitor(string monitor_name) 
{
	MonitorDataPool = new CDataPool(monitor_name+"DP", sizeof(struct VolumeOfTanks)); 
	MonitorMutex = new CMutex(monitor_name + "Mutex");
	Data = (struct VolumeOfTanks*) (MonitorDataPool->LinkDataPool());
}

void FuelTankMonitor::Init(double eco_v, double reg_v, double ext_v, double pre_v, double price = 90)
{
	MonitorMutex->Wait();
	Data->Eco_V = eco_v;
	Data->Reg_V = reg_v;
	Data->Ext_V = ext_v;
	Data->Pre_V = pre_v;
	Price->Eco_P = (price - 2);
	Price->Reg_P = price;
	Price->Ext_P = (price + 2);
	Price->Pre_P = (price + 4);

	Data->P1ReadyToFill = false;
	Data->P2ReadyToFill = false;
	Data->P3ReadyToFill = false;
	Data->P4ReadyToFill = false;
	MonitorMutex->Signal();
}
FuelTankMonitor::~FuelTankMonitor() 
{
	delete MonitorDataPool;
	delete MonitorMutex;
}
void FuelTankMonitor::Refill() {
	MonitorMutex->Wait();
	Data->Eco_V = MAX_VOLUME;
	Data->Reg_V = MAX_VOLUME;
	Data->Ext_V = MAX_VOLUME;
	Data->Pre_V = MAX_VOLUME;
	MonitorMutex->Signal();
}

void FuelTankMonitor::Withdraw(FuelType Type) {
	switch (Type) 
	{
		case Economy:
			MonitorMutex->Wait();
			Data->Eco_V -= 0.5;
			MonitorMutex->Signal();
			break;
		case Regular:
			MonitorMutex->Wait();
			Data->Reg_V -= 0.5;
			MonitorMutex->Signal();
			break;
		case Extra:
			MonitorMutex->Wait();
			Data->Ext_V -= 0.5;
			MonitorMutex->Signal();
			break;
		case Premium:
			MonitorMutex->Wait();
			Data->Pre_V -= 0.5;
			MonitorMutex->Signal();
			break;
	}
}

double FuelTankMonitor::ReadVolume(FuelType Type) {
	double val;
	switch (Type) 
	{
		case Economy:
			MonitorMutex->Wait();
			val = Data->Eco_V;
			MonitorMutex->Signal();
			return val;
			break;
		case Regular:
			MonitorMutex->Wait();
			val = Data->Reg_V;
			MonitorMutex->Signal();
			return val;
			break;
		case Extra:
			MonitorMutex->Wait();
		    val = Data->Ext_V;
			MonitorMutex->Signal();
			return val;
			break;
		case Premium:
			MonitorMutex->Wait();
			val = Data->Pre_V;
			MonitorMutex->Signal();
			return val;
			break;
	}
}

double FuelTankMonitor::ReadTotal() 
{
	double sum = Data->Eco_V + Data->Ext_V + Data->Pre_V + Data->Reg_V;
	return sum;
}

void FuelTankMonitor::SetPrice(FuelType Type, double newprice) {
	switch (Type)
	{
	case Economy:
		MonitorMutex->Wait();
		Price->Eco_P = newprice;
		MonitorMutex->Signal();
		break;
	case Regular:
		MonitorMutex->Wait();
		Price->Reg_P = newprice;
		MonitorMutex->Signal();
		break;
	case Extra:
		MonitorMutex->Wait();
		Price->Ext_P = newprice;
		MonitorMutex->Signal();
		break;
	case Premium:
		MonitorMutex->Wait();
		Price->Pre_P = newprice;
		MonitorMutex->Signal();
		break;
	}
}

struct PriceOfFuel FuelTankMonitor::GetPrice() {
		struct PriceOfFuel returnprices;

		MonitorMutex->Wait();

		returnprices.Eco_P = Price->Eco_P;
		returnprices.Ext_P = Price->Ext_P;
		returnprices.Reg_P = Price->Reg_P;

		returnprices.Pre_P = Price->Pre_P;

		MonitorMutex->Signal();

		return returnprices;

}

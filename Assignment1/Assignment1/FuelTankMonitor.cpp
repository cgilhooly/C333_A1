#include "FuelTankMonitor.h"
#include <iostream>
using namespace std;
FuelTankMonitor::FuelTankMonitor(string monitor_name) 
{
	MonitorDataPool = new CDataPool(monitor_name+"DP", sizeof(struct VolumeOfTanks)); 
	MonitorMutex = new CMutex(monitor_name + "Mutex");
	Data = (struct VolumeOfTanks*) (MonitorDataPool->LinkDataPool());
}

void FuelTankMonitor::Init(double eco_v, double reg_v, double ext_v, double pre_v) 
{
	MonitorMutex->Wait();
	Data->Eco_V = eco_v;
	Data->Reg_V = reg_v;
	Data->Ext_V = ext_v;
	Data->Pre_V = pre_v;
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

bool FuelTankMonitor::GetPumpStatus(int which_pump) 
{
	bool status = false;
	switch (which_pump)
	{
	case 1:
		MonitorMutex->Wait();
		status = Data->P1ReadyToFill;
		MonitorMutex->Signal();
		break;
	case 2:
		MonitorMutex->Wait();
		status = Data->P2ReadyToFill;
		MonitorMutex->Signal();
		break;
	case 3:
		MonitorMutex->Wait();
		status = Data->P3ReadyToFill;
		MonitorMutex->Signal();

		break;
	case 4:
		MonitorMutex->Wait();
		status = Data->P4ReadyToFill;
		MonitorMutex->Signal();
		break;
	}
	return status;
}
void FuelTankMonitor::SetPumpReady(int which_pump) 
{
	switch (which_pump) 
	{
		case 1:
			MonitorMutex->Wait();
			Data->P1ReadyToFill = true;
			MonitorMutex->Signal();
			break;
		case 2:
			MonitorMutex->Wait();
			Data->P2ReadyToFill = true;
			MonitorMutex->Signal();
			break;
		case 3:
			MonitorMutex->Wait();
			Data->P3ReadyToFill = true;
			MonitorMutex->Signal();

			break;
		case 4:
			MonitorMutex->Wait();
			Data->P4ReadyToFill = true;
			MonitorMutex->Signal();
			break;
	}
}
void FuelTankMonitor::SetPumpNotReady(int which_pump) 
{
	switch (which_pump) 
	{
		case 1:
			MonitorMutex->Wait();
			Data->P1ReadyToFill = false;
			MonitorMutex->Signal();
			break;
		case 2:
			MonitorMutex->Wait();
			Data->P2ReadyToFill = false;
			MonitorMutex->Signal();
			break;
		case 3:
			MonitorMutex->Wait();
			Data->P3ReadyToFill = false;
			MonitorMutex->Signal();

			break;
		case 4:
			MonitorMutex->Wait();
			Data->P4ReadyToFill = false;
			MonitorMutex->Signal();
			break;
	}
}
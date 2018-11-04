#pragma once
#include "rt.h"
#define MAX_VOLUME 500
typedef struct FuelTankStruct FuelTankStruct;
enum FuelType {Economy, Regular, Extra, Premium};


class FuelTankMonitor
{
private:
	struct VolumeOfTanks 
	{
		double Eco_V;
		double Reg_V;
		double Ext_V;
		double Pre_V;
		bool P1ReadyToFill;
		bool P2ReadyToFill;
		bool P3ReadyToFill;
		bool P4ReadyToFill;
	};

	CDataPool* MonitorDataPool;
	struct VolumeOfTanks* Data;
	CMutex *MonitorMutex;
	

public:
	static string FuelTypeToString(FuelType F) 
	{
		switch (F) 
		{
			case Economy:
				return "Economy";
			case Regular:
				return "Regular";
			case Extra:
				return "Extra";
			case Premium:
				return "Premium";
			default:
				return "";
		}
	}
	FuelTankMonitor(string monitor_name);
	void Init(double eco_v, double reg_v, double ext_v, double pre_v);
	void Withdraw(FuelType Type);
	void Refill();
	double ReadVolume(FuelType Type);
	double ReadTotal();
	bool GetPumpStatus(int which_pump);
	void SetPumpReady(int which_pump);
	void SetPumpNotReady(int which_pump);
	~FuelTankMonitor();
};
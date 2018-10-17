#include "rt.h"
#define MAX_VOLUME 500
typedef struct FuelTankStruct FuelTankStruct;
enum FuelType {Economy, Regular, Extra, Premium};

struct FuelTankStruct
{
	double Volume;
};

class FuelTankMonitor
{
	CDataPool *EconomyDataPool;
	CDataPool *RegularDataPool;
	CDataPool *ExtraDataPool;
	CDataPool *PremiumDataPool;
	FuelTankStruct *EconomyPtr;
	FuelTankStruct *RegularPtr;
	FuelTankStruct *ExtraPtr;
	FuelTankStruct *PremiumPtr;
	CMutex  *EcoMutex;
	CMutex *RegMutex;
	CMutex *ExtMutex;
	CMutex *PreMutex;

public:
	FuelTankMonitor(double v0, double v1, double v2, double v3);
	void Withdraw(FuelType Type);
	void Refill();
	double ReadVolume(FuelType Type);
	double ReadTotal();
	~FuelTankMonitor();
};
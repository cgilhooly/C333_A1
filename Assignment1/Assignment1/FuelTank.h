#include "rt.h"
typedef struct FuelTypeStruct FuelType;
struct FuelTypeStruct
{
	int V0;
	int V1;
	int V2;
    int V3;
};

class FuelTank
{
	CDataPool *FTPool;

public:
	FuelTank(int v0, int v1, int v2, int v3);
	void TestDP();
};
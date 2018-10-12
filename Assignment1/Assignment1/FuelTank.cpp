#include "FuelTank.h"
#include <stdio.h>

FuelTank::FuelTank(int v0, int v1, int v2, int v3) 
{
	FTPool = new CDataPool("hi", sizeof(FuelType));
	FuelType *T = (FuelType *)(FTPool->LinkDataPool());
	T->V0 = v0;
	T->V1 = v1;
	T->V2 = v2;
	T->V3 = v3;
}

void FuelTank::TestDP() 
{
	CDataPool Pool("hi", sizeof(FuelType));
	FuelType* F = (FuelType *)(Pool.LinkDataPool());
	printf("I read V0 = %d\n", F->V0);
	printf("I read V1 = %d\n", F->V1);
	printf("I read V2 = %d\n", F->V2);
	printf("I read V3 = %d\n", F->V3);
}
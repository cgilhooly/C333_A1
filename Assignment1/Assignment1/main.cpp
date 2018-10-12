#include "rt.h"
#include "Customer.h"


int main() 
{
	Customer C = Customer(10);
	C.TestPipe();
	getchar();

	FuelTank F = FuelTank(10, 10, 20, 30);
	F.TestDP();
	getchar();
	return 0;
}
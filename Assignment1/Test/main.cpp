#include "rt.h"
#include "Customer.h"
#include "Pump.h"
UINT __stdcall ReadFromPipe(void* args)
{
	int i;
	CTypedPipe<int> P = CTypedPipe<int>("pipe", 1);
	while (true)
	{
		P.Read(&i);
		printf("child thread read %d from pipe 10\n", i);
	}
	return 0;
}
int main() 
{
	/*Customer C1 = Customer("name", Economy, 0, 1.0f, "Pipe1");
	Pump P1 = Pump("PumpStatus1", 1);
	printf("hello world\n");
	C1.Resume();
	P1.Resume();
	getchar();*/
	return 0;
}
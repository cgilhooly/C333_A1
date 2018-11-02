#include "rt.h"
//#include "Customer.h"
#include "Pump.h"




int main() 
{
	FuelTankMonitor Monitor = FuelTankMonitor(MAX_VOLUME, MAX_VOLUME, MAX_VOLUME, MAX_VOLUME);
	CProcess p1("D:\\Visual_Studio_Project\\C++\\CPEN333 Labs\\Assignment1\\Assignment1\\Debug\\PumpsProcess.exe",	// pathlist to child program executable				
			NORMAL_PRIORITY_CLASS,			// priority
			OWN_WINDOW,						// process has its own window					
			ACTIVE							// process is active immediately
	);
	// create pump process

	getchar();
	return 0;
}
// GSIO.cpp : Defines the entry point for the console application.
//

#include 	<stdio.h>		
#include 	"rt.h"
#include <iostream>
#include <fstream>
#include <cstdlib>


#define EMPTY  0;
#define AVAILABLE  1;
#define MAXVOLUME 700;


UINT __stdcall newthread(void *args) {
	CSemaphore s1("mutex1", 1);
	char chars[3];
	for (int i = 0; i < 1000; i++) {

		MOVE_CURSOR(0, 0);
		scanf("%s", chars);
		MOVE_CURSOR(0, 0);
		printf("          ");
		MOVE_CURSOR(0, 1);

		printf("chars = %s         ", chars);
		fflush(stdout);

		//GSC commands- add a third line to print out the effect of the command the user has input


		switch (chars[0]) {
		case 'O':
			if (chars[1] == 'S'); {
				fopen("example.csv", "r"); //need to print list
			} break;
		case 'P':
			switch (chars[1]) {
			case '1':
				CSemaphore S("Pump1Authorized" 0, 1);
				S.Signal();
				break;
			case '2':
				CSemaphore S("Pump2Authorized" 0, 1);
				S.Signal();
				break;
			case '3':
				CSemaphore S("Pump3Authorized" 0, 1);
				S.Signal();
				break;
			case '4':;
				CSemaphore S("Pump3Authorized" 0, 1);
				S.Signal();
				break;
			}
			break;
		case 'R':
			if (chars[1] = 'T');
			//fueltankmonitor->refill
			break;
		}

		MOVE_CURSOR(0, 0);
		chars[0] = 0;
		chars[1] = 0;
		chars[2] = 0;


	}
	return 0;
}

COORD GetConsoleCursorPosition(HANDLE hConsoleOutput)
{
	CONSOLE_SCREEN_BUFFER_INFO cbsi;
	if (GetConsoleScreenBufferInfo(hConsoleOutput, &cbsi))
	{
		return cbsi.dwCursorPosition;
	}
	else
	{
		// The function failed. Call GetLastError() for details.
		COORD invalid = { 0, 0 };
		return invalid;
	}
}

struct customer {  //modify to match definition inside rest of project
	int type;
	long long int card;
};

//UINT __stdcall printthread(void *args);
//{
//
//	s1.Wait();
//	cord = GetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE));
//	MOVE_CURSOR(0, 10);
//	printf("Pump 1 customer info \n", i);
//	printf("Fuel type: %d \n", c1.type);
//	printf("Card number: %lld", c1.card);
//	fflush(stdout);
//	MOVE_CURSOR(cord.X, cord.Y);
//	s1.Signal();
//
//}


void main() {
	CThread new1(newthread, ACTIVE, NULL);

	//CThread print1(printthread, ACTIVE, NULL);
	//CThread print2(printthread, ACTIVE, NULL);
	//CThread print3(printthread, ACTIVE, NULL);
	//CThread print4(printthread, ACTIVE, NULL);



	CSemaphore s1("mutex1", 1);

	COORD cord;

	customer c1;
	c1.type = 91;
	c1.card = 4444333322221111;

	customer c2;
	c2.type = 90;
	c2.card = 4444333322221111;

	customer c3;
	c3.type = 93;
	c3.card = 4444333322221111;

	customer c4;
	c4.type = 95;
	c4.card = 4444333322221111;

	int pump1status = AVAILABLE;
	int pump1volume = MAXVOLUME;
	int pump2status = AVAILABLE;
	int pump2volume = MAXVOLUME;
	int pump3status = AVAILABLE;
	int pump3volume = MAXVOLUME;
	int pump4status = AVAILABLE;
	int pump4volume = MAXVOLUME;

	SLEEP(1000); //allow the getchars to begin first


	for (int i = 0; i < 1000; i++) {

		//the display of each pump will need to be split into separate threads, to handle asynchronous customer flow

		s1.Wait();
		cord = GetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE));
		MOVE_CURSOR(0, 10);
		printf("Pump 1 customer info \n", i);
		printf("Fuel type: %d \n", c1.type);
		printf("Card number: %lld", c1.card);
		fflush(stdout);
		MOVE_CURSOR(cord.X, cord.Y);
		s1.Signal();
		std::ofstream myfile;
		myfile.open("example.csv");
		myfile << "Customer " << 4 * i << ",\n"; // need to edit i to properly identify customer numbers!
		myfile << c1.type << "\n";
		myfile << c1.card << "\lld";
		myfile.close();

		s1.Wait();
		cord = GetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE));
		MOVE_CURSOR(0, 15);
		printf("Pump 2 customer info \n", i);
		printf("Fuel type: %d \n", c2.type);
		printf("Card number: %lld", c2.card);
		fflush(stdout);
		MOVE_CURSOR(cord.X, cord.Y);
		s1.Signal();

		myfile.open("example.csv");
		myfile << "Customer " << 4 * i << ",\n";
		myfile << c1.type << "\n";
		myfile << c1.card << "\lld";
		myfile.close();

		s1.Wait();
		cord = GetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE));
		MOVE_CURSOR(0, 20);
		printf("Pump 3 customer info \n", i);
		printf("Fuel type: %d \n", c3.type);
		printf("Card number: %lld", c3.card);
		fflush(stdout);
		MOVE_CURSOR(cord.X, cord.Y);
		s1.Signal();

		myfile.open("example.csv");
		myfile << "Customer " << 4 * i << ",\n";
		myfile << c1.type << "\n";
		myfile << c1.card << "\lld";
		myfile.close();

		s1.Wait();
		cord = GetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE));
		MOVE_CURSOR(0, 25);
		printf("Pump 4 customer info \n", i);
		printf("Fuel type: %d \n", c4.type);
		printf("Card number: %lld", c4.card);
		s1.Signal();

		MOVE_CURSOR(cord.X, cord.Y);

		myfile.open("example.csv");
		myfile << "Customer " << 4 * i << ",\n";
		myfile << c1.type << "\n";
		myfile << c1.card << "\lld";
		myfile.close();


		SLEEP(500);



	}



}

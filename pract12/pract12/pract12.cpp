// pract12.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

int main()
{
	ifstream fileIn("input5.txt");
	if (!fileIn.is_open())
	{
		return 1;
	}

	ofstream fileOut("output.txt");
	if (!fileOut.is_open())
	{
		return 1;
	}

	int N;
	fileIn >> N;
	for (size_t i = 0; i < N; ++i)
	{
		int x;
		int y;
		fileIn >> x >> y;
		fileOut << ((((x % 2) != 0) && ((y % 2) != 0)) ? 2 : 1) << endl;
	}

    return 0;
}


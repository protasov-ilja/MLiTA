// kvadrat.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{ 
	ifstream fileIn("input.txt");
	if (!fileIn.is_open())
	{
		cout << "Failed to open input.txt for reading\n";
		return 1;
	}

	ofstream fileOut("output.txt");
	if (!fileOut.is_open())
	{
		cout << "Failed to open output.txt for writing\n";
		return 1;
	}
	int n;
	cin >> n;

	int arrNum[100000];
	arrNum[0] = 0;
	arrNum[1] = 1;
	for (int i = 1; i <= n; ++i)
	{
		int min = 100000;
		for (int j = 1; j <= i; ++j)
		{
			if ((j * j) <= i)
			{
				int curr = 1 + arrNum[i - j * j];
				//cout << "curr" << curr <<" j " << j << " min " << min << endl;
				if (curr < min)
				{
					arrNum[i] = curr;
					min = curr;
				}
			}
		}
	}

	fileOut << arrNum[n];
	cout << arrNum[n];

    return 0;
}


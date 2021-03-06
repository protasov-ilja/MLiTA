// pract16.cpp : Defines the entry point for the console application.
// определить является ли арифметической прогрессей
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
	ifstream fileIn("in5.txt");
	if (!fileIn.is_open())
	{
		return 1;
	}

	ofstream fileOut("output.txt");
	if (!fileOut.is_open())
	{
		return 1;
	}

	int testsCount;
	fileIn >> testsCount;
	for (int i = 0; i < testsCount; ++i)
	{
		int elementsNumber;
		fileIn >> elementsNumber;
		if (elementsNumber == 1)
		{
			fileOut << "Yes" << endl;
		}
		else
		{
			bool isCorrect = true;
			vector<int> arifmP(elementsNumber);
			for (size_t j = 0; j < arifmP.size(); ++j)
			{
				fileIn >> arifmP[j];
			}

			sort(arifmP.begin(), arifmP.end());
			int d = arifmP[1] - arifmP[0];
			for (int k = 1; k < arifmP.size(); ++k)
			{
				if ((arifmP[0] + d * k) != arifmP[k])
				{
					isCorrect = false;
					break;
				}
			}

			fileOut << (isCorrect ? "Yes" : "No") << endl;
		}
	}
	
    return 0;
}

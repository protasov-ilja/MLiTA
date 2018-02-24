// balls.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char* argv[])
{
	//ifstream fileIn("input.txt");
	//ifstream fileIn("input1.txt");
	//ifstream fileIn("empty.txt");
	//ifstream fileIn("oneArrow.txt");
	ifstream fileIn("moreArrows21.txt");
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
	
	int ballsNumber;
	if (!fileIn.eof())
	{
		fileIn >> ballsNumber;
	}
	else
	{ 
		cout << "Error file is empty" << endl;
		return 1;
	}

	if ((ballsNumber > 1000000) || (ballsNumber < 1))
	{
		cout << "Error N is less then 1 or more than 1000000" << endl;
		return 1;
	}
	
	char ballsArray[1000000];
	char ch;
	
	for (int i = 0; i < ballsNumber; ++i) 
	{
		if (!fileIn.eof())
		{
			fileIn >> ch;
			ballsArray[i] = ch;
		}
		else
		{
			cout << "argument is less then N" << endl;
			return 1;
		}
	}

	int begArr = 0;
	int endArr = ballsNumber;
	bool isСollision = true;
	int countCollision = 0;
	int counter = 0;
	while (isСollision)
	{
		cout << counter << endl;
		for (int i = 0; i < ballsNumber; ++i)
		{
			cout << ballsArray[i];
		}
		cout << endl;
		isСollision = false;

		int i = begArr;
		while ((ballsArray[i] == '<') && (i < ballsNumber))
		{
			cout << "i " << i << endl;
			i++;
		}

		begArr = i;
		int j = endArr - 1;

		while ((ballsArray[j] == '>') && (j >= 0))
		{
			cout << "j " << j << endl;
			j--;
		}
		endArr = j + 1;

		while (i < endArr)
		{
			if ((ballsArray[i] == '>') && ((i + 1) < endArr) && (ballsArray[i + 1] == '<'))
			{
				ballsArray[i] = '<';
				ballsArray[i + 1] = '>';
				countCollision++;
				cout << "Сollision" << countCollision << endl;
				isСollision = true;
			}
			++i;
		}
		counter++;
	}

	cout << countCollision << endl;
	fileOut << countCollision << endl;

	return 0;
}
// pract7.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <algorithm>

using namespace std;

bool CreateNewTransposition(vector<int>& numbersVector, vector<int>& newVector, int vectorLength);
void ReadVector(std::vector<int>& numbersVector);

int main()
{
	vector<int> numbersVector;
	ReadVector(numbersVector);
	int vectorLength = numbersVector.size();
	const int MAX_TRANSPOSITION = 5;
	int countTransposition = 0;
	bool isFound = true;
	vector<int> newVector(numbersVector.size());
	while ((countTransposition < MAX_TRANSPOSITION) && isFound)
	{
		isFound = CreateNewTransposition(numbersVector, newVector, vectorLength);
		if (isFound)
		{
			copy(numbersVector.begin(), numbersVector.end(), ostream_iterator<int>(cout, " "));
			cout << endl;
		}

		countTransposition++;
	}

    return 0;
}

void ReadVector(std::vector<int>& numbersVector)
{
	copy(std::istream_iterator<int>(std::cin), std::istream_iterator<int>(), back_inserter(numbersVector));
}

bool CreateNewTransposition(vector<int>& numbersVector, vector<int>& newVector, int vectorLength)
{
	int i = vectorLength - 1;
	while ((i - 1 >= 0) && (numbersVector[i - 1] >= numbersVector[i]))
	{
		i--;
		if (i - 1 < 0)
		{
			return false;
		}
	}

	// найти эл-т от i + 1 до len со значением больше i но самого наименьшего среди них
	int minNum = 100;
	int minCord = -1;
	for (int j = i; j < vectorLength; ++j)
	{
		if ((numbersVector[j] > numbersVector[i - 1]) && (numbersVector[j] < minNum))
		{
			minNum = numbersVector[j];
			minCord = j;
		}
	}

	if (minCord != -1)
	{
		int buf = numbersVector[i - 1];
		numbersVector[i - 1] = numbersVector[minCord];
		numbersVector[minCord] = buf;
		int x = i;
		for (int j = 0; j < i; ++j)
		{
			newVector[j] = numbersVector[j];
		}

		for (int j = vectorLength - 1; j > i - 1; --j)
		{
			newVector[j] = numbersVector[x];
			++x;
		}

		numbersVector = newVector;
	}
	else
	{
		return false;
	}

	return true;
}
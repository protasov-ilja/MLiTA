// pract5.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
	std::ifstream fileIn("input.txt");
	std::ofstream fileOut("output.txt");
	int M;
	int N;
	fileIn >> M;
	fileIn >> N;
	int number;
	std::vector<int> sellers;
	for (int i = 0; i < M; ++i)
	{
		fileIn >> number;
		sellers.push_back(number);
	}
	sort(sellers.begin(), sellers.end());

	std::vector<int> clients;
	for (int i = 0; i < N; ++i)
	{
		fileIn >> number;
		clients.push_back(number);
	}
	sort(clients.begin(), clients.end());
	int j = 0;
	int maxSum = 0;
	int maxPrice = 0;
	int currSum;
	int currPrice;
	int currCountSellers;
	int currCountClients;
	while (j < N)
	{
		currSum = 0;
		currPrice = 0;
		currCountClients = 0;
		while ((j < N) && (currPrice >= sellers[0]))
		{

		}

		currPrice = clients[j];
		int i = 0;
		while ((i < M) && (currPrice >= sellers[i]))
		{
			currCountSellers++;
			++i;
		}

		currSum = currPrice * min((j + 1), currCountSellers);
		if (currSum > maxSum)
		{
			maxPrice = currPrice;
			maxSum = currSum;
		}

		++j;
	}

	cout << maxSum << " " << maxPrice << endl;

    return 0;
}


// pract14.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

const string EXIT_COMMAND = "Exit";
const string UPDATE_COMMAND = "Update(";
const string RSQ_COMMAND = "Rsq(";

void CommandHandler(int arrLen, vector<int>& fanvicTree, const vector<int>& initArray);
int Rsq(int k, vector<int>& fanvicTree);
int CountRsq(int i, int j, vector<int>& fanvicTree);
void Update(int k, int d, vector<int>& fanvicTree);

int main()
{
	ifstream fileIn("input.txt");
	if (!fileIn.is_open())
	{
		return 1;
	}

	ofstream fileOut("output.txt");
	if (!fileOut.is_open())
	{
		return 1;
	}

	int arrLen;
	fileIn >> arrLen;
	vector<int> fanvicTree(arrLen, 0);
	vector<int> initArray(arrLen);
	for (size_t i = 0; i < initArray.size(); ++i)
	{
		fileIn >> initArray[i];
	}

	for (int i = 0; i < fanvicTree.size(); ++i)
	{
		Update(i, initArray[i], fanvicTree);
	}

	CommandHandler(arrLen, fanvicTree, initArray);

    return 0;
}

void CommandHandler(int arrLen, vector<int>& fanvicTree, const vector<int>& initArray)
{
	std::string commandLine;
	bool wasExit = false;
	while (!wasExit)
	{
		getline(cin, commandLine);
		std::istringstream strm(commandLine);

		std::string action;
		strm >> action;

		if (action == EXIT_COMMAND)
		{
			return;
		} 
		else if (action == RSQ_COMMAND)
		{
			char c;
			int i;
			int j;
			strm >> i >> c >> j;
			cout << CountRsq(i, j, fanvicTree) << endl;
		}
		else if (action == UPDATE_COMMAND)
		{
			char c;
			int k;
			int d;
			strm >> k >> c >> d;
			Update(k, d, fanvicTree);
		}
	}
}

int Rsq(int k, vector<int>& fanvicTree)
{
	int res = 0;
	while (k >= 0)
	{
		res += fanvicTree[k];
		k = (k & (k + 1)) - 1;
	}

	return res;
}

int CountRsq(int i, int j, vector<int>& fanvicTree)
{
	return Rsq(j, fanvicTree) - Rsq(i - 1, fanvicTree);
}

void Update(int k, int d, vector<int>& fanvicTree)
{
	while (k < fanvicTree.size())
	{
		fanvicTree[k] += d;
		k = k | (k + 1);
	}
}
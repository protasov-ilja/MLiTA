// pract9.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stack>

using namespace std;

bool GetUnvisited(vector<int> visited, int& x);

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

	int K;
	fileIn >> K;
	vector<vector<int> > points(K, vector<int>(K));

	for (size_t i = 0; i < points.size(); ++i)
	{
		int doctorNumber;
		fileIn >> doctorNumber;
		if (doctorNumber != 0)
		{
			for (size_t j = 0; j < doctorNumber; ++j)
			{
				int doctor;
				fileIn >> doctor;
				points[doctor - 1][i] = 1;
			}
		}
	}
	
	int withoutParents = -1;
	for (size_t i = 0; i < points.size(); ++i)
	{
		int parents = 0;
		for (size_t j = 0; j < points.size(); ++j)
		{
			if (points[j][i] != 0)
			{
				++parents;
			}
		}

		if (parents == 0)
		{
			withoutParents = i;
		}
	}

	cout << withoutParents << endl;

	if (withoutParents == -1)
	{
		fileOut << "No" << endl;
		return 0;
	}

	vector<int> visited(K, 0);
	vector<int> result;
	int i;
	while (GetUnvisited(visited, i))
	{
		while (!myStack.empty())
		{
			i = myStack.top();
			
			size_t j = 0;
			while (j < points.size())
			{
				if (points[i][j] != 0)
				{
					points[i][j] = 0;
					if (visited[j] == 0)
					{
						myStack.push(j);
					}
				}
				else 
				{
					++j;
				}
			}

			if (j == points.size())
			{
				visited[i] = 1;
				if (visited[myStack.top()] == 0)
				{
					result.push_back(myStack.top());
				}
				
				myStack.pop();
			}
		}
	}
	
	for (size_t i = 0; i < points.size(); ++i)
	{
		cout << result[i];
	}

	cout << endl;
	for (size_t i = 0; i < points.size(); ++i)
	{
		for (size_t j = 0; j < points.size(); ++j)
		{
			cout << points[i][j];
		}

		cout << endl;
	}

    return 0;
}

bool GetUnvisited(vector<int> visited, int& x)
{
	for (int i = 0; i < visited.size(); ++i)
	{
		if (visited[i] == 0)
		{
			x = i;
			return true;
		}
	}

	return false;
}
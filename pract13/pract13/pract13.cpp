// pract13.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <queue>
#include <vector>

using namespace std;

struct Point
{
	int x;
	int y;
};

struct PointVirus
{
	Point currCord;
	int prior;
};

int findMinPath(const vector<Point>& viruses, std::vector<std::vector<int>>& arrayOfSteps);
void CreateNewStack(PointVirus currStep, std::vector<std::vector<int>>& arrayOfSteps, queue<PointVirus>& queueOfNextSteps);

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

	int n;
	int m;
	fileIn >> n >> m;
	n += 2;
	int maxPrior = n * n + 1;
	std::vector<std::vector<int>> arrayOfSteps(n, std::vector<int>(n, maxPrior));
	for (size_t i = 0; i < arrayOfSteps.size(); ++i)
	{
		arrayOfSteps[0][i] = 1;
		arrayOfSteps[arrayOfSteps.size() - 1][i] = 1;
		arrayOfSteps[i][0] = 1;
		arrayOfSteps[i][arrayOfSteps.size() - 1] = 1;
	}

	std::vector<Point> viruses(m);
	for (size_t i = 0; i < viruses.size(); ++i)
	{
		fileIn >> viruses[i].x >> viruses[i].y;
	}

	cout << findMinPath(viruses, arrayOfSteps) << endl;
	
    return 0;
}

int findMinPath(const vector<Point>& viruses, std::vector<std::vector<int>>& arrayOfSteps)
{
	queue<PointVirus> queueOfNextSteps;
	for (size_t i = 0; i < viruses.size(); ++i)
	{
		queueOfNextSteps.push({ viruses[i], 0});
	}
	
	while (!queueOfNextSteps.empty())
	{
		PointVirus currStep = queueOfNextSteps.front();
		queueOfNextSteps.pop();
		CreateNewStack(currStep, arrayOfSteps, queueOfNextSteps);
	}

	int max = 0;
	for (size_t i = 1; i < arrayOfSteps.size() - 1; ++i)
	{
		for (size_t j = 1; j < arrayOfSteps.size() - 1; ++j)
		{
			if (arrayOfSteps[i][j] > max)
			{
				max = arrayOfSteps[i][j];
			}
		}	
	}

	return max;
}

void CreateNewStack(PointVirus currStep, std::vector<std::vector<int>>& arrayOfSteps, queue<PointVirus>& queueOfNextSteps)
{
	int newPrior = currStep.prior + 1;
	if (newPrior < arrayOfSteps[currStep.currCord.y + 1][currStep.currCord.x])
	{
		queueOfNextSteps.push({ currStep.currCord.x, currStep.currCord.y + 1, newPrior });
		arrayOfSteps[currStep.currCord.y + 1][currStep.currCord.x] = newPrior;
	} 

	if (newPrior < arrayOfSteps[currStep.currCord.y - 1][currStep.currCord.x])
	{
		queueOfNextSteps.push({ currStep.currCord.x, currStep.currCord.y - 1, newPrior });
		arrayOfSteps[currStep.currCord.y - 1][currStep.currCord.x] = newPrior;
	}

	if (newPrior < arrayOfSteps[currStep.currCord.y][currStep.currCord.x + 1])
	{
		queueOfNextSteps.push({ currStep.currCord.x + 1, currStep.currCord.y, newPrior });
		arrayOfSteps[currStep.currCord.y][currStep.currCord.x + 1] = newPrior;
	}

	if (newPrior < arrayOfSteps[currStep.currCord.y][currStep.currCord.x - 1])
	{
		queueOfNextSteps.push({ currStep.currCord.x - 1, currStep.currCord.y, newPrior });
		arrayOfSteps[currStep.currCord.y][currStep.currCord.x - 1] = newPrior;
	}
}
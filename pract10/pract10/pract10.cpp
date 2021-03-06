// pract10.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <stack>

struct Point
{
	size_t x;
	size_t y;
};


int findMaxAmountOfBushes(const std::vector<std::vector<bool>>& arrayOfBushes, int maxResult, std::ofstream& fileOut);
int findPath(std::vector<std::vector<bool>> arrayOfBushes, Point currPos, std::ofstream& fileOut);

int main()
{
	std::ifstream fileIn("input6.txt");
	if (!fileIn.is_open())
	{
		std::cout << "filed to open for reading";
		return 1;
	}

	std::ofstream fileOut("output.txt");
	if (!fileOut.is_open())
	{
		std::cout << "filed to open for writing";
		return 1;
	}

	int N;
	int M;
	int maxResult = 0;
	fileIn >> M >> N;
	N += 2;
	M += 2;
	std::vector<std::vector<bool>> arrayOfBushes(M, std::vector<bool>(N, false));
	for (size_t i = 1; i < arrayOfBushes.size() - 1; ++i)
	{
		for (size_t j = 1; j < arrayOfBushes[0].size() - 1; ++j)
		{
			char ch;
			fileIn >> ch;
			if (ch == '#')
			{
				maxResult++;
				arrayOfBushes[i][j] = true;
			}
		}
	}

	int result = findMaxAmountOfBushes(arrayOfBushes, maxResult, fileOut);
	for (int i = 0; i < M; ++i)
	{
		for (int j = 0; j < N; ++j)
		{
			std::cout << arrayOfBushes[i][j];
		}
		std::cout << std::endl;
	}

	std::cout << result << std::endl;
		
    return 0;
}

int findMaxAmountOfBushes(const std::vector<std::vector<bool>>& arrayOfBushes, int maxResult, std::ofstream& fileOut)
{
	int maxBushes = 0;
	int result = 0;
	for (size_t i = 1; i < arrayOfBushes.size() - 1; ++i)
	{
		if (maxBushes < result)
		{
			maxBushes = result;
		}

		for (size_t j = 1; j < arrayOfBushes[0].size() - 1; ++j)
		{
			if (maxBushes < result)
			{
				maxBushes = result;
			}

			result = 0;
			if (maxResult == maxBushes)
			{
				break;
			}

			result = findPath(arrayOfBushes, {i, j}, fileOut);
		}
		 
		if (maxBushes < result)
		{
			maxBushes = result;
		}
	}

	return maxBushes;
}

int findPath(std::vector<std::vector<bool>> arrayOfBushes, Point currPos, std::ofstream& fileOut)
{
	std::stack<Point> stk;
	if (!arrayOfBushes[currPos.x][currPos.y])
	{
		return 0;
	}

	int result = 1;
	int maxResult = 1;
	stk.push({ currPos.x, currPos.y });
	arrayOfBushes[currPos.x][currPos.y] = false;
	while (!stk.empty())
	{
		if (arrayOfBushes[stk.top().x + 1][stk.top().y])
		{
			arrayOfBushes[stk.top().x + 1][stk.top().y] = false;
			stk.push({ stk.top().x + 1, stk.top().y });
			result++;
		} 
		else if (arrayOfBushes[stk.top().x - 1][stk.top().y])
		{
			arrayOfBushes[stk.top().x - 1][stk.top().y] = false;
			stk.push({ stk.top().x - 1, stk.top().y  });
			result++;
		}
		else if (arrayOfBushes[stk.top().x][stk.top().y + 1])
		{
			arrayOfBushes[stk.top().x][stk.top().y + 1] = false;
			stk.push({ stk.top().x, stk.top().y + 1});
			result++;
		}
		else if (arrayOfBushes[stk.top().x][stk.top().y - 1])
		{
			arrayOfBushes[stk.top().x][stk.top().y - 1] = false;
			stk.push({ stk.top().x, stk.top().y - 1});
			result++;
		} 
		else
		{
			

			result--;
			stk.pop();
		}

		if (result > maxResult)
		{
			maxResult = result;
		}

		std::cout << result << std::endl;
	}

	if (result > maxResult)
	{
		maxResult = result;
	}

	fileOut << maxResult << std::endl;

	return maxResult;
}
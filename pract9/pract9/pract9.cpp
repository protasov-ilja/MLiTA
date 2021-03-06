// pract9.cpp : Defines the entry point for the console application.
// Выполнил Протасов Илья ПС-21; VS2017

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

int main()
{
	std::ifstream fileIn("input.txt");
	if (!fileIn.is_open())
	{
		return 1;
	}

	std::ofstream fileOut("output.txt");
	if (!fileOut.is_open())
	{
		return 1;
	}

	int K;
	fileIn >> K;
	std::vector<std::vector<int> > points(K, std::vector<int>(K));
	for (size_t i = 0; i < points.size(); ++i)
	{
		int doctorNumber;
		fileIn >> doctorNumber;
		if (doctorNumber != 0)
		{
			for (int j = 0; j < doctorNumber; ++j)
			{
				int doctor;
				fileIn >> doctor;
				points[i][doctor - 1] = 1;
			}
		}
	}
	
	int withoutParents = -1;
	for (size_t i = 0; i < points.size(); ++i)
	{
		int parents = 0;
		for (size_t j = 0; j < points.size(); ++j)
		{
			if (points[i][j] != 0)
			{
				++parents;
			}
		}

		if (parents == 0)
		{
			withoutParents = i;
		}
	}

	if (withoutParents == -1)
	{
		fileOut << "NO" << std::endl;
		return 0;
	}

	std::vector<int> result;
	result.push_back(withoutParents);
	bool notChangesMade = false;
	while (!notChangesMade)
	{
		notChangesMade = true;
		for (size_t i = 0; i < points.size(); ++i)
		{
			for (size_t j = 0; j < points.size(); ++j)
			{
				if (points[i][j] == 1)
				{
					if (find(result.begin(), result.end(), j) != result.end())
					{
						points[i][j] = 0;
						notChangesMade = false;
					}
				}
			}

			if ((find(points[i].begin(), points[i].end(), 1) == points[i].end()) && (find(result.begin(), result.end(), i) == result.end()))
			{
				result.push_back(i);
			}
		}
	}

	if (result.size() != K)
	{
		fileOut << "NO" << std::endl;
		return 0;
	}

	fileOut << "YES" << std::endl;
	for (size_t i = 0; i < result.size(); ++i)
	{
		fileOut << result[i] + 1 << std::endl;
	}

    return 0;
}
// pract8.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <vector>

struct Point
{
	int x;
	int y;
};

bool CheckMulOfVectors(const Point& aVector, const Point& bVector);

int main()
{
	std::ifstream fileIn("in5.txt");
	std::ofstream fileOut("output.txt");
	int N;
	fileIn >> N;
	std::vector<Point> Points(N);
	for (size_t i = 0; i < Points.size(); ++i)
	{
		fileIn >> Points[i].x >> Points[i].y;
	}

	Point aVector;
	aVector.x = Points[1].x - Points[0].x;
	aVector.y = Points[1].y - Points[0].y;
	Point bVector;
	int countVector = 0;
	for (size_t i = 2; i < Points.size(); ++i)
	{
		Point bVector;
		bVector.x = Points[i].x - Points[i - 1].x;
		bVector.y = Points[i].y - Points[i - 1].y;
		if (CheckMulOfVectors(aVector, bVector))
		{
			++countVector;
		}

		aVector = bVector;
	}

	fileOut << countVector << std::endl;
    return 0;
}

bool CheckMulOfVectors(const Point& aVector, const Point& bVector)
{
	return (aVector.x * bVector.y - bVector.x * aVector.y) > 0;
}
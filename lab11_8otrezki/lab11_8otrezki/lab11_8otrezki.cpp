// lab11_8otrezki.cpp : Defines the entry point for the console application.
//11.8. Пересечение отрезков (5)
//Два отрезка на плоскости заданы целочисленными координатами своих концов в декартовой
//системе координат.Требуется определить, существует ли у них общая точка.
//Ввод из файла INPUT.TXT.В первой строке содержатся координаты первого конца первого
//отрезка, во второй - второго конца первого отрезка, в третьей и четвёртой - координаты концов
//второго отрезка.
//Вывод в файл OUTPUT.TXT.Выводится слово &quot; Yes&quot; , если общая точка есть, или слово &quot; No&quot; -
//в противном случае.
//Ограничения: координаты целые и по модулю не превосходят 10 000, время 1 с.
//	Примеры
//	Ввод 1 Ввод 2
//	0 0    0 0
//	1 0    1 0
//	1 0	   2 0
//	1 1	   3 0
//	Вывод 1 Вывод 2
//	Yes     No
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

short int ChekPosition(int pointPosition);
bool CheckIntersectionOfSegments(const std::vector<Point>& Points);
//test.bat "$(TargetPath)"

int main(int argc, char* argv[])
{
	std::ifstream fileIn("inputMax.txt");//argv[1]);
	if (!fileIn.is_open())
	{
		std::cout << "Failed to open input.txt for reading\n";
		return 1;
	}

	std::ofstream fileOut("output.txt");//"output.txt");argv[2]
	if (!fileOut.is_open())
	{
		std::cout << "Failed to open output.txt for writing\n";
		return 1;
	}
	
	std::vector<Point> Points(4);

	for (int i = 0; i < 4; ++i)
	{
		fileIn >> Points[i].x;
		fileIn >> Points[i].y;
		//std::cout << " x " << Points[i].x << " y " << Points[i].y << std::endl;
	}

	if (Points[0].x > Points[1].x)
	{
		//std::cout << "swap1" << std::endl;
		Point temp = Points[0];
		Points[0] = Points[1];
		Points[1] = temp;
	}

	if (Points[2].x > Points[3].x)
	{
		//std::cout << "swap2" << std::endl;
		Point temp = Points[2];
		Points[2] = Points[3];
		Points[3] = temp;
	}

	if (CheckIntersectionOfSegments(Points))
	{
		fileOut << "Yes";
		std::cout << "Yes" << std::endl;
	}
	else
	{
		//std::cout << "No" << std::endl;
		fileOut << "No";
	}

    return 0;
}

bool CheckIntersectionOfSegments(const std::vector<Point>& Points)
{
	if ((Points[1].x < Points[2].x) || (Points[0].x > Points[3].x))
	{
		//std::cout << "x" << std::endl;
		return false;
	}

	int maxY1 = Points[0].y < Points[1].y ? Points[1].y : Points[0].y;
	std::cout << "maxY1 " << maxY1 << std::endl;
	int maxY2 = Points[2].y < Points[3].y ? Points[3].y : Points[2].y;
	std::cout << "maxY1 " << maxY1 << std::endl;
	if (((maxY1 < Points[2].y) && (maxY1 < Points[3].y)) || ((maxY2 < Points[0].y) && (maxY1 < Points[1].y)))
	{
		//std::cout << "y" << std::endl;
		return false;
	}

	int pointPosition1 = (Points[2].x - Points[0].x) * (Points[1].y - Points[0].y) - (Points[2].y - Points[0].y) * (Points[1].x - Points[0].x);
	short p1 = ChekPosition(pointPosition1);
	int pointPosition2 = (Points[3].x - Points[0].x) * (Points[1].y - Points[0].y) - (Points[3].y - Points[0].y) * (Points[1].x - Points[0].x);
	short p2 = ChekPosition(pointPosition2);
	int pointPosition3 = (Points[0].x - Points[2].x) * (Points[3].y - Points[2].y) - (Points[0].y - Points[2].y) * (Points[3].x - Points[2].x);
	short p3 = ChekPosition(pointPosition3);
	int pointPosition4 = (Points[1].x - Points[2].x) * (Points[3].y - Points[2].y) - (Points[1].y - Points[2].y) * (Points[3].x - Points[2].x);
	short p4 = ChekPosition(pointPosition4);

	if ((p1 * p2 <= 0) && (p3 * p4 <= 0))
	{
		return true;
	}
	else 
	{
		//std::cout << "p" << std::endl;
		return false;
	}
}

short int ChekPosition(int pointPosition)
{
	if (pointPosition < 0)
	{
		return -1;
	}
	else if (pointPosition == 0)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}
// lab4.cpp : Defines the entry point for the console application.
//4.5. Маршрут (6)
//Дана матрица N x N, заполненная целыми положительными числами.Путь по матрице начинается в левом верхнем углу.За один ход можно пройти в соседнюю по вертикали или горизонтали клетку(если она существует).Нельзя ходить по диагонали, нельзя оставаться на месте.Требуется найти максимальную сумму чисел, стоящих в клетках по пути длиной K клеток(клетку можно посещать несколько раз).
//Ограничения: 2 ≤ N ≤ 20, элементы матрицы имеют значения от 1 до 9999, 1 ≤ K ≤ 20.
// Ввод из файла INPUT.TXT.В первой строке находятся разделенные пробелом числа N и K.Затем идут N строк по N чисел в каждой.
// Вывод в файл OUTPUT.TXT.Вывести в первой строке максимальную сумму.В следующих K строках – соответствующий маршрут в виде координат клеток.
//	Пример
//	Ввод            Вывод
//	5 7             21
//	1 1 1 1 1       1 1
//	1 1 3 1 9       1 2
//	1 1 6 1 1       1 3
//	1 1 3 1 1       2 3
//	1 1 1 1 1       3 3
//	                4 3
//                  3 3
//	Подсказка.В цикле по количеству клеток пути определить для каждой клетки, какое максимальное значение может быть получено в соседних с ней клетках с учетом предыдущих шагов.
// Выполнил студент группы ПС-21 Протасов Илья; VS2017

#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <vector>

struct Point
{
	int x;
	int y;
};

struct Cell
{
	int val = -1;
	std::vector<Point> returnPath;
};

const std::vector<Point> DIRECTION = { { 0, 1 }, { 0, -1 }, { 1, 0 }, { -1, 0 } };
int GetMaxSumOfCurrPath(const std::vector<std::vector<int>>& initField, int y, int x, std::vector<std::vector<Cell>>& arrOfMaxPath);

int main()
{
	std::ifstream fileIn("input.txt");
	if (!fileIn.is_open())
	{
		std::cout << "filed open for reading" << std::endl;
		return 1;
	}

	std::ofstream fileOut("output0.txt");
	if (!fileOut.is_open())
	{
		std::cout << "filed open for writing" << std::endl;
		return 1;
	}

	int maxLength;
	int maxStep;
	fileIn >> maxLength >> maxStep;
	std::vector<std::vector<int>> initField(maxLength, std::vector<int>(maxLength));
	for (size_t i = 0; i < initField.size(); ++i)
	{
		for (size_t j = 0; j < initField.size(); ++j)
		{
			fileIn >> initField[i][j];
		}
	}

	std::vector<std::vector<Cell>> arrOfMaxPath(maxLength, std::vector<Cell>(maxLength));
	arrOfMaxPath[0][0].val = initField[0][0];
	arrOfMaxPath[0][0].returnPath.push_back({ 0, 0 });
	std::vector<Point> maxPath;
	int maxSum = -1;
	Point maxSumPoint = {0, 0};
	for (int step = 0; step <= maxStep; ++step)
	{
		for (int i = 0; i < maxLength; ++i)
		{
			for (int j = 0; j < maxLength; ++j)
			{
				if ((i + j < step) && (((step % 2 == 0) && ((i + j) % 2 != 0)) || ((step % 2 != 0) && ((i + j) % 2 == 0))))
				{
					int newSum = GetMaxSumOfCurrPath(initField, i, j, arrOfMaxPath);
					if (maxSum < newSum)
					{
						maxSum = newSum;
						maxSumPoint.x = j;
						maxSumPoint.y = i;
						maxPath = arrOfMaxPath[i][j].returnPath;
					}
				}
			}
		}
	}

	Cell MaxPathCell = arrOfMaxPath[maxSumPoint.y][maxSumPoint.x];
	fileOut << MaxPathCell.val << "\n";
	for (size_t i = 0; i < MaxPathCell.returnPath.size(); ++i)
	{
		fileOut << MaxPathCell.returnPath[i].y + 1 << " " << MaxPathCell.returnPath[i].x + 1 << "\n";
	}

	return 0;
}

int GetMaxSumOfCurrPath(const std::vector<std::vector<int>>& initField, int y, int x, std::vector<std::vector<Cell>>& arrOfMaxPath)
{
	std::vector<Point> tmpMaxPath;
	int currMaxSum = -1;
	for (size_t i = 0; i < DIRECTION.size(); ++i)
	{
		if ((y + DIRECTION[i].y >= 0) && (y + DIRECTION[i].y < arrOfMaxPath.size()) && (x + DIRECTION[i].x >= 0) && (x + DIRECTION[i].x < arrOfMaxPath.size()))
		{
			int prevDirX = x + DIRECTION[i].x;
			int prevDirY = y + DIRECTION[i].y;
			if (arrOfMaxPath[prevDirY][prevDirX].val > currMaxSum)
			{
				currMaxSum = arrOfMaxPath[prevDirY][prevDirX].val;
				tmpMaxPath = arrOfMaxPath[prevDirY][prevDirX].returnPath;
				tmpMaxPath.push_back({ x, y });
			}
		}
	}

	if (currMaxSum != -1)
	{
		arrOfMaxPath[y][x].returnPath = tmpMaxPath;
		arrOfMaxPath[y][x].val = currMaxSum + initField[y][x];

		return arrOfMaxPath[y][x].val;
	}
	else
	{
		return currMaxSum;
	}
}

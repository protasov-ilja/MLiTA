// balls13_17.cpp : Defines the entry point for the console application.
// 14.17. Шары (5)
// По горизонтально расположенному желобу бесконечной длины катятся с одинаковой скоростью N металлических шаров(1 ≤ N ≤ 105).
// Некоторые шары катятся вправо, некоторые влево.Сталкиваясь, шары испытывают абсолютно упругое соударение(то есть меняют направление движения, 
// сохраняя скорость).Зная расположение шаров в желобе и направление их движения, сосчитать количество столкновений(соударений) пар шаров.
//  Ввод.Входной файл INPUT.TXT содержит одну строку.В ней символами «>» и «<» указаны направления движения шаров.
//	Вывод.В единственной строке файла OUTPUT.TXT требуется вывести число соударений.
//	 Примеры
//	 Ввод 1        Ввод 2
//	 7             5
//	 >><>>><       <<<>>
//	 Вывод 1       Вывод 2
//	 7             0
// Выполнил Протасов Илья студент ПС-21; Версия компилятора VS2017


#include "stdafx.h"
#include <ctime>
#include <fstream>
#include <iostream>


int main()
{
	time_t start, end;
	time(&start);
	std::ifstream fileIn("input.txt");
	if (!fileIn.is_open())
	{
		std::cout << "Failed to open input.txt for reading\n";
		return 1;
	}

	std::ofstream fileOut("output.txt");
	if (!fileOut.is_open())
	{
		std::cout << "Failed to open output.txt for writing\n";
		return 1;
	}

	int ballsNumber;
	if (!fileIn.eof())
	{
		fileIn >> ballsNumber;
	}
	else
	{
		return 1;
	}

	if ((ballsNumber > 1000000) || (ballsNumber < 1))
	{
		return 1;
	}

	char ballsArray[1000000];
	for (int i = 0; i < ballsNumber; ++i) 
	{
		if (!fileIn.eof())
		{
			fileIn >> ballsArray[i];
		}
		else
		{
			return 1;
		}
	}

	int begArr = 0;
	bool isСollision = true;
	int countCollision = 0;
	int i;
	int j = ballsNumber;
	bool checkNextRight = false;
	bool checkNextLeft = false;
	int countLeft;
	int countRight;
	while (isСollision)
	{
		isСollision = false;
		i = begArr;
		while ((i < ballsNumber) && (ballsArray[i] == '<'))
		{
			i++;
		}
		begArr = i;

		--j;
		while ((ballsArray[j] == '>') && (j >= 0))
		{
			--j;
		}

		++j;
		while (i < j)
		{
			if ((ballsArray[i] == '>') && ((i + 1) < j) && (ballsArray[i + 1] == '<'))
			{
				countCollision++;
				if (((i - 1) >= 0) && (ballsArray[i - 1] == '>'))
				{
					checkNextLeft = true;
					if (((i + 2) < j) && (ballsArray[i + 2] == '<')) // 100% что i и i+1 развернутся снова так: ><
					{
						countCollision++; // когда i и i+1 становятся <>
						checkNextRight = true;
						countLeft = 0;
					}

					int k = 2;
					countCollision++;
					while (((i - k) >= 0) && (ballsArray[i - k] == '>'))
					{
						if (checkNextRight)
						{
							countLeft++;
						}
						
						k++;
						countCollision++;
					}

					if ((checkNextRight) && (countLeft > 0))
					{
						countCollision += countLeft;
						ballsArray[i - countLeft] = '<';
					}
					else if (checkNextRight) // если i и i + 1 становятся <> но дальше i - 1 таких '>' нет
					{
						ballsArray[i] = '<';
					}

					ballsArray[i - k + 1] = '<';
				}
				else
				{
					ballsArray[i] = '<';
				}

				if (((i + 2) < j) && (ballsArray[i + 2] == '<'))
				{
					if (checkNextLeft)
					{
						countRight = 0;
					}

					int k = 3;
					countCollision++;
					while (((i + k) < j) && (ballsArray[i + k] == '<'))
					{
						if (checkNextLeft)
						{
							countRight++;
						}
						
						k++;
						countCollision++;
					}

					if ((checkNextLeft) && (countRight > 0))
					{
						countCollision += countRight;
						ballsArray[i + 1 + countRight] = '>';
					}
					else if (checkNextLeft) // если i и i + 1 становятся <> но дальше i - 1 таких '>' нет
					{
						ballsArray[i + 1] = '>';
					}

					ballsArray[i + k - 1] = '>';
					i += k - 1;
				}
				else
				{
					ballsArray[i + 1] = '>';
				}

				isСollision = true;
				checkNextLeft = false;
				checkNextRight = false;
			}
			++i;
		}
	}

	time(&end);
	std::cout << countCollision << std::endl;
	std::cout << difftime(end, start);
	return 0;
}

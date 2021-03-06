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
#include <fstream>
#include <iostream>

int main()
{
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

	int countCollisions = 0;
	int countRightArrow = 0;
	char ch;

	for (int i = 0; i < ballsNumber; ++i) 
	{
		if (!fileIn.eof())
		{
			fileIn >> ch;
			if (ch == '>')
			{
				countRightArrow++;
			}
			else
			{
				countCollisions += countRightArrow;
			}
		}
		else
		{
			return 1;
		}
	}

	fileOut << countCollisions << std::endl;
	return 0;
}

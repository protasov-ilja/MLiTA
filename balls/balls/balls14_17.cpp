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
#include <string>

using namespace std;

int main(int argc, char* argv[])
{
	ifstream fileIn("input.txt");
	if (!fileIn.is_open())
	{
		cout << "Failed to open input.txt for reading\n";
		return 1;
	}

	ofstream fileOut("output.txt");
	if (!fileOut.is_open())
	{
		cout << "Failed to open output.txt for writing\n";
		return 1;
	}
	
	int ballsNumber;
	if (!fileIn.eof())
	{
		fileIn >> ballsNumber;
	}
	else
	{ 
		cout << "Error file is empty" << endl;
		return 1;
	}

	if ((ballsNumber > 1000000) || (ballsNumber < 1))
	{
		cout << "Error N is less then 1 or more than 1000000" << endl;
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
			cout << "argument is less then N" << endl;
			return 1;
		}
	}

	int begArr = 0;
	int endArr = ballsNumber;
	bool isСollision = true;
	int countCollision = 0;
	while (isСollision)
	{
		isСollision = false;

		int i = begArr;
		while ((ballsArray[i] == '<') && (i < ballsNumber))
		{
			i++;
		}
		begArr = i;

		int j = endArr - 1;
		while ((ballsArray[j] == '>') && (j >= 0))
		{
			j--;
		}
		endArr = j + 1;

		while (i < endArr)
		{
			if ((ballsArray[i] == '>') && ((i + 1) < endArr) && (ballsArray[i + 1] == '<'))
			{
				ballsArray[i] = '<';
				ballsArray[i + 1] = '>';
				countCollision++;
				isСollision = true;
			}
			++i;
		}
	}

	fileOut << countCollision << endl;

	return 0;
}

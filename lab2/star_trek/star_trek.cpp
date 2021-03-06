// star_trek.cpp : Defines the entry point for the console application.
//2.4. Звездный путь (8)
//Экспедиция готовится отправиться в путь на космическом корабле нового поколения.Планируется последовательно посетить N планет звездной системы : от планеты Земля до планеты Победа.Планеты пронумерованы от 1 до N в порядке их посещения, Земля имеет номер 1, а Победа - номер N.
//Для перелёта между планетами корабль может использовать любой тип топлива, существующий в звездной системе.Перед началом экспедиции корабль находится на планете Земля, и бак корабля пуст.Существующие типы топлива пронумерованы целыми числами, на планете с номером i можно заправиться только топливом типа ai.При посещении i - й планеты можно заправиться, полностью освободив бак от имеющегося топлива и заполнив его топливом типа ai.
//На каждой планете станция заправки устроена таким образом, что в бак заправляется ровно столько топлива, сколько потребуется для перелета до следующей планеты с топливом такого же типа.Если далее такой тип топлива не встречается, заправляться на этой планете невозможно.Иначе говоря, после заправки на i - й планете топлива хватит для посещения планет от(i + 1) - й до j - й включительно, где j - минимальный номер планеты, такой что j > i и aj = ai.Для продолжения экспедиции дальше j - й планеты корабль необходимо снова заправить на одной из этих планет.
//Требуется написать программу, которая по заданным типам топлива на планетах определяет минимальное количество заправок, требуемых для экспедиции.
//Ввод.В первой строке входного файла INPUT.TXT записано число N(2 ≤ N ≤ 300000) - количество планет.Во второй строке N целых чисел a1, a2, . . ., aN(2 ≤ ai ≤ 300000) - типы топлива на планетах.
//Вывод.В первой строке выходного файла OUTPUT.TXT выведите единственное число K - минимальное количество заправок, которые нужно произвести.Во второй строке выведите K чисел, разделённых пробелами : номера планет, на которых требуется заправиться.Номера планет требуется выводить в порядке времени заправок.Если решений с минимальным количеством заправок несколько, выведите любое из них.Если решения не существует, выведите число 0.
//Примеры
//Ввод 1             Ввод 2
//7                  7
//1 3 2 1 3 2 3      4 3 2 4 3 2 1
//Вывод 1            Вывод 2
//3                  0
//1 3 5
// Выполнил студент ПС-21 Протасов Илья компилятор VS2017 

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <algorithm>

struct PlanetData
{
	int TypeOfFuel;
	int nextPlanet = 0;
};


int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		std::cout << "Invalid arguments count\n"
				  << "Usage: star_trek.exe <input file> <output file>\n";
		return 1;
	}

	std::ifstream fileIn(argv[1]);
	if (!fileIn.is_open())
	{
		std::cout << "Failed to open " << argv[1] << " for reading\n";
		return 1;
	}

	std::ofstream fileOut(argv[2]);
	if (!fileOut.is_open())
	{
		std::cout << "Failed to open " << argv[2] << " for writing\n";
		return 1;
	}

	int numberOfPlanets;
	fileIn >> numberOfPlanets;
	int FuelCount = 0;
	std::vector<PlanetData> planetsArray(numberOfPlanets);
	for (size_t i = 0; i < planetsArray.size(); ++i)
	{
		fileIn >> planetsArray[i].TypeOfFuel;
		if (planetsArray[i].TypeOfFuel > FuelCount)
		{
			FuelCount = planetsArray[i].TypeOfFuel;
		}
	}

	std::vector<int> arrOfFuelUsed(FuelCount + 1, 0);
	
	for (int i = planetsArray.size() - 1; i >= 0; --i)
	{
		if (arrOfFuelUsed[planetsArray[i].TypeOfFuel] != 0)
		{
			planetsArray[i].nextPlanet = arrOfFuelUsed[planetsArray[i].TypeOfFuel];
		}
		arrOfFuelUsed[planetsArray[i].TypeOfFuel] = i;
	}

	if ((planetsArray[0].nextPlanet == 0) || (arrOfFuelUsed[planetsArray[planetsArray.size() - 1].TypeOfFuel] == planetsArray.size() - 1))
	{
		std::cout << 0;
		return 0;
	}

	bool isPathFound = false;
	bool isEnd = false;
	int next;
	int currLvl = 0;
	while (!isEnd)
	{

	}
	
	for (size_t i = 0; i < arrOfFuelUsed.size(); ++i)
	{
		std::cout << arrOfFuelUsed[i] << " ";
	}
	std::cout << std::endl;
	for (size_t i = 0; i < planetsArray.size(); ++i)
	{
		std::cout << planetsArray[i].TypeOfFuel << ", " << planetsArray[i].nextPlanet << " ";
	}
	
	return 0;
}
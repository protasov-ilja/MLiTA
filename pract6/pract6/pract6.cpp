// pract6.cpp : Defines the entry point for the console application.
// 7.2. Ремонт дорог (4).
// После схода с рельсов нескольких поездов, следовавших из пункта A в пункт B, решено отремонтировать железную дорогу.Для выявления дефектных участков дороги привлекли N независимых экспертов(1 £ N £ 2×105).Каждый эксперт назвал один участок дороги для ремонта в виде отрезка ненулевой длины.Оказалось, что названные отрезки могут пересекаться и лежать один внутри другого.Ввиду нехватки средств, постановили отремонтировать только те части дороги, которые находятся не менее чем в M отрезках ненулевой длины(1 £ M £ 10, M £ N).
// Одна ремонтная бригада принимает заказ на ремонт в виде единственного участка дороги, заданного отрезком.Найти минимальное количество бригад для ремонта.Напоминаем, что концы отрезка считаются принадлежащими ему.
// Ввод из файла INPUT.TXT.Первая строка содержит количество экспертов N и значение M через пробел.В следующих N строках задаются сами отрезки в виде двух целых чисел X и Y через пробел(0 £ X £ Y £ 109).
// Вывод в файл OUTPUT.TXT в виде единственного целого числа.
// Ввод
// 4 2
// 2 5
// 8 10
// 4 6
// 3 9
// Вывод
// 2

#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct roadData
{
	long long roadCoord;
	bool opend = true;
};

int main()
{
	ifstream fileIn("input10.txt");
	if (!fileIn.is_open())
	{
		return 1;
	}
	ofstream fileOut("outputMy.txt");
	if (!fileOut.is_open())
	{
		return 1;
	}
	long long numberOfRoads;
	long long numberOfExperts;
	fileIn >> numberOfRoads >> numberOfExperts;

	vector<roadData> arrayOfRoads(numberOfRoads * 2);
	for (size_t i = 0; i < arrayOfRoads.size(); i += 2)
	{
		fileIn >> arrayOfRoads[i].roadCoord >> arrayOfRoads[i + 1].roadCoord;
		arrayOfRoads[i + 1].opend = false;
	}

	sort(arrayOfRoads.begin(), arrayOfRoads.end(), [](roadData a, roadData b)
	{
		return a.roadCoord < b.roadCoord || a.roadCoord == b.roadCoord && !a.opend;
	});

	long long k = 0;
	long long supposedBrigades = 0;
	long long origin;
	long long ending = -1;
	bool fistRoad = false;
	for (size_t i = 0; i < arrayOfRoads.size(); ++i)
	{
		if (arrayOfRoads[i].opend)
		{
			++k;
		}
		else
		{
			--k;
		}

		if (k == numberOfExperts)
		{
			long long bufOrigin = arrayOfRoads[i].roadCoord;
			if (bufOrigin != ending)
			{
				fistRoad = true;
				
				origin = arrayOfRoads[i].roadCoord;
				cout << " origin " << origin << endl;
			}
		}
		else if ((k == numberOfExperts - 1) && (fistRoad))
		{
			if (i + 1 < arrayOfRoads.size())
			{
				if (!((arrayOfRoads[i].roadCoord == arrayOfRoads[i + 1].roadCoord) && (arrayOfRoads[i + 1].opend)))
				{
					long long bufending = arrayOfRoads[i].roadCoord;
					if ((bufending - origin) > 0)
					{
						ending = arrayOfRoads[i].roadCoord;
						cout << ending << endl;
						++supposedBrigades;
					}
				}
			} 
			else if (i + 1 == arrayOfRoads.size())
			{
				++supposedBrigades;
			}
			
		}
	}

	//for (size_t i = 0; i < numberOfRoads * 2; ++i)
	//{
	//	cout << arrayOfRoads[i].roadCoord << " " << arrayOfRoads[i].opend << ", ";
	//}

	//cout << endl;
	cout << supposedBrigades << endl;;

    return 0;
}


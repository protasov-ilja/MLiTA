// lab12.8plan.cpp : Defines the entry point for the console application.
//
//	12.8. Учебный план (5)
//	Учебный план включает перечень дисциплин.Задан список пар дисциплин.Отдельная пара
//	показывает, что вторая дисциплина должна изучаться после первой.Составить список дисциплин
//	учебного плана в порядке их изучения.В том случае, когда задание некорректно, т.е.в списке пар
//	имеются циклы, выдать хотя бы один из них.
//	Ввод из файла INPUT.TXT.В первой строке задается число пар дисциплин N(1 ≤ N ≤ 300).В
//	каждой из следующих N строк указываются через пробел два натуральных числа X i, Y i(X i, Y i ≤
//	1000), определяющих номера дисциплин.Первая дисциплина должна изучаться раньше второй.
//	Вывод в файл OUTPUT.TXT.В первой строке вывести Yes либо No – возможность
//	расположения в списке дисциплин в порядке их изучения.При наличии такой возможности во
//	второй строке выводится через пробел искомый список.Если задание некорректно, т.е.имеется
//	цикл, то во второй строке выдается список номеров, образующих цикл.Первый и последний
//	номера в этом списке должны совпадать.
//	Примеры
//	Ввод 1 Ввод 2
//	7		8
//	1 2		1 2
//	1 3		1 3
//	2 5		2 5
//	3 4		3 4
//	4 2		4 2
//	3 2		3 2
//	6 4		6 4
//			5 3
//	Вывод 1 Вывод 2
//	Yes			No
//	1 6 3 4 2 5 2 5 3 4 2
// Выполнил студент группы ПС-21 Протасов Илья; Компилятор VS2017
//
//

#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <stack>
#include <vector>

struct Vertex
{
	bool inСhain = false;
	bool visited = false;
	std::stack<int> sons;
};

struct Results
{
	bool noLoops = true;
	std::vector<int> resultArr;
};

const size_t MAX_VERTEX = 300;

Results TopologicalSort(std::vector<Vertex>& graph, int graphSize);
void DFSGraph(std::vector<Vertex>& graph, std::stack<int>& mainStack, Results& result);
std::vector<int> StackUntwisting(std::stack<int>& mainStack);
void PrintResults(std::ofstream& fileOut, const Results& result);

int main()
{
	std::ifstream fileIn("input.txt");
	if (!fileIn.is_open())
	{
		std::cout << "filed to open input file" << std::endl;
		return 1;
	}

	std::ofstream fileOut("output.txt");
	if (!fileIn.is_open())
	{
		std::cout << "filed to open output file" << std::endl;
		return 1;
	}

	int N;
	fileIn >> N;
	std::vector<Vertex> graph(MAX_VERTEX);
	int graphSize = 0;
	for (int i = 0; i < N; ++i)
	{
		int x;
		int y;
		fileIn >> x >> y;
		graph[x - 1].sons.push(y - 1);
		graphSize = (graphSize < x) ? x : graphSize;
		graphSize = (graphSize < y) ? y : graphSize;
	}

	PrintResults(fileOut, TopologicalSort(graph, graphSize));

	return 0;
}

void PrintResults(std::ofstream& fileOut, const Results& result)
{
	fileOut << (result.noLoops ? "Yes" : "No") << "\n";
	for (int i = result.resultArr.size() - 1; i >= 0; --i)
	{
		fileOut << result.resultArr[i] << " ";
	}
}

Results TopologicalSort(std::vector<Vertex>& graph, int graphSize)
{
	std::stack<int> mainStack;
	Results result;
	for (int i = 0; i < graphSize; ++i)
	{
		if (!graph[i].visited)
		{
			if (!graph[i].sons.empty())
			{
				mainStack.push(i);
				DFSGraph(graph, mainStack, result);
				if (!result.noLoops)
				{
					result.resultArr = StackUntwisting(mainStack);
					break;
				}
			}
			else
			{
				result.resultArr.push_back(i + 1);
				mainStack.pop();
				graph[i].visited = true;
			}
		}
	}

	return result;
}

void DFSGraph(std::vector<Vertex>& graph, std::stack<int>& mainStack, Results& result)
{
	while (!mainStack.empty())
	{
		int currPos = mainStack.top();
		Vertex currV = graph[currPos];
		if (!currV.visited)
		{
			graph[currPos].inСhain = true;
			if (currV.sons.empty())
			{
				result.resultArr.push_back(currPos + 1);
				graph[currPos].visited = true;
				graph[currPos].inСhain = false;
				mainStack.pop();
			}
			else if (!graph[currV.sons.top()].inСhain)
			{
				mainStack.push(currV.sons.top());
				graph[currPos].sons.pop();
			}
			else
			{
				mainStack.push(currV.sons.top());
				result.noLoops = false;
				break;
			}
		}
		else
		{
			mainStack.pop();
		}
	}
}

std::vector<int> StackUntwisting(std::stack<int>& mainStack)
{
	int loopVertex = mainStack.top();
	std::vector<int> result;
	result.push_back(loopVertex + 1);
	mainStack.pop();
	while (mainStack.top() != loopVertex)
	{
		result.push_back(mainStack.top() + 1);
		mainStack.pop();
	}

	result.push_back(loopVertex + 1);

	return result;
}

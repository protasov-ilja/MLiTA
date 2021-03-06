// lab15.4GameTree.cpp : Defines the entry point for the console application.
//
//15.4. Дерево игры (5)
//	Игра для двух игроков определяется ее деревом.Соперники делают ходы по очереди.Первый
//	игрок начинает игру.Игра кончается или вничью, или победой одного из игроков.Листья дерева
//	этой игры могут иметь значения, равные одному из трех чисел : +1 - победа первого игрока, -1 -
//	победа второго игрока, 0 - ничья.Ваша задача - определить, кто выиграет, если оба противника
//	следуют правильной стратегии.
//	Ввод из файла INPUT.TXT.Узлы дерева пронумерованы последовательными целыми числами.
//	Корень дерева всегда имеет номер 1. Первая строка входного файла содержит целое N - число
//	узлов в дереве игры.Следующая N - 1 строка описывает узлы - одна строка для каждого узла(за
//	исключением первого).Вторая строка содержит описание второго узла дерева, третья - третьего
//	узла и т.д.Если узел является листом, первый символ строки - L, затем идёт пробел, затем номер
//	родительского узла, ещё пробел и результат игры(+1 - победа первого игрока, -1 - победа
//	второго, 0 - ничья).Если узел внутренний, то строка содержит N - первый символ, затем пробел и
//	номер родительского узла.
//	Вывод в файл OUTPUT.TXT.Выводится + 1, если выигрывает первый игрок, -1, если второй,
//	и 0 - в случае ничейного исхода.
//	Ограничения: 2<= N <= 1000, время 1 с.
//	Примеры
//	Ввод 1		Ввод 2
//	7			7
//	N 1			N 1
//	N 1			N 1
//	L 2 - 1		L 2 - 1
//	L 2 + 1		L 2 + 1
//	L 3 + 1		L 3 + 1
//	L 3 + 1		L 3 0
//	Вывод 1		Вывод 2
//	+ 1			0
// Выполнил студент группы ПС-21 Протасов Илья; компилятор VS2017

#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <map>

const int UNKNOWN = -100;
const int POSIT = 1;
const int ZERO = 0;
const int NEGAT = -1;

struct Node
{
	int val = UNKNOWN;
	int futh = -1;
	bool isMax = true;
};

int main()
{
	std::ifstream fileIn("input5.txt");
	if (!fileIn.is_open())
	{
		std::cout << "filed to open for reading" << std::endl;
		return 1;
	}

	std::ofstream fileOut("output.txt");
	if (!fileOut.is_open())
	{
		std::cout << "filed to open for writing" << std::endl;
		return 1;
	}

	int N;
	fileIn >> N;
	std::map<int, Node> gameTree;
	Node firstElem;
	gameTree.insert(std::pair<int, Node>(1, firstElem));
	for (int i = 1; i < N; ++i)
	{
		char state;
		int currFuth;
		int currVal = UNKNOWN;
		fileIn >> state >> currFuth;
		if (state == 'L')
		{
			Node prev = gameTree[currFuth];
			fileIn >> currVal;
			if (prev.val == UNKNOWN)
			{
				gameTree[currFuth].val = currVal;
			}
			else
			{
				if (prev.isMax)
				{
					if (prev.val < currVal)
					{
						gameTree[currFuth].val = currVal;
					}
				}
				else
				{
					if (prev.val > currVal)
					{
						gameTree[currFuth].val = currVal;
					}
				}
			}
		}
		else
		{
			gameTree.insert(std::pair<int, Node>(i + 1, { currVal, currFuth, !gameTree[currFuth].isMax }));
		}
	}

	for (auto it = gameTree.rbegin(); it != gameTree.rend(); ++it)
	{
		Node curr = it->second;
		Node prev = gameTree[curr.futh];
		if (prev.val == UNKNOWN)
		{
			gameTree[curr.futh].val = curr.val;
		}
		else
		{
			if (prev.isMax)
			{
				if (prev.val < curr.val)
				{
					gameTree[curr.futh].val = curr.val;
				}
			}
			else
			{
				if (prev.val > curr.val)
				{
					gameTree[curr.futh].val = curr.val;
				}
			}
		}
	}

	fileOut << ((gameTree[1].val == 1) ? "+" : "") << gameTree[1].val << std::endl;

	return 0;
}

// pract15.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

void CreateTree(vector<int> initVec, vector<int> tree, int i, int left, int right);
int Rmq(vector<int> tree, int left, int right, int i, int Tl, int Tr);

int main()
{
	ifstream fileIn("input.txt");
	if (!fileIn.is_open())
	{
		return 1;
	}

	ofstream fileOut("output.txt");
	if (!fileOut.is_open())
	{
		return 1;
	}

	int N;
	cin >> N;
	vector<int> initVector(N);
	for (size_t i = 0; i < initVector.size(); ++i)
	{
		cin >> initVector[i];
	}

	vector<int> segmentTree(4 * N);
	CreateTree(initVector, segmentTree, 0 , 0, N - 1);
	cout << Rmq(segmentTree, 2, 5, 0, 0, 4 * N - 1) << endl;
	return 0;
}

void CreateTree(vector<int> initVec, vector<int> tree, int i, int left, int right)
{
	if (left == right)
	{
		tree[i] = initVec[left];
	}
	else
	{
		int m = (left + right) / 2;
		CreateTree(initVec, tree, 2 * i, left, m);
		CreateTree(initVec, tree, 2 * i + 1, m + 1, right);
		tree[i] = (tree[2 * i] > tree[2 * i + 1]) ? tree[2 * i] : tree[2 * i + 1];
	}
}

int Rmq(vector<int> tree, int left, int right, int i, int Tl, int Tr)
//L, R - интервал индексов в A для суммы - первоначально 1 и N,
//Tl, Tr - границы поиска в массиве A, -первоначально 1 и N
{
	if ((left == Tl) && (right == Tr))
	{
		return tree[i];
	}
	else
	{
		int m = (Tl + Tr) / 2;
		if (right <= m)
		{
			return Rmq(tree, left, right, 2 * i, Tl, m);
		}
		else
		{
			if (left > m)
			{
				return Rmq(tree, left, right, 2 * i + 1, m + 1, Tr);
			}
			else
			{
				return max(Rmq(tree, left, m, 2 * i, Tl, m), Rmq(tree, m + 1, right, 2 * i + 1, m + 1, Tr));
			}
		}
	}
}

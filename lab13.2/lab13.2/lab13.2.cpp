// lab13.2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include "windows.h"
#include <algorithm>
using namespace std;

void CharToLower(char& ch);
bool FuncSubStr(const vector<int>& f, const string& p, const string& nameStr, ofstream& fileOut);
vector<int> FunctionPrefix(const string& p);

//vector<int> prefix_function(string s) {
//	int n = (int)s.length();
//	cout << "lenStr: " << n << endl;
//	vector<int> pi(n);
//	for (int i = 0; i < n; ++i)
//	{
//		for (int k = 0; k <= i; ++k)
//		{
//			cout << " i:- " << i << " k:- " << k << endl;
//			cout << " s.substr(0, k): " << s.substr(0, k) << " ? s.substr(i - k + 1, k): " << s.substr(i - k + 1, k) << endl;
//			if (s.substr(0, k) == s.substr(i - k + 1, k))
//			{
//				cout << "+++" << endl;
//				pi[i] = k;
//			}
//		}
//	}
//	
//	return pi;
//}


//vector<int> FunctionPrefixMLITA(string p)
//{
//	int n = p.length();
//	int k = 0;
//	vector<int> f(n);
//	f[0] = 0;
//	for (int i = 1; i < n; ++i)
//	{
//		cout << "i: " << i << endl;
//		cout << "befor k: " << k << "\n p[i]: " << p[i] << "          p[k]: " << p[k] << endl;
//		while ((k > 0) && (p[i] != p[k]))
//		{
//			cout << "p[i] != p[k]" << endl;
//			cout << "k: " << k << "    f[k]: " << f[k] << endl;
//			k = f[k];
//		}
//
//		if (p[i] == p[k])
//		{
//			cout << "p[i] == p[k]" << endl;
//			++k;
//			cout << "++k: " << k << endl;
//		}
//
//		f[i] = k;
//		cout << "add f[i]: " << f[i] << endl;
//	}
//
//	return f;
//}



int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	ifstream fileIn("input.txt");
	if (!fileIn.is_open())
	{
		cout << "filed to open for reading!" << endl;
		return 1;
	}

	string str;
	getline(fileIn, str);
	string nameStr;
	getline(fileIn, nameStr);
	for (size_t i = 0; i < str.size(); i++)
	{
		CharToLower(str[i]);
	}

	ofstream fileOut("output.txt");
	if (!fileOut.is_open())
	{
		cout << "filed to open for writing!";
		return 1;
	}

	vector<int> newArr = FunctionPrefix(str);
	if (!FuncSubStr(newArr, str, nameStr, fileOut))
	{
		fileOut << "No" << endl;
	}

    return 0;
}

bool FuncSubStr(const vector<int>& f, const string& p, const string& nameStr, ofstream& fileOut)
{
	bool wasFound = false;
	ifstream fileIn(nameStr);
	if (!fileIn.is_open())
	{
		cout << "filed to open for reading!" << endl;
		return false;
	}

	int startLine = 1;
	int startPos = 1;
	int currLine = 1;
	int currPos = 1;
	int pp = 0; // текущая позиция в образце
	int tp = 0; // текущая позиция в тексте
	char c;
	while (fileIn.get(c)) // очередной символ текста
	{
		//cout << pp << endl;
		if (c == '\n') // если конец строки
		{
			currPos = 1;
			c = ' ';
			currLine++;
		}

		CharToLower(c);
		//cout << c << ", " << " p[pp]: " << p[pp] << endl;
		while ((pp > 0) && (p[pp] != c))
		{
			pp = f[pp]; // следующее начало конец
		}

		if (p[pp] == c)
		{
			if (pp == 0)
			{
				startLine = currLine;
				startPos = currPos;
			}

			//cout << "++pp" << endl;
			++pp;
		}

		if (pp == f.size()) // совпал последний символ образца
		{
			if (!wasFound)
			{
				wasFound = true;
			}

			fileOut << startLine << " " << startPos << endl; // позиция первого символа
			pp = f[pp - 1];
			//cout << "after pp: " << pp << endl;
		}

		++tp;
		++currPos;
	}

	return wasFound;
}

void CharToLower(char& ch)
{
	if (ch >= 'A' && ch <= 'Z')
	{
		ch += 'a' - 'A';
	}
	else if (ch >= 'А' && ch <= 'Я')
	{
		ch += 'а' - 'А';
	}
	else if (ch == 'Ё')
	{
		ch = 'ё';
	}
}

vector<int> FunctionPrefix(const string& p)
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int n = p.length();
	int k = 0;
	vector<int> f(n);
	f[0] = 0;
	for (size_t i = 1; i < n; ++i)
	{
		while ((k > 0) && (p[i] != p[k]))
		{
			k = f[k];
		}

		if (p[i] == p[k])
		{
			++k;
		}

		f[i] = k;
	}

	return f;
}
// lab13.2.cpp : Defines the entry point for the console application.
//13.2. Алгоритм Кнута – Морриса – Пратта (6)
//Требуется найти все вхождения образца в текстовом файле методом КМП.В файле нет
//переноса слов.Образец может включать пробелы и переходить с одной строки файла на другую.
//Конец строки файла может интерпретироваться как пробел.Результаты поиска не должны
//зависеть от регистра букв, то есть каждая буква в образце и файле может быть как строчной, так и
//прописной.
//Ввод из файла INPUT.TXT.Первая строка файла является образцом и имеет длину от 1 до 255.
//Вторая строка задает имя текстового файла.
//Вывод в файл OUTPUT.TXT.Вывести в каждой строке через пробел последовательность
//номеров строк и позиций в строке, начиная с которых образец входит в текст.Нумерация строк и
//позиций в строке начинается с 1. Если вхождений нет, вывести No.
//Пример
//
//Ввод
//Мама мыла раму
//Bukvar.txt
//Вывод
//1 1
//1 23
//Пояснение.Файл Bukvar.txt состоит из следующих двух строк :
//Мама мыла раму вчера, мама
//мыла раму сегодня.
// Выполнил студент ПС-21 Протасов Илья Компилятор; VS2017

#include "stdafx.h"
#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include "windows.h"

using namespace std;

void CharToLower(char& ch);
bool FindCompInFile(const vector<int>& prefix, const string& subStr, const string& nameStr, ofstream& fileOut);
vector<int> GetPrefixFunction(const string& str);
vector<int> CopySubVector(const vector<int>& vec, int i);

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

	vector<int> prefix = GetPrefixFunction(str);
	if (!FindCompInFile(prefix, str, nameStr, fileOut))
	{
		fileOut << "No" << endl;
		cout << "No" << endl;
	}

    return 0;
}

bool FindCompInFile(const vector<int>& prefix, const string& subStr, const string& nameStr, ofstream& fileOut)
{
	bool wasFound = false;
	ifstream fileIn(nameStr);
	if (!fileIn.is_open())
	{
		cout << "filed to open for reading!" << endl;
		return false;
	}

	int subStrLen = subStr.length();
	int startLine = 1;
	int startPos = 1;
	int currLine = 1;
	int currPos = 1;
	int pp = 0;
	char c;
	bool check = false;
	bool addInStr = false;
	vector<int> strsLen;
	bool wasBack = false;
	while (fileIn.get(c)) 
	{
		if (c == '\n')
		{
			check = true;
			c = ' ';
		}

		CharToLower(c);
		while ((pp > 0) && (subStr[pp] != c))
		{
			pp = prefix[pp - 1];
			if (addInStr)
			{
				addInStr = false;
			}

			wasBack = true;
		}

		if ((pp != 0) && (wasBack))
		{
			int i = strsLen.size() - 1;
			int pMin;
			if (pp == 1)
			{
				pMin = pp;
			}
			else
			{
				pMin = pp - 1;
			}

			if ((currPos - pMin) > 0)
			{
				startPos = currPos - pMin;
				startLine = currLine;
			}
			else
			{
				int befP = pMin - currPos;
				while ((strsLen[i] - befP) <= 0)
				{
					befP -= strsLen[i];
					--i;
				}

				startLine += i;
				startPos = strsLen[i] - befP;
			}

			if (!strsLen.empty())
			{
				if (i == strsLen.size() - 1)
				{
					strsLen.clear();
				}
				else
				{
					strsLen = CopySubVector(strsLen, i);
				}
			}
		}

		if (wasBack)
		{
			wasBack = false;
		}
		
		if (subStr[pp] == c)
		{
			if (!addInStr)
			{
				addInStr = true;
			}
			
			if (pp == 0)
			{
				strsLen.clear();
				addInStr = true;
				startLine = currLine;
				startPos = currPos;
			}

			++pp;
		}

		if (pp == prefix.size())
		{
			if (!wasFound)
			{
				wasFound = true;
			}
			
			fileOut << startLine << " " << startPos << "\n";
			pp = prefix[pp - 1];
			int i = strsLen.size() - 1;
			if (pp != 0)
			{
				int pMin = pp - 1;
				if ((currPos - pMin) > 0)
				{
					startPos = currPos - pMin;
					startLine = currLine;
				}
				else
				{
					int befP = pMin - currPos;
					while ((strsLen[i] - befP) <= 0)
					{
						befP -= strsLen[i];
						--i;
					}

					startLine += i;
					startPos = strsLen[i] - befP;
				}
			}

			if (!strsLen.empty())
			{	
				if (i == strsLen.size() - 1)
				{
					strsLen.clear();
				}
				else
				{
					strsLen = CopySubVector(strsLen, i);
				}
			}
		}

		++currPos;
		if (check)
		{
			if (addInStr)
			{
				strsLen.push_back(currPos - 1);
			}

			check = false;
			currPos = 1;
			currLine++;
		}
	}

	return wasFound;
}

vector<int> CopySubVector(const vector<int>& vec, int i)
{
	vector<int> nVec;
	copy(vec.begin() + i, vec.end(), std::back_inserter(nVec));
	return nVec;
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

vector<int> GetPrefixFunction(const string& str)
{
	int len = str.length();
	int k = 0;
	vector<int> prefix(len);
	prefix[0] = 0;
	for (size_t i = 1; i < len; ++i)
	{
		while ((k > 0) && (str[i] != str[k]))
		{
			k = prefix[k - 1];
		}

		if (str[i] == str[k])
		{
			++k;
		}

		prefix[i] = k;
	}

	return prefix;
}
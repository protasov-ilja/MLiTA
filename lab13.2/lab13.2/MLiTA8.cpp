// 13_3_Islamov.cpp: определяет точку входа для консольного приложения.
//Исламов Яхья ПС-21
/*13.3. Алгоритм Бойера – Мура (6)
Требуется найти все вхождения образца в текстовом файле методом Бойера – Мура. В файле нет
переноса слов. Образец может включать пробелы и переходить с одной строки файла на другую.
Конец строки файла может интерпретироваться как пробел. Результаты поиска не должны
зависеть от регистра букв, то есть каждая буква в образце и файле может быть как строчной, так и
прописной.*/

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <locale>
using namespace std;

struct letterInLine
{
	char letter;
	int indexOfLine;
	int indexOfLetterInLine;
};

void InserTextToQueue(ifstream& file, vector<letterInLine> &queue);
int searchWordinLine(vector<letterInLine> queue, int index, string obrazec, vector<int> dict);
void InicializateOffsetTable(vector<int>& dict, string line);
void TuneOffsetTable(vector<int>& dict, string obrazec);
void ChangeRegister(string& line);
int main()
{
	setlocale(LC_ALL, "Russian");
	int result;
	string searchLine;
	vector<int> dict(257, 0);
	vector<letterInLine> queue;
	string obrazec;
	string line;
	string nameOfBukvar;
	ifstream inFile("input.txt");
	getline(inFile, obrazec);
	int index = obrazec.length() -1;
	inFile >> nameOfBukvar;
	ifstream bukvar(nameOfBukvar);
	ofstream outFile("output.txt");
	ChangeRegister(obrazec);
	int numberLine = 0;

	InicializateOffsetTable(dict, obrazec);
	TuneOffsetTable(dict, obrazec);

	try {
		InserTextToQueue(bukvar, queue);
	}
	catch (exception e)
	{
		cout << e.what() << endl;
		system("pause");
		return 1;
	}


	while (true)
	{
     	result = searchWordinLine(queue, index, obrazec, dict);

		if (result > 400)
		{
			outFile << queue[index - obrazec.length() + 1].indexOfLine << ' ' << queue[index - obrazec.length() + 1].indexOfLetterInLine + 1 << endl;
			index += 1;
		}
		else
			index += result;
	}

    return 0;
}

void TuneOffsetTable(vector<int>& dict, string obrazec)
{
	int index = 1;
	for (size_t i = obrazec.length() - 2; i >= 0; i--)
	{
		if (dict[(int)obrazec[i]] == obrazec.length())
			dict[(int)obrazec[i]] = index;
		if (i == 0)
			break;
		index++;
	}
}

void InicializateOffsetTable(vector<int>& dict, string line)
{

	for (size_t i = 0; i < dict.size(); i++)
		dict[i] = line.length();
}

void ChangeRegister(string& line)
{
	for (size_t i = 0; i < line.length(); i++)
		if ((line[i] >= 'A' && line[i] <= 'Z') || (line[i] >= 'А' && line[i] <= 'Я'))
			line[i] = (char)(int)(line[i] + 32);
}

int searchWordinLine(vector<letterInLine> queue, int index, string obrazec, vector<int> dict)
{
	if (index > queue.size() - 1)
		exit (0);
	int K = 0;

	for (size_t i = obrazec.length() - 1; i >= 0; i--)
	{

		if (queue[index].letter != obrazec[i])
		{
			if ((dict[(int)queue[index].letter] - K) <= 0)
				return 1;
			return (dict[(int)queue[index].letter] - K);
		}
		else
			K++;

		index--;
		if (i == 0)
			break;
	}
	return (index - (obrazec.length()-1) + 500);
}

void InserTextToQueue(ifstream& file, vector<letterInLine> &queue)
{
	string searchLine;
	getline(file, searchLine);
	ChangeRegister(searchLine);
	letterInLine value;
	for (size_t i = 0; i < searchLine.length(); i++)
	{
		value.letter = searchLine[i];
		value.indexOfLine = 1;
		value.indexOfLetterInLine = i;
		queue.push_back(value);	
	}

	int indexOfLastLetter = searchLine.length();
	int indexOfLine = 1;
	while (!file.eof())
	{
		value.indexOfLine = indexOfLine;
		value.indexOfLetterInLine = indexOfLastLetter;
		value.letter = ' ';
		queue.push_back(value);

		getline(file, searchLine);
		ChangeRegister(searchLine);
		indexOfLine++;

		for (size_t i = 0; i < searchLine.length(); i++)
		{
			value.letter = searchLine[i];
			value.indexOfLine = indexOfLine;
			value.indexOfLetterInLine = i;
			queue.push_back(value);
		}
	}
}
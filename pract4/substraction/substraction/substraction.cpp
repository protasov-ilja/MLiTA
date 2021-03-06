// substraction.cpp : Defines the entry point for the console application.
// Выполнил Протасов Илья ПС-21 Компилятор VS2017

#include "stdafx.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

int main(int argc, char* argv[])
{
	std::string str1;
	std::string str2;
	std::string str3;
	std::ifstream fileIn("input.txt");
	std::ofstream fileOut("output.txt");
	fileIn >> str1;
	fileIn >> str2;
	size_t length1 = str1.length();
	size_t length2 = str2.length();

	std::vector<int> arrInt1;
	for (size_t i = 0; i < length1; ++i)
	{
		arrInt1.insert(arrInt1.begin(), std::stoi(std::string(1, str1[i])));
	}

	std::vector<int> arrInt2;
	for (size_t i = 0; i < length2; ++i)
	{
		arrInt2.insert(arrInt2.begin(), std::stoi(std::string(1, str2[i])));
	}

	std::vector<int> arrInt3;

	for (size_t i = 0; i < length1; ++i)
	{
		arrInt3.insert(arrInt3.begin(), 0);
	}

	for (size_t i = 0; i < length1; ++i)
	{
		if (i < length2)
		{
			if (arrInt1[i] < arrInt2[i])
			{
				bool isFind = false;
				size_t one = 1;
				while (!isFind && (one + i < length1))
				{
					if (arrInt1[i + one] == 0)
					{
						arrInt1[i + one] = 10 - 1;
						one++;
					}
					else
					{
						isFind = true;
					}
				}
				if (one + i >= length1)
				{
					arrInt1[i + one - 1] = 0;
				}
				else
				{
					arrInt1[i + one]--;
				}

				arrInt3[i] = (10 + arrInt1[i]) - arrInt2[i];
			}
			else
			{
				arrInt3[i] = arrInt1[i] - arrInt2[i];
			}
		}
		else
		{
			arrInt3[i] = arrInt1[i];
		}
	}

	int j = arrInt3.size() - 1;
	while ((j >= 0) && (arrInt3[j] == 0))
	{
		--j;
	}

	if (j < 0)
	{
		fileOut << 0 << std::endl;
	}
	else
	{
		for (int i = j; i >= 0; --i)
		{
			fileOut << arrInt3[i];
		}
		fileOut << std::endl;
	}

	return 0;
}

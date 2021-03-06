// pract11.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>

using namespace std;

bool FindResult(map<char, int> mapStr, const string& str);

int main()
{
	ifstream fileIn("input7.txt");
	if (!fileIn.is_open())
	{
		return 1;
	}

	ofstream fileOut("output.txt");
	if (!fileOut.is_open())
	{
		return 1;
	}

	string str;
	getline(fileIn, str);
	map<char, int> mapStr;
	for (size_t i = 0; i < str.length(); ++i)
	{
		auto it = mapStr.find(str[i]);
		if (it != mapStr.end())
		{
			++it->second;
		}
		else
		{
			mapStr.insert(pair<char, int>(str[i], 1));
		}
	}

	vector<string> arrOfStrings;
	string obr;
	int result = 0;

	while (getline(fileIn, obr))
	{
		if (FindResult(mapStr, obr))
		{
			result += obr.length();
			arrOfStrings.push_back(obr);
		}
	}

	fileOut << result << endl;

	sort(arrOfStrings.begin(), arrOfStrings.end(), [](const string& a, const string& b) {
		return (a.length() > b.length() || ((a.length() == b.length()) && (a < b)));
	});

	for (auto elem : arrOfStrings)
	{
		fileOut << elem << endl;
	}

    return 0;

}

bool FindResult(map<char, int> mapStr, const string& str)
{
	for (size_t i = 0; i < str.length(); ++i)
	{
		auto it = mapStr.find(str[i]);
		if (it != mapStr.end())
		{
			if (it->second > 0)
			{
				--it->second;
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}

	return true;
}
// lab13.2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <vector>
#include <iostream>
#include <string>
using namespace std;

vector<int> prefix_function(string s) {
	int n = (int)s.length();
	cout << "lenStr: " << n << endl;
	vector<int> pi(n);
	for (int i = 0; i < n; ++i)
	{
		for (int k = 0; k <= i; ++k)
		{
			cout << " i:- " << i << " k:- " << k << endl;
			cout << " s.substr(0, k): " << s.substr(0, k) << " ? s.substr(i - k + 1, k): " << s.substr(i - k + 1, k) << endl;
			if (s.substr(0, k) == s.substr(i - k + 1, k))
			{
				cout << "+++" << endl;
				pi[i] = k;
			}
		}
	}
		
			
				
	return pi;
}


int main()
{
	vector<int> newArr = prefix_function("ababefab");
	for (size_t i = 0; i < newArr.size(); ++i)
	{
		cout << newArr[i] << ", ";
	}

    return 0;
}


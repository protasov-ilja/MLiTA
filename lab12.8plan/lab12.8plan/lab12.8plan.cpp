// lab12.8plan.cpp : Defines the entry point for the console application.
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
	std::ifstream fileIn("in1.txt");
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
	std::cout << "sucess";

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
		std::cout << " 1currPos " << currPos << std::endl;
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
				std::cout << " currV.sons.top() " << currV.sons.top() << std::endl;
				std::cout <<" 2currPos " << currPos << std::endl;
				std::cout << "1 graph[currPos].sons.top(); " << graph[currPos].sons.top() << std::endl;
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
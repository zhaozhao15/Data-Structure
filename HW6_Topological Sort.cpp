#include <iostream>
#include <stdio.h> 
#include <string>
using namespace std;

int graph[26][26];
int inDegree[26];
string input[200];
int n = 0;
int count = 0;

string low(string name)
{
	for (int i = 0; i < (int)name.length(); i++)
		if (name[i] >= 'A' && name[i] <= 'Z') name[i] += 32;
	return name;
}

void remove(int i)
{
	for (int j = 0; j < 26; j++)
	{
		if (graph[i][j] == 1) inDegree[j]--;
		graph[i][j] = 0;
	}
}

int main()
{
	for (int i = 0; i < 26; i++) inDegree[i] = 0;

	for (int i = 0; i < 26; i++)//初始化图
	{
		for (int j = 0; j < 26; j++) graph[i][j] = 0;
	}

	string name;
	while(getline(cin,name))
	{
		input[n] = name;
		n++;
	}
	//n-1 names
	//until index n-1

	for (int i = 1; i < n; ++i)
	{
		int pos = input[i].find(" ");
		while (pos != -1)
		{
			input[i] = input[i].replace(pos, 1, "");
			pos = input[i].find(" ");
		}
		input[i] = low(input[i]);
	}

	for (int i = 1; i <= n-2; i++)
	{
		string bf = input[i];
		string af = input[i+1];

		int j;
		for (j = 0; j < (int)bf.length(); j++)
		{
			if ((bf[j] == af[j]) == 0)	break;
		}

		if (graph[bf[j]-97][af[j]-97]==0)
		{
			inDegree[af[j]-97]++;
			graph[bf[j]-97][af[j]-97]=1;
		}
	}

	while(1)
	{
		for (int i = 0; i < 26; ++i)
		{
			if (inDegree[i]==0)
			{
				inDegree[i] = -1;
				printf("%c", i+97);
				count++;
				remove(i);
				break;
			}
		}
		if (count == 26) break;
	return 0;
}
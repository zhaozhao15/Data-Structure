#include <iostream>
#include <stdlib.h>
#include <stdio.h>
using namespace std;
#define MAX 0x7fffffff

int n;	//cities <20000
int m;	//old roads <60000
int k;	//regions <4000
int count;         //count current region numbers
int data[100000]; //save input
int uset[20000]; //union set

void makeset(int size)
{
	for (int i = 0; i < size; i++) uset[i] = -1;
}

int find(int x)
{
	if (uset[x] < 0) return x;
	uset[x] = find(uset[x]);
	return uset[x];
}

int unionset(int x, int y)
{
	x = find(x);
	y = find(y);
	if (x == y) return -1;
	if (uset[x] <= uset[y])
	{
		uset[x] += uset[y];
		uset[y] = x;
	}
	else
	{
		uset[y] += uset[x];
        uset[x] = y;
	}
	count--;
	return 0;
}

typedef struct road{
	int city1;
	int city2;
	int weight;
	road* next;
}road;

road* newRoad(int city1, int city2, int weight)
{
	road* ptr = new road;
	ptr->city1 = city1;
	ptr->city2 = city2;
	ptr->weight = weight;
	ptr->next = NULL;
	return ptr;
}

road* allRoads[60000];

typedef struct region{
	int roadNum;
	int minCity;
	road** roads;
}region;

region* newRegion(int roadNum, int minCity)
{
	region* ptr = new region;
	ptr->roadNum = roadNum;
	ptr->minCity = minCity;
	ptr->roads = new road*[roadNum];
	return ptr;
}

region* allRegions[4000];

typedef struct info{
	int roadNum;
	int minCity;
	road* head;
	road* end;
}info;

info* newInfo()
{
	info* ptr = new info;
	ptr->roadNum = 0;
	ptr->minCity = MAX;
	ptr->head = newRoad(MAX,MAX,MAX);
	ptr->end = NULL;
	return ptr;
}

info* allInfo[20000];

int qsortWeight(int left, int right, road* r[])
{
	if (left > right) return 0;
	road* tmp = r[left];
	int i = left;
	int j = right;
	while(i!=j)
	{
		while(r[j]->weight >= tmp->weight && i<j)	j--;
		while(r[i]->weight <= tmp->weight && i<j)	i++;
		if (i < j)
		{
			road* t = r[i];
			r[i] = r[j];
			r[j] = t;
		}
	}
	r[left] = r[i];
	r[i] = tmp;
	qsortWeight(left, i-1, r);
	qsortWeight(i+1, right, r);
	return 0;
}

int qsortWeight2(int left, int right, road* r[])
{
	while(1)
	{
		int flag = 0;
		for (int p = 0; p < right; p++)
		{
			if (r[p]->weight == r[p+1]->weight)
			{
				if (r[p]->city1 > r[p+1]->city1)
				{
					flag = 1;
					road* t = r[p];
					r[p] = r[p+1];
					r[p+1] = t;
				}
				else if ((r[p]->city1 == r[p+1]->city1) && (r[p]->city2 > r[p+1]->city2))
				{
					flag = 1;
					road* t = r[p];
					r[p] = r[p+1];
					r[p+1] = t;
				}
			}
		}
		if (flag == 0) break;
	}
	return 0;
}

int qsortRoadNum(int left, int right, region* r[])
{
	if (left > right)	return 0;
	region* tmp = r[left];
	int i = left;
	int j = right;
	while(i!=j)
	{
		while(r[j]->roadNum >= tmp->roadNum && i<j)	j--;
		while(r[i]->roadNum <= tmp->roadNum && i<j)	i++;
		if (i < j)
		{
			region* t = r[i];
			r[i] = r[j];
			r[j] = t;
		}
	}
	r[left] = r[i];
	r[i] = tmp;
	qsortRoadNum(left, i-1, r);
	qsortRoadNum(i+1, right, r);
	return 0;
}

int qsortRoadNum2(int left, int right, region* r[])
{
	while(1)
	{
		int flag = 0;
		for (int i = 0; i < right; i++)
		{
			if (r[i]->roadNum == r[i+1]->roadNum)
			{
				if (r[i]->minCity > r[i+1]->minCity)
				{
					flag = 1;
					region* t = r[i];
					r[i] = r[i+1];
					r[i+1] = t;
				}
			}
		}
		if (flag == 0) break;
	}
	return 0;
}


int main()
{
	int save;
	int zhaozhao = 0;
	int z = 0;
	while (scanf("%d%*c", data + z++) == 1);
	data[z-1] = -1;
	n = data[0];
	m = data[1];
	k = data[2];
	count = n;

	for (int i = 0; i < m; i++) allRoads[i] = NULL;
	for (int i = 0; i < n; i++) allInfo[i] = NULL;
	for (int i = 0; i < k; i++) allRegions[i] = NULL;

	for (int i = 1; i <= m; i++)
	{
		int a = 3*i;
		int b = a+1;
		int c = a+2;
		if (data[a] <= data[b]) allRoads[i-1] = newRoad(data[a], data[b], data[c]);
		else allRoads[i-1] = newRoad(data[b], data[a], data[c]);
	}

	qsortWeight(0, m-1, allRoads);
	qsortWeight2(0, m-1, allRoads);
	makeset(n);

	for (int i = 0; i < m; i++)
	{
		if (count <= k)
		{
			save = i-1;
			break;
		}
		int a = allRoads[i]->city1;
		int b = allRoads[i]->city2;
		if(unionset(a,b) == -1)
		{
			allRoads[i]->weight = MAX - zhaozhao;
			zhaozhao++;
		}
		save = i;
	}

	save -= zhaozhao;
	qsortWeight(0, m-1, allRoads);
	qsortWeight2(0, m-1, allRoads);

	int record[20000];
	for (int i = 0; i < 20000; ++i)
	{
		record[i]= -1;
	}
	int save1 = 0;

	if (count == n)
	{
		save=-1;
	}
	for (int i = 0; i <= save; i++)
	{
		int a = allRoads[i]->city1;
		int b = find(a);
		if (allInfo[b] == NULL)
		{
			record[save1] = b;
			save1++;

			allInfo[b] = newInfo();
			allInfo[b]->head->next = allRoads[i];
			allInfo[b]->end = allRoads[i];
			allInfo[b]->roadNum++;
			allInfo[b]->minCity = a;
		}
		else
		{
			if (a < allInfo[b]->minCity) allInfo[b]->minCity = a;
			allInfo[b]->end->next = allRoads[i];
			allInfo[b]->end = allRoads[i];
			allInfo[b]->roadNum++;
		}
	}

	for (int i = 0; i < count; i++)
	{
		int tmp = record[i];
		if (tmp!=-1)
		{
			int roadNum = allInfo[tmp]->roadNum;
			int minCity = allInfo[tmp]->minCity;
			allRegions[i] = newRegion(roadNum ,minCity);
			road* rd = allInfo[tmp]->head->next;
			for (int j = 0; j < roadNum; j++)
			{
				(allRegions[i]->roads)[j] = rd;
				rd = rd->next;
			}
		}
		else
		{
			allRegions[i] = newRegion(0 ,-1);
		}
	}

	qsortRoadNum(0, count-1, allRegions);
	qsortRoadNum2(0, count-1, allRegions);

	printf("[\n");
	for (int i = count-1; i >= 0; i--)
	{
		printf("[\n");
		for (int j = allRegions[i]->roadNum-1; j >=0 ; j--)
		{
			printf("[");
			road* tmp = (allRegions[i]->roads)[j];
			printf("%d,", tmp->city1);
			printf("%d,", tmp->city2);
			printf("%d", tmp->weight);
			printf("]");
			if (j != 0) printf(",");
			printf("\n");
		}
		printf("]");
		if (i != 0) printf(",");
		printf("\n");
	}
	printf("]\n");
	return 0;
}
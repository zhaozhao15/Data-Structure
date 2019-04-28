#include <iostream>
#include <stdio.h>
using namespace std;

string maze[100][100];
int mark[100][100];
int nextt[4][2] = {{-1,0},{1,0},{0,1},{0,-1}};
int endx,endy;
int m,n;//地图行数，列数
int flag = 0;
int head = 0;
int tail = 1;
int startx,starty;

struct point
{
	int x;
	int y;
	int pre;
	int step;
};

point* trace[10000];

point* newpoint(int x, int y, int pre, int step)
{
	point* tmp = new point;
	tmp->x = x;
	tmp->y = y;
	tmp->pre = pre;
	tmp->step = step;
	return tmp;
}

void display()
{
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout<<maze[i][j];
		}
		printf("\n");
	}
}

int bfs()
{
	trace[0] = newpoint(startx, starty, -1, 0);
	mark[startx][starty] = 1;
	while(head < tail)
	{
		for (int i = 0; i < 4; i++)
		{
			int nexttx = trace[head]->x + nextt[i][0];
			int nextty = trace[head]->y + nextt[i][1];
			if (nexttx<0 || nexttx>=m || nextty<0 || nextty>= n)
			{
				continue;
			}
			if (maze[nexttx][nextty]==" " && mark[nexttx][nextty]==0)
			{
				//maze[nexttx][nextty] = "x";
				mark[nexttx][nextty] = 1;
				trace[tail] = newpoint(nexttx, nextty, head, trace[head]->step+1);
				tail++;
				//display();
			}
			if (nexttx==endx && nextty==endy)
			{
				flag = 1;
				break;
			}
		}
		if (flag == 1)
		{
			break;
		}
		head++;
	}
	return 0;
}

int main()
{
	m = 0;
	string input[100];
	string in;
	while(getline(cin, in))
	{
		input[m] = in;
		m++;
	}
	//m行，序号m-1

	n = input[0].length();
	//n列，序号n-1

	//printf("%d rows\n",m );
	//printf("%d cols\n",n );
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			maze[i][j] = input[i][j];
			if (input[i][j] == '*')
			{
				startx = i;
				starty = j;
			}
			if (input[i][j] == '+')
			{
				maze[i][j] = " ";
				endx = i;
				endy = j;
			}
		}
	}

	//display();
	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			mark[i][j] = 0;
		}
	}

	bfs();

	point* end = trace[tail-1];
	//printf("end\n");
	//printf("%d %d\n",end->x,end->y );
	int father = end->pre;
	int totalstep = end->step;
	//maze[endx][endy] = ".";
	maze[end->x][end->y] = ".";

	if (end->x!=endx || end->y!=endy)
	{
		printf("NO SOLUTION");
		return 0;
	}

	while(father >= 0)
	{
		maze[trace[father]->x][trace[father]->y] = ".";
		father = trace[father]->pre;
	}

	display();
	printf("%d", totalstep);
	return 0;
}
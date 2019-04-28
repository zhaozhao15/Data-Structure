#include <iostream>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
using namespace std;

int oldlen;
int len;
int mysize;
int lf;
string data[2000000];

typedef struct node{
	string key;
	int val;     //frequency
	struct node *next;
}node;

node** table;

node* init_node(string key, int val)
{
	node* ptr = new node;
	ptr->key = key;
	ptr->val = val;
	ptr->next = NULL;
	return ptr;
}

bool all_num(string key)  
{
    for (int i = 0; i < (int)key.size(); i++)
    {
		int tmp = (int)key[i];
		if (tmp < 48 || tmp > 57)
        {
            return false;
        }
    }
    return true;
}

int myhash(string key)
{
	if (all_num(key))
	{
		int index = stoi(key) % len;
		return index;
	}
	else
	{
		const unsigned char* s = (unsigned char*)key.c_str();
		int modsum = 0;
		for (int i = 0; i < (int)key.size(); i++)
		{
			modsum = modsum*256%len + s[i]%len;
		}
		
		int index = modsum % len;
		return index;
	}
}

node* exist(string key, node** table)//return position if exist, else null
{
	int index = myhash(key);
	
	node* position = table[index];

	while(position != NULL)
	{
		if (position->key == key)
		{
			return position;
		}
		else
		{
			position = position->next;
		}
	}
	return position;
}

int insert(string key, int val, node** table, int index)//position is table[index]
{
	node* newnode = init_node(key, val);
	newnode->next = table[index];
	table[index] = newnode;
	return 0;
}

int operate(string key, int val, node** table)
{
	node* position = exist(key, table);
	int index = myhash(key);
	if (position == NULL)
	{
		insert(key, val, table, index);
		mysize++;
	}
	else
	{
		(position->val)++;
	}
	return 0;
}

int remove(string key, node** table)
{
	node* position = exist(key, table);
	if (position == NULL)
	{
		return 0;
	}

	if (position->next == NULL)
	{
		int index = myhash(key);
		node* aa = table[index];

		if (aa->next == NULL)
		{
			table[index] = NULL;
		}
		else
		{
			while(aa->next != NULL)
			{
				if (aa->next->key == key)
				{
					aa->next = NULL;
					break;
				}
				else
				{
					aa = aa->next;
				}
			}
		}
	}
	else
	{
		position->key = position->next->key;
		position->val = position->next->val;
		position->next = position->next->next;
	}
	return 0;
}

int freetable(node** table)
{
	for (int i = 0; i < oldlen; i++)
	{
		node* curr = table[i];
		while(curr != NULL)
		{
			node* next = curr->next;
			delete curr;
			curr = next;
		}
	}
	return 0;
}

int display(node** table)
{
	printf("[\n");
	for (int i = 0; i < len; i++)
	{
		if (table[i] == NULL)
		{
			printf("{}");
		}
		else
		{
			node* current = table[i];
			printf("{");
			while(current != NULL)
			{
				printf("\"");
				cout<<current->key;
				printf("\":");
				printf("%d", current->val);
				current = current->next;

				if (current != NULL)
				{
					printf(",");
				}
			}
			printf("}");
		}

		if (i != len-1)
		{
			printf(",");
		}
		printf("\n");
	}
	printf("]");
	return 0;
}

int main()
{
	printf("begin!\n");
	string a;
	int d = 0;
	while(getline(cin,a))
	{
		data[d] = a;
		d++;
	}
	lf = stoi(data[0]);
	len = stoi(data[1]);

	int save;

	mysize = 0;
	table = new node*[len];

	for (int i = 0; i < len; i++)
	{
		table[i] = NULL;
	}

	for (int i = 2; i < d; i++)
	{
		if (data[i] != "************************")
		{
			string tmp = data[i];
			operate(tmp, 1, table);
		}
		else
		{
			save = i;
			break;
		}

		if (mysize*100 > len*lf)
		{
			oldlen = len;

			while(mysize*100 > len*lf)
			{
				len = 2*len + 1;
			}
			mysize = 0;
			
			node** newtable = new node*[len];
			for (int j = 0; j < len; j++)
			{
				newtable[j] = NULL;
			}

			for (int j = 0; j < oldlen; j++)
			{
				node* current = table[j];
				while(current != NULL)
				{
					operate(current->key, current->val, newtable);
					current = current->next;
				}
			}

			freetable(table);
			delete table;
			table = newtable;
		}
	}

	for (int i = save+1; i < d; i++)
	{
		if (data[i] != "************************")
		{
			remove(data[i], table);
			mysize--;
		}
		else
		{
			break;
		}
	}

	display(table);
	return 0;
}

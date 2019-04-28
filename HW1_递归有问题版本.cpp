#include <iostream>
#include <cstdlib>
#include <sstream>
#include <string>
#include <cctype>
#include <stdio.h>
#include <stdlib.h>
using namespace std;
//修改了优先级判断的等号
const int piror[6]={2,1,0,1,0,2};   
//ASCII ### 42:*, 43:+, 44:', 45:-, 46:., 47:/, 48:0, 49:1

//////////////////////
//////////////////////
//////////////////////
template<class type>
class stack
{
    int toppp;
    type* ptr;
    int maxsize;

public:
    stack(int size):toppp(-1),maxsize(size)
    {
        ptr = new type[maxsize];
    }

    ~stack()
    {
        delete[] ptr;
    }

    bool empty();

    void push(type elem);

    type top();

    type pop();

    int size();

    void show();
};

template<class type>
bool stack<type>::empty()
{
    if(toppp==-1){
        return true;
    }
    else
        return false;
}

template<class type>
type stack<type>::top()
{
    return ptr[toppp];
}

template<class type>
void stack<type>::push(type elem)
{
    ptr[++toppp] = elem;
}

template<class type>
type stack<type>::pop()
{
    return ptr[toppp--];
}

template<class type>
int stack<type>::size()
{
    return toppp+1;
}

template<class type>
void stack<type>::show()
{
    for (int k = 0; k < 1000; ++k)
    {
    	cout<<ptr[k]<<endl;
    	if (ptr[k] == '\0')
    	{
    		break;
    	}
    }
}

double getnumber(char s[],int &i)//提取数字
{
    double result=0;
    int j;

    //整数部分
    while(s[i]!='.'&&s[i]!='+'&&s[i]!='-'&&s[i]!='*'&&s[i]!='/'&&s[i]!='('&&s[i]!=')'&&s[i]!='\0')
    {
        result=result*10+s[i]-'0';
        i++;
    }
    if(s[i]=='.')//小数部分
    {
        i++;
        for(j=10;s[i]!='+'&&s[i]!='-'&&s[i]!='*'&&s[i]!='/'&&s[i]!='('&&s[i]!=')'&&s[i]!='\0';j=j*10,i++)  
        {
            result+=(double(s[i]-'0'))/j;
        }
    }
    i--;//考虑到原来的函数存在i自增，所以这里要退一位   
    return result;
}


void calculate(stack<double> &num,stack<char> &op)//计算当前能计算的部分
{
    double a,b;
    while(!op.empty())//直到当前没有运算符剩余，即只剩下一个结果值   
    {
        b=num.top();
        num.pop();
        a=num.top();  
        num.pop();
        printf("number a is %f\n", a);
        printf("number b is %f\n", b);
        printf("fuhao is %c\n", op.top());
        char fuhao = op.pop();
        printf("fuhao is %c\n", op.top());
        switch(fuhao)
        {
        case '+':{if (op.top()=='-')
        	{
        		num.push(a-b);break;
        	}
        	else
        	{
        		num.push(a+b);break;
        	}
        }
        case '-':{
        	if (op.top()=='-')
        	{
        		num.push(a+b);break;
        	}
        	else
        	{
        		num.push(a-b);break;
        	}
        }
        case '*':{
        	if (op.top()=='/')
        	{
        		num.push(a/b);break;
        	}
        	else
        	{
        		num.push(a*b);break;
        	}
        }
        case '/':{
        	if (op.top()=='/')
        	{
        		num.push(a*b);break;
        	}
        	else
        	{
        		num.push(a/b);break;
        	}
        }
    }
}}

double exec(char s[], int &i, char flag)
{
	double result = 0;
	stack<double> num(1000) ;
	stack<char> op(500);

	for (;s[i] != flag; i++)
	{
		if (s[i]>='0'&&s[i]<='9')
		{	
			int a = getnumber(s,i);
			num.push(a);
			printf("getnumber%d\n", a);
		}
		else
		{
			if (s[i]=='(')
			{	printf("once\n");
				i++;
				double tmp = exec(s,i,')');
                num.push(tmp);
                printf("in()%f\n", tmp);
			}
			else
			{
				if (s[i]=='+'||s[i]=='-'||s[i]=='*'||s[i]=='/')
				{
					if (op.empty())
					{
						op.push(s[i]);
					}
					else
					{
						if (piror[s[i]-42] < piror[op.top()-42])
						{
							calculate(num,op);
						}
						op.push(s[i]);
					}
				}
			}
		}
	}
	calculate(num,op);//计算剩下的
    result=num.top();
    num.pop();
    printf("size of number %d\n",num.size());
    return result;
}








int main()
{
	int i;//枚举下标
	int j = 0;
	int l = 0;
	int m = 0;
    double result;
    char s[1000];
    char ss[1000];
    char sss[1000];
    char ssss[1000];

    stack<char> op(500);//运算符栈
    stack<double> num(1000);//数值栈

    cin.getline(s,1000);

    for (int k = 0; k < 1000; k++)
    {
    	if (s[k] != ' ' && s[k] != '\t')
    	{
    		ss[j] = s[k];
    		j++;
    	}
    }

    for (int k = 0; k < 1000; k++)
    {
    	if (ss[k]=='.')
    	{
    		if (ss[k-1]<'0' || ss[k-1]>'9')
    		{
    			sss[l] = '0';
    			l++;
    		}
    	}
    	sss[l] = ss[k];
    	l++;
    }

    for (int k = 0; k < 1000; k++)
    {
    	ssss[m] = sss[k];
    	m++;
    	if (sss[k]=='.')
    	{
    		if (sss[k+1]<'0' || sss[k+1]>'9')
    		{
    			ssss[m] = '0';
    			m++;
    		}
    	}
    }

    result=exec(ssss,i,'\0');
    i=0;

    cout<<result<<endl;
    printf("hhhhhhhhhhhhhhhhh\n");
	return 0;
}

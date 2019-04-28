#include <iostream>
#include <stdio.h>

using namespace std;

const int piror[8]={0,0,2,1,0,1,0,2};
//ASCII ## 40:(, 42:*, 43:+, 44:', 45:-, 46:., 47:/, 48:0, 49:1

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

    int size();
    bool empty();
    void push(type elem);
    type top();
    type pop();
};

template<class type>
int stack<type>::size()
{
    return toppp+1;
}

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


double calculate(double a, double b, char op)
{
    switch(op)
    {
        case '+':return a+b;break;
        case '-':return a-b;break;
        case '*':return a*b;break;
        case '/':return a/b;break;
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


int main()
{
    stack<char> op(2000);//运算符栈
    stack<double> num(2000);//数值栈
    
    int i = 0;//枚举下标
    int j = 0;
    int l = 0;
    int m = 0;
    double result;
    char s[2000];
    char ss[2000];
    char sss[2000];
    char s0[2000];

    cin.getline(s,2000);

    for (int k = 0; k < 2000; k++)//去除空格和tab
    {
        if (s[k] != ' ' && s[k] != '\t')
        {
            ss[j] = s[k];
            j++;
        }
        if (s[k] == '\0')
        {
            break;
        }
    }

    for (int k = 0; k < 2000; k++)//前补0
    {
        if (ss[k]=='.')
        {
            if (ss[k-1]<'0' || ss[k-1]>'9' || k==0)
            {
                sss[l] = '0';
                l++;
            }
        }
        sss[l] = ss[k];
        l++;
        if (ss[k] == '\0')
        {
            break;
        }
    }

    for (int k = 0; k < 2000; k++)//后补0
    {
        s0[m] = sss[k];
        m++;
        if (sss[k]=='.')
        {
            if (sss[k+1]<'0' || sss[k+1]>'9')
            {
                s0[m] = '0';
                m++;
            }
        }
        if (sss[k] == '\0')
        {
            break;
        }
    }


    for (; s0[i] != '\0'; i++)
    {
        if (s0[i]>='0'&&s0[i]<='9')
        {   
            double a = getnumber(s0,i);
            num.push(a);
        }
        if (s0[i] == '+' || s0[i] == '-' || s0[i] == '*' || s0[i] == '/')
        {
            if (op.empty())
            {
                op.push(s0[i]);
            }
            else 
            {
                if (piror[s0[i]-40] > piror[op.top()-40])
                {
                    op.push(s0[i]);
                }
                else
                {
                    while(piror[s0[i]-40] <= piror[op.top()-40])
                    {
                        char opp = op.pop();
                        double b = num.pop();
                        double a = num.pop();
                        double tmp = calculate(a, b, opp);
                        num.push(tmp);
                        if (op.empty())
                        {
                            break;
                        }
                    }
                    op.push(s0[i]);
                }
            }
        }
        else if (s0[i] == '(')
        {
            op.push(s0[i]);
        }
        else if (s0[i] == ')')
        {
            while(op.top() != '(')
            {
				char opp = op.pop();
                double b = num.pop();
                double a = num.pop();
                double tmp = calculate(a, b, opp);
                num.push(tmp);
            }
        op.pop();
        }
    }

    while(!op.empty())
    {
        char opp = op.pop();
        double b = num.pop();
        double a = num.pop();
        double tmp = calculate(a,b,opp);
        num.push(tmp);
    }

    result = num.pop();

    //cout<<result<<endl;
    printf("%.6f\n", result);

    return 0;
}

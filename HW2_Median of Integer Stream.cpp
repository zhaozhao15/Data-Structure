#include <iostream>   
using namespace std;

template <class T>
class MaxHeap{
	public:
		T *mHeap;         // 数据
		int mCapacity;    // 总的容量
		int mSize;        // 实际容量
		void filterdown(int start, int end);
		void filterup(int start);
		MaxHeap(int capacity);
		~MaxHeap();
		int remove(int index);
		int insert(T data);
		void print();
		int getlv();
		int getspace();
};

template <class T>
MaxHeap<T>::MaxHeap(int capacity)
{
    mSize = 0;
    mCapacity = capacity;
    mHeap = new T[mCapacity];
}

template <class T>
MaxHeap<T>::~MaxHeap() 
{
    mSize = 0;
    mCapacity = 0;
    delete[] mHeap;
}

template <class T>
int MaxHeap<T>::getlv() 
{
    int tmp = 1;
	int j = 1;
	while(tmp <= mSize)
	{
		tmp *= 2;
		j++;
	}
	return j-1;
}

template <class T>
int MaxHeap<T>::getspace() 
{
	int lv = getlv();
	int tmp = 1;
	for (int i = 0; i < lv; ++i)
	{
		tmp *= 2;
	}
    return (tmp-1-mSize);
}

template <class T>
void MaxHeap<T>::filterup(int start) //最大堆的向上调整算法(从start开始向上直到0，调整堆),start -- 被上调节点的起始位置(一般为数组中最后一个元素的索引)
{
	int c = start;            // 当前节点(current)的位置
	int p = (c-1)/2;          // 父(parent)结点的位置，下取整
	T tmp = mHeap[c];         // 当前节点(current)的大小
//第N个节点的左孩子的索引值是(2N+1)，右孩子的索引是(2N+2)。
	while(c > 0)
	{
		if(mHeap[p] >= tmp)
			break;
		else
		{
			mHeap[c] = mHeap[p];
			c = p;
			p = (p-1)/2;
		}
	}
	mHeap[c] = tmp;
}

template <class T>
int MaxHeap<T>::insert(T data)
{
	mHeap[mSize] = data;        // 将"数组"插在表尾
	filterup(mSize);            // 向上调整堆
	mSize++;                    // 堆的实际容量+1
	return 0;
}

//start -- 被下调节点的起始位置(一般为0，表示从第1个开始)
//end   -- 截至范围(一般为数组中最后一个元素的索引)

template <class T>
void MaxHeap<T>::filterdown(int start, int end)
{
	int c = start;          // 当前(current)节点的位置
	int l = 2*c + 1;        // 左(left)孩子的位置
	T tmp = mHeap[c];       // 当前(current)节点的大小

	while(l <= end)
	{
		// "l"是左孩子，"l+1"是右孩子
		if(l < end && mHeap[l] < mHeap[l+1])
		    l++;        // 左右两孩子中选择较大者，即mHeap[l+1]
		if(tmp >= mHeap[l])
		    break;        //调整结束
		else
		{
			mHeap[c] = mHeap[l];
			c = l;
			l = 2*l + 1;
		}
	}
	mHeap[c] = tmp;
}

template <class T>
int MaxHeap<T>::remove(int index)
{
	mHeap[index] = mHeap[--mSize];    // 用最后元素填补
	filterdown(index, mSize-1);        // 从index位置开始自上向下调整为最大堆
	
	return 0;
}

template <class T>
void MaxHeap<T>::print()
{
	int a = 2;
    for (int i=0; i<mSize; i++)
    {
    	if ((i+1+1)%a == 0)
    	{
    		a*=2;
    		printf("%d\n",mHeap[i]);
    	}
    	else
    		printf("%d ", mHeap[i]);	
    }
    for (int i = 0; i < getspace(); ++i)
    {
    	if (i == getspace()-1)
    		printf("S\n");
		else
			printf("S ");
    }
}




//最小堆========================================================
//=============================================================
//=============================================================
//=============================================================







template <class T>
class MinHeap{
    public:
        T *mHeap;        // 数据
        int mCapacity;    // 总的容量
        int mSize;        // 实际容量
        void filterdown(int start, int end);
        void filterup(int start);
        MinHeap(int capacity);
        ~MinHeap();
        int remove(int index);
        int insert(T data);
        void print();
        int getlv();
        int getspace();
};

template <class T>
MinHeap<T>::MinHeap(int capacity)
{
    mSize = 0;
    mCapacity = capacity;
    mHeap = new T[mCapacity];
}

template <class T>
MinHeap<T>::~MinHeap() 
{
    mSize = 0;
    mCapacity = 0;
    delete[] mHeap;
}

template <class T>
int MinHeap<T>::getlv() 
{
    int tmp = 1;
	int j = 1;
	while(tmp <= mSize)
	{
		tmp *= 2;
		j++;
	}
	return j-1;
}

template <class T>
int MinHeap<T>::getspace() 
{
	int lv = getlv();
	int tmp = 1;
	for (int i = 0; i < lv; ++i)
	{
		tmp *= 2;
	}
    return (tmp-1-mSize);
}

template <class T>
void MinHeap<T>::filterdown(int start, int end)
{
    int c = start;          // 当前(current)节点的位置
    int l = 2*c + 1;     // 左(left)孩子的位置
    T tmp = mHeap[c];    // 当前(current)节点的大小

    while(l <= end)
    {
        // "l"是左孩子，"l+1"是右孩子
        if(l < end && mHeap[l] > mHeap[l+1])
            l++;        // 左右两孩子中选择较小者，即mHeap[l+1]
        if(tmp <= mHeap[l])
            break;        //调整结束
        else
        {
            mHeap[c] = mHeap[l];
            c = l;
            l = 2*l + 1;   
        }       
    }   
    mHeap[c] = tmp;
}
 
template <class T>
int MinHeap<T>::remove(int index)
{
    mHeap[index] = mHeap[--mSize];        // 用最后元素填补
    filterdown(index, mSize-1);    // 从index号位置开始自上向下调整为最小堆

    return 0;
}

template <class T>
void MinHeap<T>::filterup(int start)
{
    int c = start;            // 当前节点(current)的位置
    int p = (c-1)/2;        // 父(parent)结点的位置 ,这里会自动下取整
    T tmp = mHeap[c];        // 当前节点(current)的大小

    while(c > 0)
    {
        if(mHeap[p] <= tmp)
            break;
        else
        {
            mHeap[c] = mHeap[p];
            c = p;
            p = (p-1)/2;   
        }       
    }
    mHeap[c] = tmp;
}

template <class T>
int MinHeap<T>::insert(T data)
{
    mHeap[mSize] = data;        // 将"数组"插在表尾
    filterup(mSize);            // 向上调整堆
    mSize++;                    // 堆的实际容量+1

    return 0;
}

template <class T>
void MinHeap<T>::print()
{
	int a = 2;
    for (int i=0; i<mSize; i++)
    {
    	if ((i+1+1)%a == 0)
    	{
    		a*=2;
    		printf("%d\n",mHeap[i]);
    	}
    	else
    		printf("%d ", mHeap[i]);	
    }
    for (int i = 0; i < getspace(); ++i)
    {
    	if (i == getspace()-1)
    		printf("S\n");
		else
			printf("S ");
    }
}




////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////




int main()
{
	MinHeap<int> min(10000);
	MaxHeap<int> max(10000);
	int num[10000];  //最后以12344321结束
	int median;

	int i = 0;
	while (scanf("%d%*c", num + i++) == 1)
		;
	num[i-1] = 12344321;
	

	if (num[0] < num[1])
	{
		max.insert(num[0]);
		min.insert(num[1]);
	}
	else
	{
		max.insert(num[1]);
		min.insert(num[0]);
	}

	median = (num[0]+num[1])/2;
	printf("%d", median);
	if ((num[0]+num[1])%2==0)
		printf("\n");
	else
		printf(".5\n");

	min.print();
	max.print();


	for (int i = 2; i < 10000; i++)
	{
		if (num[i] == 12344321)
			break;

		if (num[i] < max.mHeap[0])
			max.insert(num[i]);
		else
			min.insert(num[i]);

		if (max.mSize - min.mSize > 1)
		{
			int tmp = max.mHeap[0];
			max.remove(0);
			min.insert(tmp);
		}
		else if (min.mSize - max.mSize > 1)
		{
			int tmp = min.mHeap[0];
			min.remove(0);
			max.insert(tmp);
		}

		if (max.mSize == min.mSize)
		{
			median = (max.mHeap[0]+min.mHeap[0])/2;
			printf("%d", median);
			if ((max.mHeap[0]+min.mHeap[0])%2==0)
				printf("\n");
			else
				printf(".5\n");
		}
		else if (max.mSize > min.mSize)
		{	
			median = max.mHeap[0];
			printf("%d\n", median);
		}
		else
		{	
			median = min.mHeap[0];
			printf("%d\n", median);
		}
		min.print();
		max.print();
	}

	return 0;
}


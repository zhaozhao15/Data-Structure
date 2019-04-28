#include <cstdio>
#include <cstdlib>
#include <cstring>
#define N 100000
using namespace std;
typedef unsigned char byte;
typedef unsigned int uint;

template<typename T> inline void swap(T &a, T &b){
	T t=a;
	a=b,b=t;
}

template<typename T, unsigned int max_len_heap, class cmp>
class heap{
private:
	T data[max_len_heap];
	unsigned int len_heap;
	cmp cmper;
public:
	heap():len_heap(0){}
	unsigned int size(){return len_heap;}
	void push(const T &x);
	T pop();
	const T& top(){return data[1];}
};

template<typename T, unsigned int max_len_heap, class cmp>
void heap<T,max_len_heap,cmp>::push(const T &x)
{
	data[++len_heap]=x;
	for(int i=len_heap;i>1&&cmper(data[i],data[i/2]);i/=2)
		swap(data[i/2],data[i]);
}

template<typename T, unsigned int max_len_heap, class cmp>
T heap<T,max_len_heap,cmp>::pop()
{
	T ans=data[1];
	data[1]=data[len_heap--];
	for(unsigned int i=1;i<=len_heap;)
	{
		unsigned int t=i;
		if(t*2<=len_heap && cmper(data[t*2],data[i])) i=t*2;
		if(t*2+1<=len_heap && cmper(data[t*2+1],data[i])) i=t*2+1;
		if(t!=i) swap(data[i],data[t]);else break;
	}
	return ans;
}

struct node{
	uint weight;
	node *lch, *rch;
	uint minb;
}poor[N*2],*p_poor=poor;

struct cmp_Huffman{
	bool operator () (const node *a, const node *b)
	{
		if(a->weight!=b->weight) return a->weight<b->weight;
		return a->minb<b->minb;
	}
};

template<typename T> inline T min(const T &a, const T &b){return a<b?a:b;}

heap<node*,N,cmp_Huffman> forest;
uint cnt_ascii[256]={0};
uint HuffmanCode[256];
uint width_HuffmanCode[256];

void encode_gen_cnt(byte *raw, uint len)
{
	while(len--) cnt_ascii[*(raw++)]++;
}

void decode_gen_cnt(byte *raw)
{
	raw += 8; // Skip magic header
	memcpy(cnt_ascii, raw ,256*sizeof(uint));
}

void gen_HuffmanTree()
{
	for(uint i=0;i<256;++i)
	{
		if(!cnt_ascii[i]) continue;
//		fprintf(stderr,"%d: %d\n",i ,cnt_ascii[i]);
		*(++p_poor) = (node){cnt_ascii[i],NULL,NULL,i};
		forest.push(p_poor);
	}
	while(forest.size()>1)
	{
		node *minn = forest.pop();
		node *subn = forest.pop();
		*(++p_poor)=(node){minn->weight+subn->weight,subn,minn,min(minn->minb,subn->minb)};
		forest.push(p_poor);
	}
}

void gen_HuffmanCode(node *now, uint code, uint width)
{
	if(!now->lch && !now->rch)
	{
		HuffmanCode[now->minb]=code;
		width_HuffmanCode[now->minb]=width;
		return;
	}
	if(now->lch) gen_HuffmanCode(now->lch,code,width+1);
	if(now->rch) gen_HuffmanCode(now->rch,code+(1<<width),width+1);
}

byte buffer[N];
void encode_output(byte *raw, uint len)
{
	fwrite("DECODE",sizeof(char),6,stdout);
	fwrite("HUFFMAN",sizeof(char),8,stdout);
	fwrite((char*)cnt_ascii,sizeof(uint),256,stdout);
	uint offset=0;
	while(len--)
	{
		*((uint*)&buffer[offset>>3]) |= HuffmanCode[*raw]<<(offset&7);
		offset += width_HuffmanCode[*raw];
		raw++;
	}
	fwrite(buffer, sizeof(byte), (offset+7)>>3, stdout);
}

int get_uncompress(uint code)
{
	node *now = forest.top();
	while(now->lch || now->rch)
	{
		if(code&1) now=now->rch;
		else now=now->lch;
		code >>= 1;
	//	if(!now) fputs("ASSERT!",stderr);
	}
	return (int)now->minb;
}

void decode_output(byte *raw)
{
	raw += 8; // Skip magic header
	raw += 256*sizeof(uint); // Skip frequencies
	printf("ENCODE");
	uint cnt_char=0;
	for(uint i=0;i<256;++i) cnt_char+=cnt_ascii[i];
	uint offset=0;
	for(;cnt_char>0;--cnt_char)
	{
		uint data_compress=*(uint*)&raw[offset>>3];
		data_compress >>= (offset&7);
		int c = get_uncompress(data_compress);
		putchar(c);
		offset += width_HuffmanCode[c];
	}
}

byte raw[N];
int main()
{
	freopen("t.in","rb",stdin);
	freopen("t.out","wb",stdout);
	uint len=fread(raw, sizeof(byte), N, stdin);
	if(raw[0]!='E' && raw[0]!='D') return puts("Invalid Input"),-1;
	if(raw[0]=='E') encode_gen_cnt(raw+6, len-6);
	else decode_gen_cnt(raw+6);
	gen_HuffmanTree();
	if(forest.size()>0) gen_HuffmanCode(forest.top(), 0, 0);
	if(raw[0]=='E') encode_output(raw+6, len-6);
	else decode_output(raw+6);
	return 0;
}

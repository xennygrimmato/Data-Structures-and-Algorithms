#include <bits/stdc++.h>
using namespace std;

#define INF                         (int)1e9
#define forall(i,a,b)               for(int i=a;i<b;i++)
#define bitcount                    __builtin_popcount  // counts 1 eg- 1101 has value 3
// with bitcount be careful with data types

// Useful container manipulation / traversal macros
#define forall(i,a,b)               for(int i=a;i<b;i++)
#define foreach(v, c)               for( typeof( (c).begin()) v = (c).begin();  v != (c).end(); ++v)
#define all(a)                      a.begin(), a.end()
#define in(a,b)                     ( (b).find(a) != (b).end())
#define pb                          push_back
#define fill(a,v)                    memset(a, v, sizeof a)
#define sz(a)                       ((int)(a.size()))
#define mp                          make_pair

// comparision Guys 
#define maX(a,b)                     ( (a) > (b) ? (a) : (b))
#define abs(a)                       ( (a) > (0) ? (a) : (-a))
#define miN(a,b)                     ( (a) < (b) ? (a) : (b))
#define checkbit(n,b)                ( (n >> b) & 1)
#define DREP(a)                      sort(all(a)); a.erase(unique(all(a)),a.end()) //deletes repeat

// The bit standard guys
#define bit(x,i)                    (x&(1<<i))  //select the bit of position i of x
#define lowbit(x)                   ((x)&((x)^((x)-1))) //get the lowest bit of x
#define hBit(msb,n)        asm("bsrl %1,%0" : "=r"(msb) : "r"(n)) //get the highest bit of x, maybe the fastest
#define higbit(x)                   (1 << ( int) log2(x) )

// The vectors and pairs
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int,int> ii;
#define ft                 first
#define sd                 second

// the data types
#define ll long long
#define st string

int a[10000],s[10000],n,NEXT_FREE_INDEX = 1,root[10000],L[10000],R[10000],ir;

/*
  Here is how the persistent segtree worksWe have an array a1,a2,...,an and at first q update queries 
  and then u ask queries which you have to answer online.

Each update query gives you numbers p and v and asks you to increase ap by v .

Each ask query, gives you three numbers i and x and y and asks you to print the value of ax1+ax2+...+ay after
performing ith query.Each update query, changes the value of O(log(n)) nodes in the segment tree, 
so you should keep rest of nodes (not containing p) and create log(n) new nodes. Totally, you need 
to have q.log(n) nodes. So, you can not use normal segment's indexing, you should keep the index of 
children in the arrays L and R.
If you update a node, you should assign a new index to its interval (for i-th query).

You should keep an array root[q] which gives you the index of the interval of the root ( [0,n) )
after performing each query and a number ir=0 which is its index in the initial 
segment tree (ans of course, an array s[MAXNODES] which is the sum of elements in that node). 
Also you should have a NEXT_FREE_INDEX = 1 which is always the next free index for a node.

First of all, you need to build the initial segment tree :

(In these codes, all arrays and queries are 0-based)


*/

void build(int id = ir,int l = 0,int r = n){
	if(r - l < 2){
		s[id] = a[l];
		return ;
	}
	int mid = (l+r)/2;
	L[id] = NEXT_FREE_INDEX ++;
	R[id] = NEXT_FREE_INDEX ++;
	build(L[id], l, mid);
	build(R[id], mid, r);
	s[id] = s[L[id]] + s[R[id]];
	
}

int upd(int p, int v,int id,int l = 0,int r = n){
	int ID =  NEXT_FREE_INDEX ++; // index of the node in new version of segment tree
	if(r - l < 2){
		s[ID] = (a[p] += v);
		return ID;
	}
	int mid = (l+r)/2;
	L[ID] = L[id], R[ID] = R[id]; // in case of not updating the interval of left child or right child
	if(p < mid)
		L[ID] = upd(p, v, L[ID], l, mid);
	else
		R[ID] = upd(p, v, R[ID], mid, r);
		s[ID]=s[L[ID]]+s[R[ID]];
		
		return ID;
	
}

int sum(int x,int y,int id,int l = 0,int r = n){
	if(x >= r or l >= y)	return 0;
	if(x <= l && r <= y)	return s[id];
	int mid = (l+r)/2;
	return sum(x, y, L[id], l, mid) +
	       sum(x, y, R[id], mid, r);
}

int main()
{
	cout << " the orignal segtre \n";
	a[0]=4;a[1]=7;a[2]=2;a[3]=3;a[4]=5;a[5]=9;
	// Query type  1,0,number of elements
    build(0,0,6);
	
	/*Word of CAUTION (For the first query (with index 0) we should run root[0]=upd(p, v, ir) and 
	for the rest of them,for j-th query se should run root[j]=upd(p, v,root[j-1]) )*/
	cout << "The origninal thing is \n";
	forall(i,0,25)cout << s[i] <<" ";cout << "\n";
    root[0]=upd(0,2,0,0,6);      
    root[1]=upd(2,1,root[0],0,6);
    root[2]=upd(1,4,root[1],0,6);
    cout << "the changed thing is \n";
    forall(i,0,25)cout << s[i] <<" ";cout << "\n";
     int  k=sum(0,3,0,0,6);cout << k <<"\n";
	      k=sum(0,3,root[0],0,6);cout << k <<"\n";
	      k=sum(0,3,root[1],0,6);cout << k <<"\n";
	      k=sum(0,3,root[2],0,6);cout << k <<"\n";
}
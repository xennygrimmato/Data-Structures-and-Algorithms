#include <bits/stdc++.h>
#include <iostream>
#include <list>
#include <limits.h>
#include <cstdio>
#include <map>
#include <math.h>
#include <string.h>
#include <algorithm>
#include <string.h>
using namespace std;
#define s(n)                        scanf("%lld",&n)
#define sc(n)                       scanf("%c",&n)
#define sl(n)                       scanf("%lld",&n)
#define sf(n)                       scanf("%Lf",&n)
#define ss(n)                       scanf("%s",n)
#define maX(a,b)                     ( (a) > (b) ? (a) : (b))
// Useful constants
#define INF                         (int)1e9
#define EPS                         1e-9

// Useful hardware instructions
#define bitcount                    __builtin_popcount
#define gcd                         __gcd

// Useful container manipulation / traversal macros
#define forall(i,a,b)               for(long long i=a;i<b;i++)
#define foreach(v, c)               for( typeof( (c).begin()) v = (c).begin();  v != (c).end(); ++v)
#define all(a)                      a.begin(), a.end()
#define in(a,b)                     ( (b).find(a) != (b).end())
#define pb                          push_back
#define fill(a,v)                    memset(a, v, sizeof a)
#define sz(a)                       ((int)(a.size()))
#define mp                          make_pair





int abse(int a)
{
    if(a>0)return a;
    return -a;
}

typedef  long long ULL;

ULL mulmod(ULL a, ULL b, ULL c){
	ULL x = 0,y = a%c;

	while(b>0){
		if(b&1) x = (x+y)%c;
		y = (y<<1)%c;
		b >>= 1;
	}

	return x;
}

ULL pow(ULL a, ULL b, ULL c){
	ULL x = 1, y = a;

	while(b>0){
		if(b&1) x = mulmod(x,y,c);
		y = mulmod(y,y,c);
		b >>= 1;
	}

	return x;
}

bool isPrime(ULL p, int it){
	if(p<2) return false;
	if(p==2) return true;
	if((p&1)==0) return false;

	ULL s = p-1;
	while(s%2==0) s >>= 1;

	while(it--){
		ULL a = rand()%(p-1)+1,temp = s;
		ULL mod = pow(a,temp,p);

		if(mod==-1 || mod==1) continue;

		while(temp!=p-1 && mod!=p-1){
			mod = mulmod(mod,mod,p);
			temp <<= 1;
		}

		if(mod!=p-1) return false;
	}

	return true;
}



int main()
{
    ULL test,n;
    test=10000;
    s(test);
    forall(i,0,test)
    {
        s(n);
        {if(isPrime(n,5))
        printf("%lld\n",n);
    }

}

#include <iostream>
#define MAXN 1000005
using namespace std;

long long etf[MAXN];

void cal_etf()
{
    for(int i = 1 ;i <= MAXN ; i++ )
    	etf[i]=i;
    for(int i=2 ; i<= MAXN ; i++ )
        if ( etf[i] == i)
            for(int j = 2*i ; j <= MAXN ; j += i)
            	etf[j] -=  etf[j]/ i ;
    
    etf[1]=1;
    for(int i=2 ; i<= MAXN ; i++) {	
        if ( etf[i]==i) //if that number is prime
    		etf[i] = i-1;
    }
}

int main()
{
    cal_etf();
    for(int i=1;i<=10;i++) cout<<etf[i]<<" ";
}

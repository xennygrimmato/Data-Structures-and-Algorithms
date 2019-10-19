#include <iostream>
#define MAXN 1000005
using namespace std;

long long etf[MAXN];

void cal_etf()
{
    for(int i = 1 ;i <= MAXN ; i++ )
    	etf[i]=i;
    }

    for(int i=2;i<=MAXN;i++){
        if(etf[i]==i){
            etf[i]=i-1;
            for(int j=2;j*i<=MAXN;j++){
                etf[j*i]=(1-(1/i));
            }
        }
    }
}

int main()
{
    cal_etf();
    for(int i=1;i<=10;i++) cout<<etf[i]<<" ";
}

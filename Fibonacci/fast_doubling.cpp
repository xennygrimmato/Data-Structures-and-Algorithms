#include <bits/stdc++.h>

using namespace std;

#define MOD 1000000007;
long long int a,b,c,d;

void fast_fib(long long int n,long long int ans[])
{
    if(n == 0)
    {
        ans[0] = 0;
        ans[1] = 1;
        return;
    }
    fast_fib((n/2),ans);
    a = ans[0];             /* F(n) */
    b = ans[1];             /* F(n+1) */
    c = 2*b - a;
    if(c < 0)
        c += MOD;
    c = (a * c) % MOD;      /* F(2n) */
    d = (a*a + b*b) % MOD;  /* F(2n + 1) */
    if(n%2 == 0)
    {
        ans[0] = c;
        ans[1] = d;
    }
    else
    {
        ans[0] = d;
        ans[1] = c+d;
    }
}

int main()
{
    long long int n;        /* nth value to be found */
    scanf("%lld",&n);
    long long int ans[2]={0};
    fast_fib(n,ans);
    printf("%lld\n", ans[0]);
    return 0;
}

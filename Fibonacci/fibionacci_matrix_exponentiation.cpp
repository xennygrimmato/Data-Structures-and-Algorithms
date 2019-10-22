#include<bits/stdc++.h>
using namespace std;

void multiply(int a[2][2],int m[2][2])
{
	int fv = a[0][0] * m[0][0] + a[0][1] * m[1][0];
	int sv = a[0][0] * m[0][1] + a[0][1] * m[1][1];
	int tv = a[1][0] * m[0][0] + a[1][1] * m[1][0];
	int frv = a[1][0] * m[0][1] + a[1][1] * m[1][1];
	
	a[0][0] = fv;
	a[0][1] = sv;
	a[1][0] = tv;
	a[1][1] = frv;
}

void power(int a[2][2],int n)
{
	if(n==0||n==1)
		return;
	
	power(a,n/2);
	multiply(a,a);
	
	if(n%2 == 1)
	{
		int m[2][2] = {{1,1},{1,0}};
		multiply(a,m);	
	} 
}

int fib(int n)
{
		if(n==0)
			return 0;
			
		int a[2][2] = {{1,1},{1,0}};
		power(a,n-1);
		return a[0][0];
}

int main()
{
	cout<<fib(3)<<endl;
	return 0;
}

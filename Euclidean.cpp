
#include<bits/stdc++.h>

using namespace std;

int euclid(int a, int b)
{
        if (a==0)
        return b;
        else
        {
            return (b%a,a);
        }
        
}
int main()
{
    int a,b;
    cout << "Enter two numbers to find gcd" << endl;
    cin >> a >> b;
    euclid(a,b);
}


#include<bits/stdc++.h>
using namespace std;

int main() 
{
    vector<int> A{1,11,2,10,4,5,2};
    int n = A.size();
    if(n < 1)
    return 0;
    int lis[n];
    int lds[n];
    lis[0] = 1;
    lds[n-1] = 1;
    for(int i = 1 ; i < A.size() ; ++i)
    {
        lis[i] = 1;
        for(int j = 0 ; j < i ; ++j)
        {
            if(A[i] > A[j] && lis[i] < lis[j] + 1)
            lis[i] = lis[i] + 1;
        }
    }
    for(int i = n-2 ; i >= 0 ; --i)
    {
        lds[i] = 1;
        for(int j = n-1 ; j > i ; --j)
        {
            if(A[i] > A[j] && lds[i] < lds[j] + 1)
            lds[i] = lds[i] + 1;
        }
    }
    int max = lis[0] + lds[0] - 1;
    for(int i= 0 ; i < n ; ++i)
    {
        if(lis[i] + lds[i] - 1 > max)
        max = lis[i] + lds[i] - 1;
    }
    
    cout << "\nLength of longest bitonic subsequence : " << max;
    return 0;
}
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int LIS()
{
    int n;
    cin>>n; // Number of elements
    vector<int> d; // A possible solution that is one of the Longest Increasing Subsequences
    int elem;
    for(int i=0;i<n;i++)
    {
        cin>>elem;
        d.push_back(elem);
    }
    int dp[n];
    for(int i=0;i<n;i++){
        dp[i]=1;
    }
    for(int i=2;i<n;i++){
        for(int j=i-1;j>=0;j--){
            if(d[i]>=d[j]){
                dp[i]=max(dp[i],dp[j]+1);
            }
        }
    }
    int ans=INT_MIN;
    for(int i=0;i<n;i++){
        if(ans<dp[i]){
            ans=dp[i];
        }
    }
    cout<<ans<<endl;
}

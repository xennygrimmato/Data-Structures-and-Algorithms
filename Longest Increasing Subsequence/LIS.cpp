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
        //vector<int>::iterator it = upper_bound(d.begin(),d.end(),elem); // non-decreasing
        vector<int>::iterator it = lower_bound(d.begin(),d.end(),elem); // strictly increasing
        if(it == d.end()) d.push_back(elem);
        else *it=elem;
    }
    cout<<d.size();
}

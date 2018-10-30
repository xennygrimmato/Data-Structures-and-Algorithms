#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define o 100005
#define MOD 1000000007
#define pb push_back
#define mp make_pair
#define mem(a,b) memset(a,(b),sizeof(a))
#define lpo(a) for(int i=0;i<a;i++)
#define loop(a,x) for(int i=a;i<x;i++)
#define srt(x) sort(x.begin(),x.end())
#define all(x) x.begin(),x.end()
const ll MAX=1000000000000000001;
typedef pair<int,int> pii;
int knapSack(int W, int wt[], int val[], int n) 
{ 
   int i, w; 
   int K[n+1][W+1]; 
   for (i = 0; i <= n; i++) 
   { 
       for (w = 0; w <= W; w++) 
       { 
           if (i==0 || w==0) 
               K[i][w] = 0; 
           else if (wt[i-1] <= w) 
                 K[i][w] = max(val[i-1] + K[i-1][w-wt[i-1]],  K[i-1][w]); 
           else
                 K[i][w] = K[i-1][w]; 
       } 
   } 
  
   return K[n][W]; 
} 
  
int main() 
{ 
    int val[] = {20, 30, 40}; 
    int wt[] = {10, 20, 30}; 
    int  W = 50; 
    int n = sizeof(val)/sizeof(val[0]); 
    cout<<knapSack(W, wt, val, n); 
    return 0; 
} 
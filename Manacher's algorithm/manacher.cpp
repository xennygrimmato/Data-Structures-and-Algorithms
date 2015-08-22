#include<bits/stdc++.h>
using namespace std;
//reference http://articles.leetcode.com/2011/11/longest-palindromic-substring-part-ii.html
//a sample problem which needs this algorithm - http://www.spoj.com/problems/MSUBSTR/
int manacher_algorithm(string x)
{
    string y="#";
    int l=x.length();
    int i=0;
    int len=0;
    int p[10001]={0}; //array for preprocessing
    int c=0,r=0,i_mirror=0;
    for(i=0;i<l;i++) //insert special character # between characters of a string
    {
        y+=x[i];
        y+="#";
    }
    len=y.length();
    c=1,r=1,i_mirror=0;
    for(i=1;i<len;i++)
    {
        i_mirror=2*c-i;
        p[i]=(r>i)?min(r-i,p[i_mirror]):0;
        while(i-p[i]-1>=0 && p[i]+i-1<len && (y[p[i]+i-1]==y[i-1-p[i]])) //palindrome expands past right edge
        {
            p[i]+=1;
        }
        if(i+p[i]>r) //reassgining center of palindrome at p[i]
        {
            r=p[i]+i;
            c=i;
        }
    }
    int max_val=INT_MIN;
    for(i=0;i<len;i++) //finding maximum value of p[i]
    {
        if(p[i]>max_val)
            max_val=p[i];
    }
    int counter=0;
    for(i=0;i<len;i+=1)  //finding number of occurences of max_val in p[]
        if(p[i]==max_val)
            counter++;
    cout<<max_val-1<<" "<<counter<<endl; //print the length and number of occurrences
}
int main()
{
    int t=0,i=0;
    string x;
    //input number of testcases
    cin>>t;
    while(t--)
    {
        cin>>x;
        manacher_algorithm(x);
    }
    return 0;
}

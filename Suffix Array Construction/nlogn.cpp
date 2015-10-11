#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#define MAXN 1001
using namespace std;

struct Triple {
    int index;
    int fh, sh;
};

int cmp(Triple a, Triple b) {
    if(a.fh==b.fh) return a.sh<b.sh;
    else return a.fh<b.fh;
}

vector < Triple > rad[MAXN];

int main() {
    string s;
    cin>>s;
    int len = s.length();
    int rank[len][20];
    Triple a[len];
    for(int i=0;i<len;i++) {
        rank[i][0] = s[i]-'a';
    }
    for(int i=1,stp=1; i<len; i*=2,stp+=1) {

        // build the current rank array
        for(int j=0;j<len;j++) {
            a[j].index = j;
            a[j].fh = rank[j][stp-1];
            if (j+i<len) a[j].sh = rank[j+i][stp-1];
            else a[j].sh = -1;
        }

        // radix sort part 1: for sorting second half
        for(int i=0;i<MAXN;i++) rad[i].clear();
        for(int i=0;i<len;i++) {
            rad[a[i].sh+1].push_back(a[i]);
        }
        int start = 0;
        for(int i=0;i<MAXN;i++) {
            for(int j=0;j<rad[i].size();j++) {
                a[start] = rad[i][j];
                start += 1;
            }
        }
        // radix sort part 2: for sorting first half
        for(int i=0;i<MAXN;i++) rad[i].clear();
        for(int i=0;i<len;i++) {
            rad[a[i].fh+1].push_back(a[i]);
        }
        start = 0;
        for(int i=0;i<MAXN;i++) {
            for(int j=0;j<rad[i].size();j++) {
                a[start] = rad[i][j];
                start += 1;
            }
        }

        // set rank to the sorted part
        start = 0;
        rank[a[0].index][stp] = start;
        for(int i=1;i<len;i++) {
            if(a[i].fh != a[i-1].fh || a[i].sh != a[i-1].sh ) {
                start += 1;
            }
            rank[a[i].index][stp] = start;
        }
    }
    for(int i=0;i<len;i++) {
        cout<<a[i].index<<" ";
    }
    cout<<"\n";
    return 0;
}

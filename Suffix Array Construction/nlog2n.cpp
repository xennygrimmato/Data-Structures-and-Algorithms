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
    int mx_stp = -1;
    int mx = -1;
    for(int i=1,stp=1; i<len; i*=2,stp+=1) {

        // build the current rank array
        for(int j=0;j<len;j++) {
            a[j].index = j;
            a[j].fh = rank[j][stp-1];
            if (j+i<len) a[j].sh = rank[j+i][stp-1];
            else a[j].sh = -1;
        }
        sort(a, a+len, cmp);

        // set rank to the sorted part
        int start = 0;
        rank[a[0].index][stp] = start;
        for(int i=1;i<len;i++) {
            if(a[i].fh != a[i-1].fh || a[i].sh != a[i-1].sh ) {
                start += 1;
            }
            rank[a[i].index][stp] = start;
        }
        mx_stp = stp;
    }
    for(int i=0;i<len;i++) {
        cout<<a[i].index<<" ";
    }
    cout<<"\n";
    return 0;
}

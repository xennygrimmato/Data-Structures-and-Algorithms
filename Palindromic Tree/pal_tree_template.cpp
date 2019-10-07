#include<bits/stdc++.h>
using namespace std;

#define ll long long int
#define LD long double

const int N = 100010;

int inf = 1e9;
int mod = 1e9 + 7;


struct PalindromicTree {

    struct node {
        int next[26], suffixlink, len;
        int cnt, num;
        node(int l = 0) : suffixlink(0), len(l), cnt(0), num(0) {
            for(int i = 0; i < 26; i++)
                next[i] = 0;
        }
    };

    vector<node> state;
    vector<int> s;
    int last, n;

    PalindromicTree() {
        last = 1;
        n = 0;
        state.push_back(0);
        state.push_back(-1);
        state[0].suffixlink = 1;
        s.push_back(-1); //Breaking character
    }

    void reset() {
        state.clear();
        s.clear();
        last = 1;
        n = 0;
        state.push_back(0);
        state.push_back(-1);
        state[0].suffixlink = 1;
        s.push_back(-1); //Breaking character
    }

    int get_link(int x) {
        while(s[n - state[x].len - 1] != s[n]) {
            x = state[x].suffixlink;
        }
        return x;
    }

    void add(char nxt) {
        int c = nxt - 'a';
        s.push_back(c);
        n++;
        int cur = get_link(last);

        if(!state[cur].next[c]) {
            int now = state.size();
            state.push_back(state[cur].len + 2);
            state[now].suffixlink = state[get_link(state[cur].suffixlink)].next[c];
            state[cur].next[c] = now;
            state[now].num = state[state[now].suffixlink].num + 1;
        }

        last = state[cur].next[c];
        state[last].cnt++;
    }

    int size() {
        return state.size() - 2;
    }
};

#include <bits/stdc++.h>

using namespace std;

#define end _end
#define next _nxt

const int MaxN = 500500;
int sz = 0;

int next[27][MaxN];
int end[MaxN];
bool created[MaxN];

void insert (string &s) {
	int v = 0;

	for (int i = 0; i < s.size(); ++i) {
		int c = s[i] - 'a';
		if (!created[next[c][v]]) {
			next[c][v] = ++sz;
			created[sz] = true;
		}
		v = next[c][v];
	}
	++end[v];
}

bool search (string tmp) {
	int v = 0;
	
	for (int i = 0; i < tmp.size(); ++i) {
		int c = tmp[i] - 'a';
		if (!created[next[c][v]])
			return false;
		v = next[c][v];
	}
	return end[v] > 0;
}

int main () {
	string keys[] = {"hi", "hello", "you", "ekta", "me"};
	string output[] = {"NO", "YES"};

	for (int i = 0; i < 5; ++i)
		insert (keys[i]);

	cout << output[search ("my")] << endl;
	cout << output[search ("me")] << endl;
	
	return 0;
}

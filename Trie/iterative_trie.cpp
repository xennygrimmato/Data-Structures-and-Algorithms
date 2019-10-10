// C++ implementation of trie
#include <bits/stdc++.h>

using namespace std;

#define end _end
#define next _nxt

const int MaxN = 500500;
int sz = 0;

int next[27][MaxN];
int end[MaxN];
bool created[MaxN];
// insert key into trie
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
// return true if key present in trie and
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
	// keys supports lowercase and uppercase letters
	string keys[] = {"hi", "hello", "you", "ekta", "me"};
	string output[] = {"NO", "YES"};

	// construct trie
	for (int i = 0; i < 5; ++i)
		insert (keys[i]);

	cout << output[search ("my")] << endl;
	cout << output[search ("me")] << endl;
	
	return 0;
}

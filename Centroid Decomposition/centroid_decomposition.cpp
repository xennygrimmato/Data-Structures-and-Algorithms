// centroid_decomp.cpp
// Eric K. Zhang; Jul. 9, 2018

#include <bits/stdc++.h>
using namespace std;

#define MAXN 100013
int N;
vector<int> adj[MAXN];

namespace cd {
	int sz[MAXN];
	int cpar[MAXN];
	bool vis[MAXN];

	void dfs(int n, int p=-1) {
		sz[n] = 1;
		for (int v : adj[n]) if (v != p && !vis[v]) {
			dfs(v, n);
			sz[n] += sz[v];
		}
	}

	int centroid(int n) {
		dfs(n);
		int num = sz[n];
		int p = -1;
		do {
			int nxt = -1;
			for (int v : adj[n]) if (v != p && !vis[v]) {
				if (2 * sz[v] > num)
					nxt = v;
			}
			p = n, n = nxt;
		} while (~n);
		return p;
	}

	void centroid_decomp(int n=0, int p=-1) {
		int c = centroid(n);
		vis[c] = true;
		cpar[c] = p;
		for (int v : adj[c]) if (!vis[v]) {
			centroid_decomp(v, c);
		}
	}
}

using cd::centroid_decomp;
using cd::cpar;

int main() {
	N = 5;
	vector<pair<int, int> > edges = {{0, 1}, {1, 2}, {1, 3}, {3, 4}};
	for (auto p : edges) {
		adj[p.first].push_back(p.second);
		adj[p.second].push_back(p.first);
	}

	centroid_decomp();

	for (int i = 0; i < N; i++)
		cout << i << " -> " << cpar[i] << endl;
}

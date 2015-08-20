#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define INF 0x3f3f3f3f
#define MAXN 310
using namespace std;

class MaxFlow {
	public:
	vector<vector<int> > initial_g, g; // initial_g: stores initial capacities which should not be changed.
	vector<int> vis, from;
	int n, s, t; // no. of vertices, src, dst
	MaxFlow(int vertices) {
		n = vertices+1; // 0&1 based graphs both handled
		initial_g = vector<vector<int> >(n, vector<int>(n,0));
		g = vector<vector<int> >(n, vector<int>(n,0));
	}
	void add_edge(int u, int v, int w) {
		initial_g[u][v] = w;
		g[u][v] = w;
	}
	
	int bfs_augment() {
		vis = vector<int>(n,0);
		from = vector<int>(n,-1);
		
		queue<int> q;
		q.push(s);
		vis[s] = true;
		
		int where;
		bool reached;
		reached = false;
		
		// find augmenting path
		while(!q.empty()) {
			where = q.front();
			q.pop();
			for(int i=0;i<g[where].size();i++) { // iterate through neighbours of "where"
				int next = i;
				if(!vis[next] && g[where][next] > 0) {
					q.push(next);
					vis[next] = true;
					from[next] = where;
					if(next == t) { // if sink reached, augmenting path is found.
						reached = true;
						break;
					}
				}
			}
			if(reached) break;
		}
		
		int prev;
		int path_capacity = INF;
		where = t;
		while(from[where] > -1) { // path capacity = minimum edge in path
			prev = from[where];
			path_capacity = min(path_capacity, g[prev][where]);
			where = prev;
		}
		
		where = t;
		while(from[where] > -1) { // augment flow in graph by path capacity.
			prev = from[where];
			g[prev][where] -= path_capacity;
			g[where][prev] += path_capacity;
			where = prev;
		}
		if(path_capacity == INF) return 0;
		else return path_capacity;
	}
	
	int pfs_augment() {
		vis = vector<int>(n,0);
		from = vector<int>(n,-1);
		
		struct node {
			int vertex, priority, from;
			node(int v,p,f) {
				vertex = v, priority = p, from = f;
			}
		}
		priority_queue<int> pq;
		pq.push(node(s,INF,-1));
		int path_capacity = 0;
		while(!pq.empty()) {
			node aux = pq.top();
			pq.pop();
			
			int where = aux.vertex, cost = aux.priority;
			if(vis[where]) continue;
			from[where] = aux.from;
			
			if(where == sink) {
				path_capacity = cost;
				break;
			}
			
			vis[where] = true;
			for(int next=0;next<g[where].size();next++) {
				if(g[where][i] > 0) {
					int new_cost = min(cost, g[where][next]);
					pq.push(node(next,new_cost,where));
				}
			}
		}
		
		int where = sink;
		while(from[where] > -1) {
			int prev = from[where];
			g[prev][where] -= path_capacity;
			g[where][prev] += path_capacity;
			where = prev;
		}
		
		return path_capacity;
	}
	
	int get_max_flow(int _s, int _t) {
		s = _s, t = _t;
		int flow = 0;
		while(int increment = bfs_augment()) {
			flow += increment;
		}
		return flow;
	}
	
	void disp() {
        cerr << endl;
        cerr << "Flow from " << s << " to " << t << endl;
        for(int i = 0; i < n; ++i) for(int j = 0; j < n; ++j) if(initial_g[i][j] > 0) {
            cerr << i << " " << j << " " << g[i][j] << "/" << initial_g[i][j] << endl;
        }
        cerr << endl;
    }
};

int main() {
	int n,m;
	cin>>n>>m;
	MaxFlow f(n);
	int u,v,w;
	for(int i=0;i<m;i++) {
		cin>>u>>v>>w;
		f.add_edge(u,v,w);
	}
	cout<<f.get_max_flow(1,n)<<"\n";
}

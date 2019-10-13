#include <iostream>
#include <vector>
#include <queue>


using namespace std;


struct edge
{
	int to, cost;
};

const int maxN = 1000002; // Actualizar este valor
const int INF = 0x7fffffff;

vector<edge> g[maxN];

int cost[maxN];

void dijkstra(int s)
{
	priority_queue<pair<int,int>> pq;
	int node;
	int weig;
	int no;
	int we;
	cost[s] = 0;
	pq.push({0,s});

	while( !pq.empty() ) 
	{
	    node = pq.top().second;
	    weig = -pq.top().first;
	    pq.pop();

	    if ( weig > cost[node]) continue;

	    for ( edge e : g[node]){
	    	no = e.to;
	    	we = e.cost;

	    	if (cost[no] > cost[node] + we){
	    		cost[no] = cost[node] + we;
	    		pq.push({-cost[no],no});
	    	}

	    }
	}

}

#include <bits/stdc++.h>
#define MAXN 110

using namespace std;

typedef pair < double, int > di;

vector <di>ladj[MAXN];
double S[MAXN];

void Dijkstra(int V){
	priority_queue <di, vector<di>, greater<di> > fila;
	S[V] = 0;
	fila.push(make_pair(0.0, V));
	while(!fila.empty()){
		di X = fila.top();
		fila.pop();

		double dist = X.first;
		int v = X.second;
		if(S[v] < dist)continue;
		for(int i = 0; i < ladj[v].size(); i++){
			di X = ladj[v][i];
			if(S[X.second] > dist + X.first){
				S[X.second] = dist + X.first;
				fila.push(make_pair(S[X.second], X.second));
			}
			
		}
	}
}

int main(){
  return 0;
}

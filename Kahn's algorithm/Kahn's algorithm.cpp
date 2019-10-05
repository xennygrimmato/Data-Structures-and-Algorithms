#include <bits/stdc++.h>
#define ll long long int
#define v vector<int>
using namespace std;
int n, m;
v in_deg;
queue<int> q;
v res;
void BFS(v adj[], int curr)
{
    while (!q.empty())
    {
        curr = q.front();
        res.push_back(curr);
        q.pop();
        for (int i = 0; i < adj[curr].size(); i++)
        {
            int To = adj[curr][i];
            in_deg[To]--;
            if (in_deg[To] == 0)
                q.push(To);
        }
    }
}

void Kahn_algo(v adj[])
{
    for (int i = 0; i < n; i++)
        if (in_deg[i] == 0)
            q.push(i);
    BFS(adj, q.front());
}

int main()
{
    freopen("./input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);
    int a, b;
    cin >> n >> m;
    v adj[n];
    for (int i = 0; i < n; i++)
        in_deg.push_back(0);
    for (int i = 0; i < m; i++)
    {
        cin >> a >> b;
        adj[a].push_back(b);
        in_deg[b]++;
    }
    Kahn_algo(adj);
    for (int i = 0; i < res.size(); i++)
        cout << res[i] << " ";

    return 0;
}
/*
INPUT :
5
6
1 0
2 1
2 4
4 1
3 0
3 1

OUTPUT:
2 3 4 1 0
*/

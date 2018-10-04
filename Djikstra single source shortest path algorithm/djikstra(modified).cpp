#include<bits/stdc++.h>
using namespace std;
void djikstra(vector < pair<int,int> > adj[],int dist[],bool vis[],int v,int s)
{
    dist[s]=0;
    multiset < pair < int , int > > q;  //acts as priority queue
    q.insert(make_pair(s,0));
    while(!q.empty())
    {
        pair<int,int> p= *q.begin(); //vertex with minimum distance
        q.erase(q.begin());
        int x= p.second, wt=p.first;
        if(vis[x])
            continue;
        vis[x]=true;
        for(int i=0;i<adj[x].size();i++)
        {
            int e = adj[x][i].first;
            int w= adj[x][i].second;
            if(dist[x]+w<dist[e])
            {
                dist[e]=dist[x]+w;
                q.insert({dist[e],e});
            }
        }

    }

}
int main()
{
    int v,e,w,v1,v2;
    cin>>v>>e;
    vector < pair<int,int> > adj[v+1];
    for(int i=0;i<e;i++)
        {
            cin>>v1>>v2>>w;
            adj[v1].push_back(make_pair(v2,w));
            adj[v2].push_back(make_pair(v1,w));
        }
    int dist[v+1];
    for(int i=0;i<v;i++)
        dist[i]=INT_MAX;
    bool vis[v+1];
    memset(vis,false,sizeof vis);
    int s,d;
    cin>>s>>d;
    djikstra(adj,dist,vis,v,s);
    for(int i=0;i<v;i++)
    {
        cout<<"Distance of "<<i<<" From source "<<s<<" is "<<dist[i]<<endl;
    }
}

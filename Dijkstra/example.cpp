#include<bits/stdc++.h>
#include<cstdio>
#include<cstdlib>
#include<string>
#define  ll long long int
#define loop(i,n) for(i=0;i<n;i++)
#define loop1(i,s,e) for(ll i=s;i<=e;i++)
#define io std::ios::sync_with_stdio(false);cin.tie(NULL);
#define mod 1000000007
#define rep(i,c) for(typeof(c.begin())i=c.begin();i!=c.end();++i)
#define pb push_back
#define pii pair<ll,ll>
using namespace std;
#define MAX 109
#define INF 1000000000000000
ll dis[MAX];
bool visit[MAX];
vector<pii> edge[MAX];
void dijkstra(ll src,ll dest)
{
    priority_queue<pii,vector<pii>,greater<pii> > pq;
    while(!pq.empty())
        pq.pop();
    pq.push({0,src});
    dis[src]=0;
    while(!pq.empty())
    {
        ll w=pq.top().first;
        ll u=pq.top().second;
        pq.pop();
        if(!visit[u])
        {
            visit[u]=1;
            if(dis[u]<w)
            continue;
            rep(i,edge[u])
            {
                ll v=(*i).first;
                ll wt=(*i).second;
                if(visit[v])
                    continue;
                if(dis[v]>dis[u]+wt)
                {
                    dis[v]=dis[u]+wt;
                    pq.push({dis[v],v});
                }
            }
        }
    }
}
int main()
{
    io
    ll n,m,lim,a,b,c,i,s,temp,dest;
    cin>>n>>dest>>lim>>m;
    loop1(i,1,m)
    {
        cin>>a>>b>>c;
        edge[b].pb({a,c});
    }
    loop(i,MAX)
    {
     dis[i]=INF;
     visit[i]=false;
    }
    dijkstra(dest,n);
    int count=0;
    for(i=1;i<=n;i++)
    {
        if(dis[i]<=lim)
            count++;
    }
    cout<<count<<endl;
    return 0;
}

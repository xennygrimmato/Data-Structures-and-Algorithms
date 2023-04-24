#include<bits/stdc++.h>
using namespace std;
class graph
{
    int v,adj[100][100];
public:
     void read()
        {
            int i,j;

            cout<<"vertex"<<endl;
            cin>>v;
            for(i=0;i<v;i++)
            {
                for(j=0;j<v;j++)
                {
                    cin>>adj[i][j];

                }
            }
        }
    void djikstra(int src)
    {
        int vis[v],p[v],d[v],i,j,min,u;
        for(i=0;i<v;i++)
        {
            vis[i]=0;
            p[i]=src;
            d[i]=adj[src][i];
        }
        vis[src]=1;
        for(i=0;i<v;i++)
        {
            min=999;
            u=-1;
            for(j=0;j<v;j++)
            {
                if(d[j]<min&&vis[j]==0)
                {
                    min=d[j];
                    u=j;
                }
            }
            vis[u]=1;
            for(int k=0;k<v;k++)
            {
                if(vis[k]==0&&(adj[u][k]+d[u]<d[k]))
                {
                    d[k]=adj[u][k]+d[u];
                    p[k]=u;
                }
            }

        }
         for(i=0;i<v;i++)
         {
             cout<<"Shortest path from "<<src<<" to "<<i<<" ";
             if(i==src)
                continue;
             int k=i;
             cout<<k<<"-- ";
             while(p[k]!=src)
             {  cout<<p[k]<<"---";
                 k=p[k];
             }
             cout<<src<<endl;
             cout<<"Cost is "<<d[i]<<endl;
         }
    }

};
int main()
{
    int src;

    graph g;
    g.read();
    cout<<"Source"<<endl;
    cin>>src;
    g.djikstra(src);
}

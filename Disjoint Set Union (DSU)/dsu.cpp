
ll p[100004];
ll size[100005];
ll find(ll x)
{
    return (p[x]==x?(x):(x=find(p[x])));
}
void  unite(ll x,ll y)
{
    ll xx = find(x);ll yy =find(y);
    if(xx==yy)return;
    if(size[xx]>size[yy])swap(xx,yy);
    size[p[yy]]+=size[p[xx]];
    size[p[xx]]=0;
    p[xx]=p[yy];
    
}
Mistakes I made -> forgot to swap if size of xx is greater, forgot to return if in unite both elements parents are already same.

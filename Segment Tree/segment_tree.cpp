#include <iostream>
#include <algorithm>
#include <cmath>
#include <climits>
using namespace std;

typedef long long LL;

#define MAXN 100000
#define INF INT_MAX
#define NEG_INF INT_MIN

int a[MAXN+1]; // a has 0-indexed elements

struct node
{
    int start, end, sum_val, max_val, min_val;
};


/*
 * Segment Tree Class
 * Functions:
	 * # Range minimum query
	 * # Range maximum query
	 * # Range sum query
	 * # Range update
 */

class segtree
{
    node tree[4*MAXN+1]; // tree is has 1-indexed nodes
    int N;
    public:
    segtree(int *a, int sz)
    {
        N=sz;
        build(1,0,N-1,a); // build(node_no, begin, end, array)
    }
    
    void build(int node, int begin, int end, int *a)
    {
        if(begin == end)
        {
            tree[node].min_val = a[begin];
            tree[node].max_val = a[begin];
            tree[node].sum_val = a[begin];
        }
        else
        {
            int mid = floor((begin+end)/2);
            int lc = 2*node;
            int rc = 2*node + 1;
            build(lc, begin, mid, a);
            build(rc, mid+1, end, a);
            tree[node].min_val = min(tree[lc].min_val, tree[rc].min_val);
            tree[node].max_val = max(tree[lc].max_val, tree[rc].max_val);
            tree[node].sum_val = tree[lc].sum_val + tree[rc].sum_val;
        }
        tree[node].start = begin;
        tree[node].end = end;
    }
    
    int QMin(int node, int t_begin, int t_end, int a_begin, int a_end)
    {
        if(t_begin >= a_begin && t_end <= a_end)
        {
            return tree[node].min_val;
        }
        else
        {
            int mid = floor((t_begin + t_end)/2);
            int result = INF; // setting result to INF
            int lc = 2*node;
            int rc = 2*node+1;
            if(mid >= a_begin && t_begin <= a_end)
            {
                result = min(result, QMin(lc, t_begin, mid, a_begin, a_end));
            }
            if(t_end >= a_begin && ((mid+1) <= a_end))
            {
                result = min(result, QMin(rc, mid+1, t_end, a_begin, a_end));
            }
            return result;
        }
    }
    
    int query_min(int x, int y) // x and y are 1-indexed
    {
        x--,y--;
        return QMin(1,0,N-1,x,y);
    }
    
    
    int QMax(int node, int t_begin, int t_end, int a_begin, int a_end)
    {
        if(t_begin >= a_begin && t_end <= a_end)
        {
            return tree[node].max_val;
        }
        else
        {
            int mid = floor((t_begin + t_end)/2);
            int result = NEG_INF; // setting result to -INF
            int lc = 2*node;
            int rc = 2*node+1;
            if(mid >= a_begin && t_begin <= a_end)
            {
                result = max(result, QMax(lc, t_begin, mid, a_begin, a_end));
            }
            if(t_end >= a_begin && ((mid+1) <= a_end))
            {
                result = max(result, QMax(rc, mid+1, t_end, a_begin, a_end));
            }
            return result;
        }
    }
    
    int query_max(int x, int y) // x and y are 1-indexed
    {
        x--,y--;
        return QMax(1,0,N-1,x,y);
    }
    
    int QSum(int node, int t_begin, int t_end, int a_begin, int a_end)
    {
        if(t_begin >= a_begin && t_end <= a_end)
        {
            return tree[node].sum_val;
        }
        else
        {
            int mid = floor((t_begin + t_end)/2);
            int left=0;
            int right=0;
            int result=0;
            int lc = 2*node;
            int rc = 2*node+1;
            if(mid >= a_begin && t_begin <= a_end)
            {
                left = QSum(lc, t_begin, mid, a_begin, a_end);
            }
            if(t_end >= a_begin && ((mid+1) <= a_end))
            {
                right = QSum(rc, mid+1, t_end, a_begin, a_end);
            }
            result = left + right;
            return result;
        }
    }
    
    int query_sum(int x, int y) // x and y are 1-indexed
    {
        x--,y--;
        return QSum(1,0,N-1,x,y);
    }
    
    void QUpd(int node, int begin, int end, int pos, int val)
    {
        if(begin == end)
        {
            tree[node].min_val = val;
            tree[node].max_val = val;
            tree[node].sum_val = val;
        }
        else
        {
            int mid = floor((begin+end)/2);
            int lc, rc;
            lc = 2*node;
            rc = 2*node + 1;
            if(pos <= mid)
            {
                QUpd(lc,begin,mid,pos,val);
            }
            else
            {
                QUpd(rc,mid+1,end,pos,val);
            }
            tree[node].min_val = min(tree[lc].min_val, tree[rc].min_val);
            tree[node].max_val = max(tree[lc].max_val, tree[rc].max_val);
            tree[node].sum_val = tree[lc].sum_val + tree[rc].sum_val;
        }
    }
    
    void update(int pos, int val)
    {
        pos--;
        QUpd(1,0,N-1,pos,val);
    }
    
    
    void display_tree()
    {
        for(int i=0;i<=10;i++) cout<<tree[i].max_val<<" ";
    }
};

int main()
{
    int a[]={1,2,3,4};
    segtree s(a,4); // Create segment tree for 0-indexed array "a", for the first 4 elements.
    //s.display_tree();
    cout<<s.query_min(1,4)<<"\n";
    cout<<s.query_min(2,3)<<"\n";
    cout<<s.query_max(1,4)<<"\n";
    cout<<s.query_max(2,3)<<"\n";
    cout<<s.query_sum(1,4)<<"\n";
    cout<<s.query_sum(2,3)<<"\n";
    s.update(4,5);
    cout<<s.query_max(1,4)<<"\n";
    cout<<s.query_sum(1,4)<<"\n";
    cout<<s.query_sum(1,3)<<"\n";
    
    /*
     * To allocate memory for the segment tree on the HEAP:
     * segtree *s = new segtree(a, 4);
     * s->query_min(1,4);
     */
}

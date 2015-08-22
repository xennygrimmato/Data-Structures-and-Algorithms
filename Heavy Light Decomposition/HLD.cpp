#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define sz size
#define all(X) (X).begin(), (X).end ()
#define for_each(it, X) for (__typeof((X).begin()) it = (X).begin(); it != (X).end(); it++)


typedef long long int lld;
typedef pair < int, int > pii;

const int MaxN = 1 << 20;

int N, M, Level[MaxN], Parent[MaxN], Size[MaxN], Chain[MaxN];
vector < int > E[MaxN];
void DFS ( int Curr, int Prev )
{
    Parent[Curr] = Prev;
    Size[Curr] = 1;

    for_each ( it, E[Curr] ) 
    if ( * it != Prev )
    Level[* it] = Level[Curr] + 1, DFS ( * it, Curr ), Size[Curr] += Size[* it];
    /* So basically for each of the element in their we need to have 
       level   which tells your dist from root
       size    which is the number of your children
       parent  which is the index of your dad which is unique obviously
    */
}
/*The Hld function is initialized from the root and for every node connected to it 
  their onwards we need to check that we don't make hld from where we came 
  so basically i have a few children one of which is my special children i keep recursively
  looking for my special children and color them with my own color  but what about 
  my other children i give them another children and tell them to start a new family themselves
  this is all that i do only after i take care of all my special children*/
void HLD ( int Curr, int Prev, int Color )
{
    Chain[Curr] = Color;

    int idx = -1;
    for_each ( it, E[Curr] ) 
    if ( * it != Prev && ( idx == -1 || Size[* it] > Size[idx] ) ) 
    idx = * it;
    

    if ( idx != -1 ) HLD ( idx, Curr, Color );
    for_each ( it, E[Curr] ) if ( * it != Prev && * it != idx ) HLD ( * it, Curr, * it );
}
/*
  This is a simple function to find lca it works in O(n) and its not really cool
  but its their, however their is an improvised version of this thing called 
  Logarithmic LCA which can be learnt later 
*/
inline int LCA ( int idx, int idy )
{
    while ( Chain[idx] != Chain[idy] )
    if ( Level[Chain[idx]] < Level[Chain[idy]] ) idy = Parent[Chain[idy]];
                                            else idx = Parent[Chain[idx]];
    
    return Level[idx] < Level[idy] ? idx : idy;
}

int main ( void )
{
    

    cin >> N >> M;         /*Scan the vertices and queries for the tree */
    for ( int i = 0; i < N - 1; i++ )
    {
        int idx, idy;
        cin >> idx >> idy;
        idx--;
        idy--;

        E[idx].pb ( idy );
        E[idy].pb ( idx );   /*connect the edges*/
    }

    DFS ( 0, -1 );
    HLD ( 0, -1, 0 );

    for ( int i = 0; i < M; i++ )
    {
        int idx, idy;
        cin >> idx >> idy;
        idx--;
        idy--;

        cout << LCA ( idx, idy ) + 1 << endl;
    }

    return 0;
}
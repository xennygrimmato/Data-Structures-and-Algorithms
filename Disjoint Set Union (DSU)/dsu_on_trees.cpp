// CPP code to find maximum subtree such 
// that all nodes are even in weight 
#include<bits/stdc++.h> 

using namespace std; 

#define N 100010 

// Structure for Edge 
struct Edge 
{ 
	int u, v; 
}; 

/* 
	'id': stores parent of a node. 
	'sz': stores size of a DSU tree. 
*/
int id[N], sz[N]; 

// Function to assign root 
int Root(int idx) 
{ 
	int i = idx; 
	
	while(i != id[i]) 
		id[i] = id[id[i]], i = id[i]; 
	
	return i; 
} 

// Function to find Union 
void Union(int a, int b) 
{ 
	int i = Root(a), j = Root(b); 
	
	if (i != j) 
	{ 
		if(sz[i] >= sz[j]) 
		{ 
			id[j] = i, sz[i] += sz[j]; 
			sz[j] = 0; 
		} 
		else
		{ 
			id[i] = j, sz[j] += sz[i]; 
			sz[i] = 0; 
		} 
	} 
} 

// Utility function for Union 
void UnionUtil(struct Edge e[], int W[], int q) 
{ 

	for(int i = 0; i < q; i++) 
	{ 
		// Edge between 'u' and 'v' 
		int u, v; 
		u = e[i].u, v = e[i].v; 

		// 0-indexed nodes 
		u--, v--; 

		// If weights of both 'u' and 'v' 
		// are even then we make union of them. 
		if(W[u] % 2 == 0 && W[v] % 2 == 0) 
					Union(u,v); 
	} 
} 

// Function to find maximum 
// size of DSU tree 
int findMax(int n, int W[]) 
{ 
	int maxi = 0; 
	for(int i = 1; i <= n; i++) 
		if(W[i] % 2 == 0) 
			maxi = max(maxi, sz[i]); 
			
	return maxi; 
} 

// Driver code 
int main() 
{ 
	/* 
		Nodes are 0-indexed in this code 
		So we have to make necessary changes 
		while taking inputs 
	*/

	// Weights of nodes 
	int W[] = {1, 2, 6, 4, 2, 0, 3}; 

	// Number of nodes in a tree 
	int n = sizeof(W) / sizeof(W[0]); 

	// Initializing every node as 
	// a tree with single node. 
	for(int i = 0; i < n; i++) 
			id[i] = i, sz[i] = 1; 

	Edge e[] = {{1, 2}, {1, 3}, {2, 4}, 
				{2, 5}, {4, 6}, {6, 7}}; 

	int q = sizeof(e) / sizeof(e[0]); 

	UnionUtil(e, W, q); 

	// Find maximum size of DSU tree. 
	int maxi = findMax(n, W); 

	printf("Maximum size of the subtree with "); 
	printf("even weighted nodes = %d\n", maxi); 
	
	return 0; 
} 

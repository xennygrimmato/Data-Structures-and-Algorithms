#include <iostream>
#include <limits.h>

// Define Number of vertices in the graph
const int V = 7

using namespace std;
// function to find the vertex with minimum distance value, from the set of vertices not yet included in shortest path tree
int minDistance(int dist[], bool sptSet[])
{
    int min = INT_MAX, min_index;
    for (int v = 0; v < V; v++)
    {
	     if (sptSet[v] == false && dist[v] <= min){
            min = dist[v], min_index = v;}
    }
    return min_index;
}

// A utility function to print the constructed distance array
int printSolution(int dist[])
{
    cout<<"Vertex \t\t Distance from Source\n";
    for (int i = 0; i < V; i++)
    {
	 cout<<i<<" \t\t "<<dist[i]<<"\n";
    }
}
// Function that implements Dijkstra's single source shortest path algorithm which takes in two parameter one the graph and other the source vertix
void dijkstra(int graph[V][V], int src)
{
    int dist[V];  
    bool sptSet[V];
    for (int i = 0; i < V; i++)
    {
    	dist[i] = INT_MAX, sptSet[i] = false;
    }
    dist[src] = 0;
    for (int count = 0; count < V - 1; count++)
    {
        int u = minDistance(dist, sptSet);
        sptSet[u] = true;
        for (int v = 0; v < V; v++)
        {
		if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX
                && dist[u] + graph[u][v] < dist[v])
                dist[v] = dist[u] + graph[u][v];
	}
    }
    printSolution(dist);
}

int main()
{
    int src;
    int graph[V][V] = { { 0, 3, 0, 4, 0, 0, 4},
                        { 4, 0, 8, 0, 0, 0, 0},
                        { 0, 8, 0, 7, 0, 4, 0},
                        { 0, 0, 7, 0, 9, 14, 0},
                        { 0, 0, 0, 9, 0, 10, 0},
                        { 0, 0, 4, 14, 10, 0,2},
                        { 0, 0, 0, 0, 0, 2, 0}
		       };
    //pass the adjacency matrix and source vertex
    dijkstra(graph, 0);
    return 0;
}

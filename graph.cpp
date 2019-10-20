/*
 * C++ Program to Implement Graph Structured Stack
 */
#include <iostream>
#include <cstdlib>
#include <stack>
#include <list>
using namespace std;
 
/*
 * Class Graph Structured Stack
 */
class GraphStructuredStack
{
    private: 
        list< stack<int> > stackList;
        stack<int> mystack;
        int numberOfNodes;
        int **adjacencyMatrix;
        int *parent;
    public:
        GraphStructuredStack(int numberOfNodes)
        {
            this->numberOfNodes = numberOfNodes;
            adjacencyMatrix = new int* [numberOfNodes + 1];
            this->parent = new int [numberOfNodes + 1];
            for (int i = 0; i < numberOfNodes + 1; i++)
                adjacencyMatrix[i] = new int [numberOfNodes + 1];
        }
        /*
         * Implement Graph Structured Stack
         */        
        void graphStructuredStack(int **adjacencyMatrix, int source,int bottomNode)
        {
            bool stackFound = false;
            for (int sourceVertex = 1; sourceVertex <= numberOfNodes; sourceVertex++)
            {
                for (int destinationVertex = 1; destinationVertex <= numberOfNodes; destinationVertex++)
                {
                    this->adjacencyMatrix[sourceVertex][destinationVertex] 
                          = adjacencyMatrix[sourceVertex][destinationVertex];
                }
            }
 
            mystack.push(source);
            int element, destination;
            while (!mystack.empty())
            {
                element = mystack.top();
                destination = 1;
                while (destination <= numberOfNodes)
                {
                    if (this->adjacencyMatrix[element][destination] == 1)
                    {
                        mystack.push(destination);
                        parent[destination] = element;
                        this->adjacencyMatrix[element][destination] = 0;
                        if (destination == bottomNode)
                        {
                            stackFound = true;
                            break;
                        }
                        element = destination;
                        destination = 1;
                        continue;
                    }
                    destination++;
                }
                if (stackFound)
                {
                    stack<int> istack;
                    for (int node = bottomNode; node != source; node = parent[node])
                    {
                        istack.push(node);
                    }
                    istack.push(source);
                    stackList.push_back(istack);
                    stackFound = false;
                }
                mystack.pop();
            }
            list<stack<int> >::iterator iterator;
            iterator = stackList.begin();
            while (iterator != stackList.end())
            {
 
                stack <int> stack = *iterator;
                iterator++;
                while (!stack.empty())
                {
                    cout<<stack.top()<<"\t";
                    stack.pop();
                }
                cout<<endl;
            }
        }
};
/*
 * Main
 */
int main()
{
    int numberofnodes;
    cout<<"Enter number of nodes: ";
    cin>>numberofnodes;
    GraphStructuredStack gss(numberofnodes);
    int source, bottom;
    int **adjacencyMatrix;
    adjacencyMatrix = new int* [numberofnodes + 1];
    for (int i = 0; i < numberofnodes + 1; i++)
        adjacencyMatrix[i] = new int [numberofnodes + 1];
    cout<<"Enter the graph matrix: "<<endl;
    for (int sourceVertex = 1; sourceVertex <= numberofnodes; sourceVertex++)
    {
        for (int destinationVertex = 1; destinationVertex <= numberofnodes; destinationVertex++)
        {
            cin>>adjacencyMatrix[sourceVertex][destinationVertex];
        }
    }
    cout<<"Enter the source node: ";
    cin>>source;
    cout<<"Enter the bottom node: ";
    cin>>bottom;
    cout<<"The stacks are: "<<endl;
    gss.graphStructuredStack(adjacencyMatrix, source, bottom);
    return 0;
}
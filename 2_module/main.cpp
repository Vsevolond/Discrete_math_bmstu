#include <iostream>
#include <vector>
#include <queue>
using namespace std;

//vector<bool> used;

struct Edge {
    int from;
    int to;
};

class Graph
{
public:
    int numVertices;
    vector<vector<int>> adjLists;
    vector<Edge> edges;
    vector<bool> visited;
    Graph(int V);
    void addEdge(Edge edge);
    void DFS(int vertex);
    void BFS(int startVertex);
};

Graph::Graph(int vertices)
{
    numVertices = vertices;
    adjLists.resize(vertices);
    visited.resize(vertices);
}

void Graph::addEdge(Edge edge)
{
    edges.push_back(edge);
    adjLists[edge.from].push_back(edge.to);
    adjLists[edge.to].push_back(edge.from);
}

void Graph::DFS(int vertex)
{

    visited[vertex] = true;
    vector<int> adjList = adjLists[vertex];

    //cout << vertex << " ";

    vector<int>::iterator i;
    for(i = adjList.begin(); i != adjList.end(); ++i)
        if(!visited[*i])
            DFS(*i);
}

void Graph::BFS(int startVertex)
{
    visited.assign(numVertices, false);

    queue<int> queue;

    visited[startVertex] = true;
    queue.push(startVertex);

    vector<int>::iterator i;

    while(!queue.empty())
    {
        int currVertex = queue.front();
        //cout << "Visited " << currVertex << " ";
        queue.pop();

        for(i = adjLists[currVertex].begin(); i != adjLists[currVertex].end(); ++i)
        {
            int adjVertex = *i;
            if(!visited[adjVertex])
            {
                visited[adjVertex] = true;
                queue.push(adjVertex);
            }
        }
    }

}

int main()
{


    return 0;
}
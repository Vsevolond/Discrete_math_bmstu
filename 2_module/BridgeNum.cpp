#include <iostream>
#include <vector>
#include <algorithm>
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
    int numBridges;
    vector<vector<int>> adjLists;
    vector<Edge> edges;
    //vector<bool> visited;
    Graph(int V);
    void addEdge(Edge edge);
    void bridgeUtil(int u, bool visited[], int disc[], int low[], int parent[]);
    void bridge();
    //void DFS(int vertex);
    //void BFS(int startVertex);
};

Graph::Graph(int vertices)
{
    numBridges = 0;
    numVertices = vertices;
    adjLists.resize(vertices);
}

void Graph::addEdge(Edge edge)
{
    edges.push_back(edge);
    adjLists[edge.from].push_back(edge.to);
    adjLists[edge.to].push_back(edge.from);
}

void Graph::bridgeUtil(int u, bool visited[], int disc[], int low[], int parent[])
{
    static int time = 0;
    visited[u] = true;
    disc[u] = low[u] = ++time;

    vector<int>::iterator i;

    for (i = adjLists[u].begin(); i != adjLists[u].end(); ++i) {
        int v = *i;

        if (!visited[v]) {
            parent[v] = u;
            bridgeUtil(v, visited, disc, low, parent);
            low[u] = min(low[u], low[v]);

            if (low[v] > disc[u]) {
                numBridges++;
                //cout << u << " " << v << endl;
            }

        } else if (v != parent[u]) {
            low[u] = min(low[u], disc[v]);
        }
    }

}

void Graph::bridge() {
    bool visited[numVertices];
    int disc[numVertices];
    int low[numVertices];
    int parent[numVertices];

    for (int i = 0; i < numVertices; i++) {
        parent[i] = -1;
        visited[i] = false;
    }

    for (int i = 0; i < numVertices; i++) {
        if (!visited[i]) {
            bridgeUtil(i, visited, disc, low, parent);
        }
    }
}



/*void Graph::DFS(int vertex)
{

    visited[vertex] = true;
    vector<int> adjList = adjLists[vertex];

    //cout << vertex << " ";

    vector<int>::iterator i;
    for(i = adjList.begin(); i != adjList.end(); ++i)
        if(!visited[*i])
            DFS(*i);
}*/

/*void Graph::BFS(int startVertex)
{
    visited = new bool[numVertices];
    for(int i = 0; i < numVertices; i++)
        visited[i] = false;

    vector<int> queue;

    visited[startVertex] = true;
    queue.push_back(startVertex);

    vector<int>::iterator i;

    while(!queue.empty())
    {
        int currVertex = queue.front();
        //cout << "Visited " << currVertex << " ";
        queue.pop_back();

        for(i = adjLists[currVertex].begin(); i != adjLists[currVertex].end(); ++i)
        {
            int adjVertex = *i;
            if(!visited[adjVertex])
            {
                visited[adjVertex] = true;
                queue.push_back(adjVertex);
            }
        }
    }

}*/

int main()
{
    int n, k;
    cin >> n >> k;
    Graph graph(n);
    for (int i = 0; i < k; i++) {
        Edge edge;
        cin >> edge.from >> edge.to;
        graph.addEdge(edge);
    }
    graph.bridge();
    cout << graph.numBridges << endl;
    return 0;
}

/*
10
12
0 1
0 2
1 2
2 3
3 4
3 5
3 6
3 7
4 5
5 9
6 7
7 8
*/

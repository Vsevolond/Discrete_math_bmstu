#include <iostream>
#include <vector>

using namespace std;

vector<bool> used;

struct EdgeNode {
    vector<bool> nodes;
    int firstNode;
    int cntNodes;
    int cntEdges;
};

struct Edge {
    int from;
    int to;
};

class Graph
{

public:
    Graph(int V);

    int numVertices;
    vector<vector<int>> adjLists;
    vector<Edge> edges;
    vector<bool> visited;

    void addEdge(Edge edge);
    //void DFS(int vertex);
    EdgeNode BFS(int startVertex);
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

/*void Graph::DFS(int vertex)
{

    visited[vertex] = true;
    list<int> adjList = adjLists[vertex];

    cout << vertex << " ";

    list<int>::iterator i;
    for(i = adjList.begin(); i != adjList.end(); ++i)
        if(!visited[*i])
            DFS(*i);
}*/

EdgeNode Graph::BFS(int startVertex)
{
    int cntNodes = 1, cntEdges = 0;

    visited.assign(numVertices, false);

    vector<int> queue;

    visited[startVertex] = true;
    used[startVertex] = true;
    queue.push_back(startVertex);

    vector<int>::iterator i;

    while(!queue.empty())
    {
        int currVertex = queue.back();
        //cout << "Visited " << currVertex << " " << endl;
        queue.pop_back();

        for(i = adjLists[currVertex].begin(); i != adjLists[currVertex].end(); ++i)
        {
            int adjVertex = *i;
            cntEdges++;
            if(!visited[adjVertex])
            {
                visited[adjVertex] = true;
                used[adjVertex] = true;
                cntNodes++;
                queue.push_back(adjVertex);
            }
        }
    }
    EdgeNode res;
    res.nodes = visited;
    res.firstNode = startVertex;
    res.cntNodes = cntNodes;
    res.cntEdges = cntEdges / 2;
    return res;
}

int main()
{
    int n, k;
    cin >> n >> k;
    used.resize(n, false);
    Graph graph(n);
    for (int i = 0; i < k; i++) {
        Edge edge;
        cin >> edge.from >> edge.to;
        graph.addEdge(edge);
    }

    int maxCntNodes = 0, maxCntEdges = 0, maxFirstNode = n;
    vector<bool> maxCompNodes;
    int i = 0;
    while (i < n) {
        if (!used[i]) {
            EdgeNode comp = graph.BFS(i);
            vector<bool> compNodes = comp.nodes;
            int firstNode = comp.firstNode;
            int cntEdges = comp.cntEdges;
            int cntNodes = comp.cntNodes;
            if (cntNodes > maxCntNodes) {
                maxCompNodes = compNodes;
                maxCntNodes = cntNodes;
                maxCntEdges = cntEdges;
                maxFirstNode = firstNode;
            } else if (cntNodes == maxCntNodes) {
                if (cntEdges > maxCntEdges) {
                    maxCompNodes = compNodes;
                    maxCntNodes = cntNodes;
                    maxCntEdges = cntEdges;
                    maxFirstNode = firstNode;
                } else if (cntEdges == maxCntEdges) {
                    if (firstNode < maxFirstNode) {
                        maxCompNodes = compNodes;
                        maxCntNodes = cntNodes;
                        maxCntEdges = cntEdges;
                        maxFirstNode = firstNode;
                    }
                }
            }
        }
        i++;
    }

    cout << "graph {" << endl;
    for (int i = 0; i < n; i++) {
        if (maxCompNodes[i]) {
            printf("    %d [color = red]\n", i);
        } else {
            printf("    %d\n", i);
        }
    }
    for (Edge edge : graph.edges) {
        if (maxCompNodes[edge.from] && maxCompNodes[edge.to]) {
            printf("    %d -- %d [color = red]\n", edge.from, edge.to);
        } else {
            printf("    %d -- %d\n", edge.from, edge.to);
        }
    }
    cout << "}" << endl;
    return 0;
}

/*
7
8
0 1
0 5
1 5
1 4
5 4
2 3
3 6
6 2
*/

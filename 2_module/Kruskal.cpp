#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <algorithm>
using namespace std;

//vector<bool> used;

struct Edge {
    int from, to;
    double len;
};

struct Node {
    int node, len;
};

bool comp(Edge a, Edge b) {
    return a.len < b.len;
}

class Graph
{
public:
    //int numVertices;
    int numEdges;
    //vector<vector<Node>> adjLists;
    vector<Edge> edges;
    //vector<bool> visited;
    vector<int> parent;
    Graph(int V);
    void addEdge(Edge edge);
    int find_set(int i);
    void union_set(int u, int v);
    double kruskal();
    //void DFS(int vertex);
    //void BFS(int startVertex);
};

Graph::Graph(int vertices)
{
    //numVertices = vertices;
    numEdges = 0;
    parent.resize(vertices);
    for (int i = 0; i < vertices; i++) parent[i] = i;
    //adjLists.resize(vertices);
    //visited.resize(vertices);
}

void Graph::addEdge(Edge edge)
{
    edges.push_back(edge);
    numEdges++;
    /*Node newnode;
    newnode.node = edge.to;
    newnode.len = edge.len;
    adjLists[edge.from].push_back(newnode);
    newnode.node = edge.from;
    adjLists[edge.to].push_back(newnode);*/
}

int Graph::find_set(int i) {
    // If i is the parent of itself
    if (i == parent[i])
        return i;
    else
        // Else if i is not the parent of itself
        // Then i is not the representative of his set,
        // so we recursively call Find on its parent
        return find_set(parent[i]);
}

void Graph::union_set(int u, int v) {
    parent[u] = parent[v];
}

double Graph::kruskal() {
    int i, uRep, vRep;
    double len_way = 0;
    sort(edges.begin(), edges.end(), comp);
    for (i = 0; i < numEdges; i++) {
        uRep = find_set(edges[i].from);
        vRep = find_set(edges[i].to);
        if (uRep != vRep) {
            len_way += edges[i].len;
            union_set(uRep, vRep);
        }
    }
    return len_way;
}

/*void Graph::DFS(int vertex)
{

    visited[vertex] = true;
    vector<Node> adjList = adjLists[vertex];

    //cout << vertex << " ";

    vector<Node>::iterator i;
    for(i = adjList.begin(); i != adjList.end(); ++i)
        if(!visited[*i])
            DFS(*i);
}*/


/*void Graph::BFS(int startVertex)
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

}*/

struct Point {
    int x, y;
};

int main()
{
    int n;
    cin >> n;
    Graph graph(n);
    vector<Point> coord;
    for (int i = 0; i < n; i++) {
        Point p;
        cin >> p.x >> p.y;
        for (int j = 0; j < i; j++) {
            Edge edge = {i, j, sqrt((coord[j].x - p.x) * (coord[j].x - p.x) +
                         (coord[j].y - p.y) * (coord[j].y - p.y))};
            graph.addEdge(edge);
        }
        coord.push_back(p);
    }
     printf("%.2f\n", graph.kruskal());

    return 0;
}
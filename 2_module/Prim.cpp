#include <iostream>
#include <vector>
#include <climits>
//#include <queue>
using namespace std;

//vector<bool> used;

struct Edge {
    int from, to, len;
};

struct Node {
    int node, len;
};

class Graph
{
public:
    int numVertices;
    vector<vector<Node>> adjLists;
    vector<Edge> edges;
    vector<bool> visited;
    Graph(int V);
    void addEdge(Edge edge);
    int prim();
    //void DFS(int vertex);
    //void BFS(int startVertex);
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
    Node newnode;
    newnode.node = edge.to;
    newnode.len = edge.len;
    adjLists[edge.from].push_back(newnode);
    newnode.node = edge.from;
    adjLists[edge.to].push_back(newnode);
}

int Graph::prim() {
    int no_edge;
    vector<bool> selected(numVertices, false);
    no_edge = 0;
    selected[0] = true;

    int x, y, sumlen = 0;

    while (no_edge < numVertices - 1) {

        int min = INT_MAX;
        y = 0;

        for (int i = 0; i < numVertices; i++) {
            if (selected[i]) {
                vector<Node>::iterator j;
                for (j = adjLists[i].begin(); j != adjLists[i].end(); j++) {
                    Node adjnode = *j;
                    if (!selected[adjnode.node]) {
                        if (min > adjnode.len) {
                            min = adjnode.len;
                            y = adjnode.node;
                        }

                    }
                }
            }
        }

        sumlen += min;
        selected[y] = true;
        no_edge++;
    }

    return sumlen;
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

}*/

int main()
{
    int n, m;
    cin >> n >> m;
    Graph graph(n);
    for (int i = 0; i < m; i++) {
        Edge edge;
        cin >> edge.from >> edge.to >> edge.len;
        graph.addEdge(edge);
    }

    cout << graph.prim() << endl;

    return 0;
}
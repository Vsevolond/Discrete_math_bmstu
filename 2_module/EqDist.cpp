#include <iostream>
#include <vector>
#include <queue>
//#include <fstream>
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
    //void DFS(int vertex);
    vector<int> BFS(int startVertex);
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

//const long long INF = (long long) 1e18 + 1;


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

vector<int> Graph::BFS(int startVertex)
{
    visited.assign(numVertices, false);

    queue<int> queue;
    vector<int> dist(numVertices, numVertices);
    dist[startVertex] = 0;

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
            if (dist[adjVertex] > dist[currVertex] + 1) {
                dist[adjVertex] = dist[currVertex] + 1;
                queue.push(adjVertex);
            }
        }
    }
    //cout << endl;
    return dist;
}

/*template<typename T>
void print(vector<T> arr) {
    int n = arr.size();
    for (int i = 0; i < n; i++) cout << arr[i] << ' ';
    cout << endl;
}*/

int main()
{
    //ifstream in("/Users/vsevolod/Downloads/input.txt");
    int n, m;
    cin >> n >> m;
    Graph graph(n);
    for (int i = 0; i < m; i++) {
        Edge edge;
        cin >> edge.from >> edge.to;
        graph.addEdge(edge);
    }

    int k;
    cin >> k;
    vector<bool> is_sup(n, false);
    int sup[k];
    for (int i = 0; i < k; i++) {
        cin >> sup[i];
        is_sup[sup[i]] = true;
    }

    vector<int> dist0 = graph.BFS(sup[0]);
    vector<int> dist;
    vector<bool> eqnodes(n, true);
    bool eqnode_exist = false;
    for (int i = 1; i < k; i++) {
        dist = graph.BFS(sup[i]);
        for (int j = 0; j < n; j++) {
            eqnodes[j] = eqnodes[j] && (!is_sup[j] && dist[j] != n && dist[j] == dist0[j]);
            if (i == k - 1 && eqnodes[j]) {
                eqnode_exist = true;
                cout << j << ' ';
            }
        }
        //print(dist[i]);
    }
    if (!eqnode_exist) cout << '-' << endl;
    else cout << endl;

    return 0;
}

/*
10
10
3 8
0 4
3 7
0 3
5 1
0 2
3 6
5 9
4 1
3 5
2
5 7
*/

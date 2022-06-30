#include <iostream>
#include <vector>
#include <climits>
//#include <fstream>
#include <queue>

using namespace std;


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
    //vector<bool> visited;
    Graph(int V);
    void addEdge(Edge edge);
    int minpath(int st);
};

Graph::Graph(int vertices)
{
    numVertices = vertices;
    adjLists.resize(vertices);
    //visited.resize(vertices);
}

void Graph::addEdge(Edge edge)
{
    edges.push_back(edge);
    Node newnode;
    newnode.node = edge.to;
    newnode.len = edge.len;
    adjLists[edge.from].push_back(newnode);
}



int Graph::minpath(int st) {
    vector<int> dist(numVertices, INT_MAX);
    dist[st] = 0;
    priority_queue<pair<int, int>> q;
    q.push(make_pair(dist[st], st));

    while (!q.empty()) {
        int v = q.top().second, cur_d = -q.top().first;
        q.pop();
        if (cur_d > dist[v]) continue;

        vector<Node>::iterator j;
        for (j = adjLists[v].begin(); j != adjLists[v].end(); ++j) {
            int to = (*j).node,
                    len = (*j).len;
            if (dist[v] + len < dist[to]) {
                dist[to] = dist[v] + len;
                q.push(make_pair(-dist[to], to));
            }
        }
    }
    return dist[numVertices - 1];

}

/*template<typename T>
void print(vector<vector<T>> arr) {
    int n = arr.size();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << arr[i][j] << ' ';
        }
        cout << endl;
    }
}*/

struct Coord {
    int x, y;
};

int main()
{
    //ifstream in("/Users/vsevolod/Downloads/input-4.txt");
    int n;
    cin >> n;
    int weights[n][n];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) cin >> weights[i][j];
    }
    Graph graph(n * n);
    Coord shifts[4] = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int adjnode = i * n + j;
            for (Coord shift : shifts) {
                Coord neighcoord = {i + shift.x, j + shift.y};
                if (neighcoord.x >= 0 && neighcoord.y >= 0 && neighcoord.x < n && neighcoord.y < n) {
                    int neighnode = neighcoord.x * n + neighcoord.y;
                    Edge edge = {adjnode, neighnode, weights[neighcoord.x][neighcoord.y]};
                    graph.addEdge(edge);
                }
            }
        }
    }

    //print(graph);

    cout << weights[0][0] + graph.minpath(0) << endl;

    return 0;
}
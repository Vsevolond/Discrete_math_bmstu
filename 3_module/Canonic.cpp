#include <iostream>
#include <vector>
#include <stack>
//#include <fstream>

using namespace std;

//vector<bool> used;
vector<int> num;
vector<int> parent;

struct Edge {
    int from, to;
};

class Graph
{
public:
    int numVertices;
    vector<vector<int>> adjLists;
    vector<Edge> edges;
    vector<bool> visited;
    Graph(int vertices);
    void addEdge(Edge edge);
    void DFS(int start);
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
}


void Graph::DFS(int start)
{
    int cnt = 0;
    stack<int> stack;
    stack.push(start);

    while (!stack.empty()) {
        int cur = stack.top();
        stack.pop();
        vector<int> adjList = adjLists[cur];

        if (!visited[cur]) {
            visited[cur] = true;
            num[cnt] = cur;
            parent[cur] = cnt;
            cnt++;

            for (auto i = adjList.rbegin(); i != adjList.rend(); ++i) {
                if (!visited[*i]) {
                    stack.push(*i);
                }
            }
        }
    }
}


/*template<typename T>
void print(vector<T> arr) {
    int n = arr.size();
    for (int i = 0; i < n; i++) cout << arr[i] << ' ';
    cout << endl;
}

template<typename T>
void print(unordered_set<T> arr) {
    unordered_set<int>::iterator i;
    for (i = arr.begin(); i != arr.end(); i++) cout << *i << ' ';
    cout << endl;
}*/

int main() {
    //ifstream in("/Users/vsevolod/Downloads/input.txt");
    //ofstream out("/Users/vsevolod/Downloads/out.txt");

    int n, m, q;
    cin >> n >> m >> q;
    int trans[n][m];
    vector<vector<string>> cond(n, vector<string>(m));
    Graph graph(n);
    num.resize(n);
    parent.resize(n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> trans[i][j];
            if (i == trans[i][j]) continue;
            Edge edge = {i, trans[i][j]};
            graph.addEdge(edge);
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> cond[i][j];
        }
    }


    /*if (q == 0) {

        printf("%d\n%d\n%d\n", n, m, 0);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                cout << trans[i][j] << ' ';
            }
            cout << endl;
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                cout << cond[i][j] << ' ';
            }
            cout << endl;
        }

    } else {*/

        graph.DFS(q);
        //print(num);
        //print(parent);
        //for (int i = 0; i < n; i++) print(graph.adjLists[i]);

        printf("%d\n%d\n%d\n", n, m, 0);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (j == m - 1) {
                    cout << parent[trans[num[i]][j]] << endl;
                } else {
                    cout << parent[trans[num[i]][j]] << ' ';
                }
            }
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (j == m - 1) {
                    cout << cond[num[i]][j] << endl;
                } else {
                    cout << cond[num[i]][j] << ' ';
                }
            }
        }
    //}

    return 0;
}
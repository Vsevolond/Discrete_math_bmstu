#include <iostream>
#include <vector>
//#include <fstream>

using namespace std;

int main() {
    //ifstream in("/Users/vsevolod/Downloads/input.txt");
    //ofstream out("/Users/vsevolod/Downloads/out.txt");

    char alph[] = "abcdefghijklmnopqrstuvwxyz";
    int n, m, q;
    cin >> n >> m >> q;
    int trans[n][m];
    vector<vector<string>> cond(n, vector<string>(m));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) cin >> trans[i][j];
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) cin >> cond[i][j];
    }

    cout << "digraph {" << endl;
    cout << "    rankdir = LR" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << "    " << i << " -> " << trans[i][j] << " [label = \"" <<
            alph[j] << "(" << cond[i][j] << ")\"]" << endl;
        }
    }
    cout << "}" << endl;

    return 0;
}
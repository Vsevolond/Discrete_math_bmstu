#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool cond(long long u, long long v, vector<long long> dividers){
    bool f = false;
    for (long long w : dividers) {
        if (w != u && w != v) {
            f = f || (u % w == 0 && w % v == 0);
        }
    }
    return (!f && u % v == 0);
}

int main() {
    long long num;
    cin >> num;
    vector<long long> dividers;
    long long div = 1;
    while (div * div <= num) {
        if (num % div == 0) {
            dividers.push_back(div);
            if (div * div != num) {
                dividers.push_back(num / div);
            }
        }
        div++;
    }
    sort(dividers.begin(), dividers.end(), greater<long long>());
    int n = dividers.size();
    cout << "graph {" << endl;
    for (long long x : dividers) {
        printf("\t%lld\n", x);
    }
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (cond(dividers[i], dividers[j], dividers)) {
                printf("\t%lld--%lld\n", dividers[i], dividers[j]);
            }
        }
    }
    cout << "}" << endl;
    return 0;
}

#include <iostream>
using namespace std;

int n, m = 0, d[10000], c[10000], ts[10000];
int vs[100], t[100];

void Kruskal() {
    for (int i = 1; i <= m - 1; i++) {
        for (int j = i + 1; j <= m; j++) {
            if (ts[i] > ts[j]) {
                int tg = ts[i];
                ts[i] = ts[j];
                ts[j] = tg;
                tg = d[i];
                d[i] = d[j];
                d[j] = tg;
                tg = c[i];
                c[i] = c[j];
                c[j] = tg;
            }
        }
    }

    int wt = 0, k = 0;
    for (int i = 1; i <= n; i++) vs[i] = 0;

    for (int i = 1; i <= m; i++) {
        if (!(vs[d[i]] != 0 && vs[d[i]] == vs[c[i]])) {
            k++;
            t[k] = i;
            wt = wt + ts[i];
            if (k == n - 1) {
                cout << "Wt = " << wt << endl;
                cout << "T = {";
                for (int j = 1; j <= k; j++) {
                    cout << "(" << d[t[j]] << "," << c[t[j]] << ")";
                    if (j != k) cout << ",";
                }
                cout << "}\n";
                return;
            }
            int u = d[i], v = c[i];
            if (vs[u] == 0 && vs[v] == 0) {
                vs[u] = k;
                vs[v] = k;
            }
            else if (vs[u] == 0 && vs[v] != 0) {
                vs[u] = vs[v];
            }
            else if (vs[u] != 0 && vs[v] == 0) {
                vs[v] = vs[u];
            }
            else if (vs[u] < vs[v]) {
                int tg = vs[v];
                for (int j = 1; j <= n; j++) {
                    if (vs[j] == tg) vs[j] = vs[u];
                }
            }
            else if (vs[v] < vs[u]) {
                int tg = vs[u];
                for (int j = 1; j <= n; j++) {
                    if (vs[j] == tg) vs[j] = vs[v];
                }
            }
        }
    }

}

int main() {
    cin >> n;

    int a[100][100];
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> a[i][j];
        }
    }

    const int inf = 1000;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i < j && a[i][j] != inf) {
                m++;
                d[m] = i;
                c[m] = j;
                ts[m] = a[i][j];
            }
        }
    }
    Kruskal();
    return 0;
}

/*
10
0 6 1000 1000 8 8 1000 1000 1000 1000
6 0 2 1000 4 6 1000 1000 1000 1000
1000 2 0 2 4 1000 1000 1000 1000 1000
1000 1000 2 0 4 1000 2 2 1000 2
8 4 4 4 0 4 4 1000 1000 1000
8 6 1000 1000 4 0 4 1000 1000 1000
1000 1000 1000 2 4 4 0 2 1000 1000
1000 1000 1000 2 1000 1000 2 0 1 1
1000 1000 1000 1000 1000 1000 1000 1 0 1
1000 1000 1000 2 1000 1000 1000 1 1 0

*/
#include <iostream>
#include <vector>
using namespace std;

int n, s;
int a[100][100], d[100], e[100], vs[100];
const int inf = 1000;

void Prim(int s) {
	for (int v = 1; v <= n; v++) {
		d[v] = a[s][v];
		e[v] = s;
		vs[v] = 0;
	}

	d[s] = 0, e[s] = 0, vs[s] = 1;
	int dem = 1, Wt = 0;
	vector<pair<int, int>> v;
	while (dem < n) {
		int u = 0, Min = 100000;
		for (int i = 1; i <= n; i++) {
			if (Min > d[i] && vs[i] == 0) {
				Min = d[i];
				u = i;
			}
		}
		if (u == 0) break;
		Wt += a[u][e[u]];
		v.push_back({ e[u], u });
		vs[u] = 1;
		for (int v = 1; v <= n; v++) {
			if (vs[v] == 0 && d[v] > a[u][v]) {
				d[v] = a[u][v];
				e[v] = u;
			}
		}
		dem++;
	}

	if (dem < n) cout << "Khong co cay khung\n";
	else {
		cout << "Wt = " << Wt << endl;
		cout << "T = {";
		for (int i = 0; i < v.size(); i++) {
			auto x = v[i];
			cout << "(" << x.first << "," << x.second << ")";
			if (i != v.size() - 1) cout << ";";
		}
		cout << "}\n";
	}
}

int main() {
	cin >> n;

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cin >> a[i][j];
		}
	}

	cin >> s;

	Prim(s);
	return 0;
}
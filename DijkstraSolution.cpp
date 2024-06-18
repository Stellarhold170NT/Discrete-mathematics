#include <iostream>
using namespace std;

int n, s;
int a[100][100], d[100], e[100], vs[100];
const int inf = 1000;

void Dijkstra(int s) {
	for (int v = 1; v <= n; v++) {
		d[v] = a[s][v];
		e[v] = s;
		vs[v] = 0;
	}

	d[s] = 0, e[s] = 0, vs[s] = 1;
	while (true) {
		int u = 0, Min = 100000;
		for (int i = 1; i <= n; i++) {
			if (Min > d[i] && vs[i] == 0) {
				Min = d[i];
				u = i;
			}
		}
		if (u == 0) break;
		vs[u] = 1;
		for (int v = 1; v <= n; v++) {
			if (vs[v] == 0 && d[v] > d[u] + a[u][v]) {
				d[v] = d[u] + a[u][v];
				e[v] = u;
			}
		}
	}

	for (int i = 1; i <= n; i++) {
		if (i != s) {
			if (d[i] != inf) {
				cout << "K/C ngan nhat tu " << s << " den " << i << ": " << d[i] << "; ";
				int v = i;
				while (v != s) {
					cout << v << " <- ";
					v = e[v];
				}
				cout << s << endl;
			}
			else cout << "Khong ton tai duong di ngan nhat tu " << s << " den " << i << endl;
		}
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

	Dijkstra(s);
	return 0;
}
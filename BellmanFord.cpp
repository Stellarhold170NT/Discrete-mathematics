#include <iostream>
using namespace std;

int n;
int a[100][100], d[100], e[100];
const int inf = 1000;

void BellmanFord(int s) {
	for (int v = 1; v <= n; v++) {
		d[v] = a[s][v];
		e[v] = s;
	}

	d[s] = 0; e[s] = 0;
	int ok = 0;

	for (int k = 1; k <= n - 1; k++) {
		ok = 1;
		for (int v = 1; v <= n; v++) {
			for (int u = 1; u <= n; u++) {
				if (d[v] > d[u] + a[u][v]) {
					d[v] = d[u] + a[u][v];
					e[v] = u;
					ok = 0;
				}
			}
		}
		if (ok == 1) break;
	}

	if (ok == 0) {
		cout << "Do thi chua chu trinh am\n";
	}
	else {
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
}
int main() {
	cin >> n;

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cin >> a[i][j];
		}
	}

	int s;
	cin >> s;

	BellmanFord(s);

	return 0;
}

/*
7
0 15 1000 1000 1000 1 9
1000 0 8 1000 1000 1000 1000
1000 1000 0 4 1 1000 1000
1000 7 1000 1000 1000 1000 1
1000 10 1000 2 0 1000 1000
1000 14 2 1000 1000 0 1000
1000 2 1000 1000 1000 1000 0
6
*/

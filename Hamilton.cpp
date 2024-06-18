#include <iostream>
using namespace std;

int n;
int a[100][100];
int vs[100] = { 0 };
int x[100] = { 0 };

void Hamilton(int k) {
	for (int v = 1; v <= n; v++) {
		if (k == 1 || a[x[k - 1]][v]) {
			if (k == n + 1) {
				if (v == x[1]) {
					for (int i = 1; i <= k - 1; i++) cout << x[i] << " ";
					cout << endl;
				}
			}
			else if (vs[v] == 0) {
				vs[v] = 1; x[k] = v;
				Hamilton(k + 1);
				vs[v] = 0;
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

	Hamilton(1);

	return 0;
}
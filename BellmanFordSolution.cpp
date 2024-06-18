#include <iostream>
#include <string>
#include <iomanip>
#include <Windows.h>
using namespace std;

#define color_black      0
#define color_dark_blue  1
#define color_dark_green 2
#define color_light_blue 3
#define color_dark_red   4
#define color_magenta    5
#define color_orange     6
#define color_light_gray 7
#define color_gray       8
#define color_blue       9
#define color_green     10
#define color_cyan      11
#define color_red       12
#define color_pink      13
#define color_yellow    14
#define color_white     15

string get_textcolor_code(const int textcolor) { // Linux only
	switch (textcolor) {
	case  0: return "30"; // color_black      0
	case  1: return "34"; // color_dark_blue  1
	case  2: return "32"; // color_dark_green 2
	case  3: return "36"; // color_light_blue 3
	case  4: return "31"; // color_dark_red   4
	case  5: return "35"; // color_magenta    5
	case  6: return "33"; // color_orange     6
	case  7: return "37"; // color_light_gray 7
	case  8: return "90"; // color_gray       8
	case  9: return "94"; // color_blue       9
	case 10: return "92"; // color_green     10
	case 11: return "96"; // color_cyan      11
	case 12: return "91"; // color_red       12
	case 13: return "95"; // color_pink      13
	case 14: return "93"; // color_yellow    14
	case 15: return "97"; // color_white     15
	default: return "37";
	}
}
string get_backgroundcolor_code(const int backgroundcolor) { // Linux only
	switch (backgroundcolor) {
	case  0: return  "40"; // color_black      0
	case  1: return  "44"; // color_dark_blue  1
	case  2: return  "42"; // color_dark_green 2
	case  3: return  "46"; // color_light_blue 3
	case  4: return  "41"; // color_dark_red   4
	case  5: return  "45"; // color_magenta    5
	case  6: return  "43"; // color_orange     6
	case  7: return  "47"; // color_light_gray 7
	case  8: return "100"; // color_gray       8
	case  9: return "104"; // color_blue       9
	case 10: return "102"; // color_green     10
	case 11: return "106"; // color_cyan      11
	case 12: return "101"; // color_red       12
	case 13: return "105"; // color_pink      13
	case 14: return "103"; // color_yellow    14
	case 15: return "107"; // color_white     15
	default: return  "40";
	}
}
string get_print_color(const int textcolor) { // Linux only
	return "\033[" + get_textcolor_code(textcolor) + "m";
}
string get_print_color(const int textcolor, const int backgroundcolor) { // Linux only
	return "\033[" + get_textcolor_code(textcolor) + ";" + get_backgroundcolor_code(backgroundcolor) + "m";
}
void print_color(const int textcolor) {
#if defined(_WIN32)
	static const HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, textcolor);
#elif defined(__linux__)
	cout << get_print_color(textcolor);
#endif // Windows/Linux
}
void print_color(const int textcolor, const int backgroundcolor) {
#if defined(_WIN32)
	static const HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, backgroundcolor << 4 | textcolor);
#elif defined(__linux__)
	cout << get_print_color(textcolor, backgroundcolor);
#endif // Windows/Linux
}
void print_color_reset() {
#if defined(_WIN32)
	static const HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, 7); // reset color
#elif defined(__linux__)
	cout << "\033[0m"; // reset color
#endif // Windows/Linux
}

void println(const string& s = "") {
	cout << s << endl;
}
void print(const string& s = "") {
	cout << s;
}
void print(const string& s, const int textcolor) {
	print_color(textcolor);
	cout << s;
	print_color_reset();
}
void print(const string& s, const int textcolor, const int backgroundcolor) {
	print_color(textcolor, backgroundcolor);
	cout << s;
	print_color_reset();
}
void print_no_reset(const string& s, const int textcolor) { // print with color, but don't reset color afterwards (faster)
	print_color(textcolor);
	cout << s;
}
void print_no_reset(const string& s, const int textcolor, const int backgroundcolor) { // print with color, but don't reset color afterwards (faster)
	print_color(textcolor, backgroundcolor);
	cout << s;
}

int n;
int a[100][100], d[100], e[100];
const int inf = 1000;

void print(int ok) {
	static int cnt = 0;
	cnt++;
	//cout << s << endl;
	if (cnt == 1) {
		print("\n>", color_black, color_cyan);
		print(" Lap bang\n", color_cyan);
		cout << setw(5) << left;
		print("Buoc", color_black, color_light_gray);
		for (int i = 1; i <= n; i++) {
			string str = "d[" + to_string(i) + "] | e[" + to_string(i) + "]";
			cout << setw(12) << left;
			print(str, color_black, color_light_gray);
		}
		cout << setw(3) << left;
		print("ok", color_black, color_light_gray);
	}
	//system("Color 07");
	cout << endl << setw(5) << left << cnt;
	for (int i = 1; i <= n; i++) {
		string str = "";
		str = (d[i] == inf ? "inf" : to_string(d[i])) + " | " + to_string(e[i]);
		cout << fixed << setw(12) << left;
		if (i % 2 == 1)
			print(str, color_light_blue);
		else print(str, color_cyan);
	}
	cout << setw(3) << left << ok;
	cout << endl;
}

void BellmanFord(int s) {
	for (int v = 1; v <= n; v++) {
		d[v] = a[s][v];
		e[v] = s;
	}

	d[s] = 0; e[s] = 0;
	int ok = 0;
	print(ok);

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
		print(ok);
		if (ok == 1) break;
	}

	print("\n>", color_black, color_cyan);
	print(" Ket qua\n", color_cyan);
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
	print(">", color_black, color_cyan);
	print(" Bellman Ford\n", color_cyan);
	cout << "Nhap n: ";
	cin >> n;

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cin >> a[i][j];
		}
	}

	cout << "Nhap dinh xuat phat: ";
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

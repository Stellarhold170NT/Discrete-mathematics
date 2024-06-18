#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cstring>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <stack>
#include <cmath>
#include <iomanip>
#include <cstdlib>
#include <numeric>
#include <unordered_set>
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
int a[100][100];
int vs[100] = { 0 };
int x[100] = { 0 };
map<int, string> mp;

struct Data {
	int len;
	int base;
};

int cnt = 0;

Data Hamilton(int k) {
	int lengthNode = 0;
	int st = 0;
	int l = 0;
	int isLeafNode = 1;
	bool check = 0;
	for (int v = 1; v <= n; v++) {
		if (a[x[k - 1]][v]) {
			if (k == n + 1) {
				if (v == x[1]) {
					for (int i = 1; i <= k - 1; i++) cout << x[i] << (i < n ? " -> " : "");
					cout << endl;
				}
			}
			else if (vs[v] == 0) {
				vs[v] = 1; x[k] = v;
				isLeafNode = 0;
				Data d = Hamilton(k + 1);
				l = d.len;
				if (!check) {
					//check = 1;
					st = d.base;
					while (mp[k].length() < st) mp[k] += " ";
				}

				lengthNode += l;
				l = l + l * 2;
				string s = "";
				for (int i = 1; i <= l / 2; i++) s += " ";
				if (!check) {
					check = 1;
					s[0] = '|';
				}
				s += to_string(v);
				int r = l - s.length();
				for (int i = 1; i <= r; i++) s += " ";
				mp[k] += s;
				vs[v] = 0;
			}
		}
	}

	if (mp[k].size()) {
		mp[k][mp[k].length() - 1] = '|';
	}

	if (isLeafNode) {
		int st = cnt * 3;
		cnt++;
		return { 1, st };
	}

	return { lengthNode, st };
}

void LietKeHamilton(int u) {
	for (int v = 1; v <= n; v++) vs[v] = 0;
	vs[u] = 1;
	x[1] = u;
	print("\n>", color_black, color_cyan);
	print(" Ket Qua", color_cyan);
	cout << "\nChu trinh Hamilton xuat phat tu dinh " << u << " la : \n";
	Hamilton(2);

	print("\n>", color_black, color_cyan);
	print(" Xay dung cay tim kiem: \n", color_cyan);

	int len = mp[2].length();

	string s = "";
	for (int i = 1; i < len / 2; i++) s += " ";
	s += to_string(u);
	int r = len - s.length();
	for (int i = 1; i <= r; i++) s += " ";
	//s.at(s.length() - 1) = '|';
	cout << s << endl;
	for (int i = 2; i <= n; i++) {
		string tmp = "";
		string tmp0 = "";
		for (int j = 0; j < mp[i].length(); j++) {
			tmp += " ";
			tmp0 += " ";
		}
		int flag = 0;
		for (int j = 0; j < mp[i].length(); j++) {
			if (mp[i][j] == '|') {
				flag = 1;
				for (int k = j - 1; k >= 0; k--) {
					tmp0[k] = ' ';
					if (isdigit(mp[i][k])) break;
				}
			}
			if (flag == 0) tmp0[j] = '-';
			if (isdigit(mp[i][j])) {
				tmp[j] = '|';
				flag = 0;
			}
		}
		cout << tmp0 << endl;
		cout << tmp << endl;
		for (auto x : mp[i]) {
			if (x == '|') x = ' ';
			cout << x;
		}
		cout << endl;

	}
}

int main() {
	print(">", color_black, color_cyan);
	print(" Hamilton\n", color_cyan);
	int u;
	cout << "Nhap n: ";
	cin >> n;

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cin >> a[i][j];
		}
	}

	cout << "Nhap dinh bat dau: ";
	cin >> u;
	LietKeHamilton(u);
	return 0;
}

/*
10
0 1 1 0 0 0 0 0 0 0
 0 0 1 1 0 0 1 0 0 0
 0 0 0 1 1 0 0 0 0 0
 0 0 0 0 1 1 0 0 0 0
 0 1 0 0 0 1 0 0 0 1
 0 0 0 0 0 0 1 1 0 0
 0 0 0 0 1 0 0 1 1 0
 0 0 0 0 0 0 0 0 1 1
 1 0 0 0 0 0 0 0 0 1
1 1 0 0 0 0 1 0 0 0

|-|

5
0 1 0 1 0
1 0 1 0 1
0 1 0 1 1
1 0 1 0 1
0 1 1 1 0

8
0 1 0 0 0 0 1 1
1 0 1 0 0 1 0 1
0 1 0 1 0 0 0 0
0 0 1 0 1 1 0 0
0 0 0 1 0 1 0 0
0 1 0 1 1 0 1 1
1 0 0 0 0 1 0 0
1 1 0 0 0 1 0 0


*/

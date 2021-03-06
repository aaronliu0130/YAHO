#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
#include <ctime>
using namespace std;
bool debug = false;
bool kcs(0), nev(0);
int wnm = 3;
int mapp = 0;
bool ext, typ = false;
const string opr = "+-";
const string apha = "abcdefghijklmnopqrstuvwxyzl";
const string aval = "11234567895";
string wstdim() {
	string s, nam, val;
	for (int i = 1; i <= 3 + rand() % 12; i++)
		nam += apha[rand() % 26];

	for (int i = 1; i <= 1 + rand() % 8; i++)
		val += aval[rand() % 10];

	s = "int " + nam + " = " + val + ";\n";
	return s;
}

string wstfor() {
	string s, v0, nam, v1, v2, na2;
	for (int i = 1; i <= 3 + rand() % 12; i++)
		nam += apha[rand() % 26];

	for (int i = 1; i <= 3 + rand() % 12; i++)
		na2 += apha[rand() % 26];

	for (int i = 1; i <= 1 + rand() % 9; i++)
		v0 += aval[rand() % 10];

	for (int i = 1; i <= 1 + rand() % 2; i++)
		v1 += aval[rand() % 10];

	for (int i = 1; i <= 1 + rand() % 2; i++)
		v2 += aval[rand() % 10];
	s = "\nint " + nam + " = " + v0 + ";\n" + "for (int " + na2 + " = " + v1
			+ "; " + na2 + " <= " + v2 + "; " + na2 + "++) " + nam + " += "
			+ na2 + ";\n";
	return s;
}

string wstif() {
	string s, v0, v1;
	for (int i = 1; i <= 1 + rand() % 8; i++)
		v0 += aval[rand() % 10];

	for (int i = 1; i <= 1 + rand() % 8; i++)
		v1 += aval[rand() % 10];

	s = "if(" + v0 + " == " + v1 + ") " + wstdim() + " else " + wstdim() + "\n";

	return s;
}

string wstexp() {
	string s, v0, v1;
	for (int i = 1; i <= 1 + rand() % 8; i++)
		v0 += aval[rand() % 10];

	for (int i = 1; i <= 1 + rand() % 8; i++)
		v1 += aval[rand() % 10];

	s = "(" + v0 + "-" + v0 + ")" + "*" + v1;

	return s;
}

string dspl(string s, int sd) {
	for (int i = 1; i <= sd; i++)
		s = s + opr[rand() % 2] + wstexp();
	return s;
}
string eval(string s) {
	int eq = 0;
	while (eq <= static_cast<int>(s.length()) && s[eq] != '=')
		eq++;
	if (eq > static_cast<int>(s.length()))
		return s;
	if (s[eq + 1] == '=')
		eq++;
	int depth = 0, len = 0;
	while (eq + len < static_cast<int>(s.length()) && !(len != 0 && depth == -1)) {
		len++;
		if (s[eq + len] == '(')
			depth++;
		else if (s[eq + len] == ')' || s[eq + len] == ';')
			depth--;
	}
	if (debug)
		cerr << eq << ' ' << len << endl;
	string k;
	if (debug)
		cerr << "encoding " + s.substr(eq + 1, len - 1) + " ..." << endl;
	k = s.substr(0, eq + 1) + dspl(s.substr(eq + 1, len - 1), rand() % wnm)
			+ s.substr(eq + len, static_cast<int>(s.length()) - (eq + len) + 1);
	return k;
}

void wstgen(int a, int b, int c) {
	for (int i = 1; i <= rand() % a; i++)
		cout << (nev ? wstdim() : eval(wstdim()));
	for (int i = 1; i <= rand() % b; i++)
		cout << (nev ? wstfor() : eval(wstfor()));
	for (int i = 1; i <= rand() % c; i++)
		cout << (nev ? wstif() : eval(wstif()));
}

string chkhead(string a) {
	int x = 0;
	while (!((a[x] >= 'A' && a[x] <= 'Z') || (a[x] >= 'a' && a[x] <= 'z')
			|| a[x] == '_' || a[x] == '#' || a[x] == '{' || a[x] == '/'
			|| a[x] == '}' || a[x] == '\t' || (a[x] == '+' && a[x + 1] == '+')
			|| (a[x] == '-' && a[x + 1] == '-'))
			&& x < static_cast<int>(a.size())) {
		a[x] = ' ';
		x++;
	}

	return a;
}

string chkrem(string a) {
	for (int i = 0; i < static_cast<int>(a.size()) - 1; i++) {
		if (a[i] == '/' && a[i + 1] == '/') {
			for (int j = i; j < static_cast<int>(a.size()); j++)
				a[j] = ' ';
		} else if (a[i] == '/' && a[i + 1] == '*') {
			while (!(a[i] == '*' && a[i + 1] == '/')
					&& i < static_cast<int>(a.size()) - 1) {
				a[i] = ' ';
				i++;
			}
			a[i] = ' ';
			a[i + 1] = ' ';
		} else if (a[i] == ';' && a[i + 1] == ';') {
			a[i] = ' ';
		}
	}
	return a;
}

bool wchk(string s) {
	for (int i = 0; i < static_cast<int>(s.size()); i++)
		if (s[i] == '{')
			mapp++;
		else if (s[i] == '}' && mapp > 0)
			mapp--;

	if (mapp == 0)
		typ = false;
	int len = static_cast<int>(s.length());
	int hd = 0;
	while (s[hd] == ' ')
		hd++;
	if (debug)
		cerr << "Checking";
	if (debug)
		cerr << typ << endl;
	if (debug)
		cerr << s[hd + 0] << s[hd + 1] << s[hd + 2] << s[hd + 3] << s[hd + 4]
				<< s[hd + 5] << endl;
	if (s[hd + 0] == 'c' && s[hd + 1] == 'l' && s[hd + 2] == 'a'
			&& s[hd + 3] == 's' && s[hd + 4] == 's')
		typ = true;
	if (s[hd + 0] == 's' && s[hd + 1] == 't' && s[hd + 2] == 'r'
			&& s[hd + 3] == 'u' && s[hd + 4] == 'c' && s[hd + 5] == 't')
		typ = true;
	for (int i = 0; i < len; i++) {
		if (i < len && s[i] == '}')
			return false;
		if (i < len - 1 && s[i] == 'i' && s[i + 1] == 'f')
			return false;
		if (i < len - 1 && s[i] == 'd' && s[i + 1] == 'o')
			return false;
		if (i < len - 2 && s[i] == 'f' && s[i + 1] == 'o' && s[i + 2] == 'r')
			return false;
		if (i < len - 4 && s[i] == 'w' && s[i + 1] == 'h' && s[i + 2] == 'i'
				&& s[i + 3] == 'l' && s[i + 4] == 'e')
			return false;
		if (i < len - 3 && s[i] == 'e' && s[i + 1] == 'l' && s[i + 2] == 's'
				&& s[i + 3] == 'e')
			return false;
		if (i < len - 5 && s[i] == 's' && s[i + 1] == 'w' && s[i + 2] == 'i'
				&& s[i + 3] == 't' && s[i + 4] == 'c' && s[i + 5] == 'h')
			return false;
	}
	return true;
}

int main(int argc, char **argv) {
	srand((unsigned) time(NULL));
	if (argc < 3) {
		cerr
				<< R"(
Yet Another Helper for trOllers

语法 Usage:
YAHO <source file> <target file> [options]
YAHO <源代码> <目标文件> [设置]

设置 Options:
[-k][--kcs] 						don't generate waste but add spaghetti numbers						卡常数模式（让每个数字变得乱七八糟，但不会添加其他的垃圾代码）

[-s <swm>][--super <swm>]			super mode (Spaghetti Code Multiplier+swm,defaulted to +2)			超级模式（随机加花代码+swm，默认+2）

[-ne][--no-eval]					don't generate spaghetti numbers but add waste						不将常数（-INT_MAX~INT_MAX）加花

[-cl]								only remove comments and line numbers								不添加随机加花代码

[-d][--debug]						debug mode with process and argument information					输出微妙的运行程度与数据

[-b <binary>]						specify the binary for formatting									指明用来美化程序的可执行文件

[-h][--help]						brings up this screen with usage and options						输出这个页面

注意事项 Caveats:
1. Currently, if you don't specify the formatter, you need to put the bin folder in the same directory as where this executable is
being executed from.
2. This program is not verbose.
1. 目前如果您要使用默认程序美化可执行文件的话，您需要将bin文件夹放在与执行此可执行文件的目录相同的目录中。
2. 这个程序缺乏鲁棒性)";
		if (!strcmp(argv[0], "-h")) {
			return 0;
		}
		cerr << "Not enough arguments." << endl;
		return 1;
	}
	freopen(argv[1], "r", stdin);
	freopen(argv[2], "w", stdout);
	string t;
	if (argc >= 4) {
		for (int i = 4; i <= argc; i++) {
			if (!strcmp(argv[i - 1], "-k") || !strcmp(argv[i - 1], "--kcs")) {
				kcs = true;
				cerr << "Running in KCS Mode." << endl;
			} else if (!strcmp(argv[i - 1], "-s")
					|| !strcmp(argv[i - 1], "--super")) {
				int wplus = *argv[i] - '0';
				if (wplus >= 0 && wplus <= 9)
					wnm += wplus;
				else
					wnm += 2;
				cerr << "Running in Super Mode with number of wastes " << wnm
						<< "." << endl;
			} else if (!strcmp(argv[i - 1], "-ne")
					|| !strcmp(argv[i - 1], "--no-eval")) {
				nev = true;
				cerr << "Running in No-eval Mode." << endl;
			} else if (!strcmp(argv[i - 1], "-cl")) {
				nev = true, kcs = true;
				cerr << "Running in No-Comment-LineNo Only Mode." << endl;
			} else if (!strcmp(argv[i - 1], "-d")
					|| !strcmp(argv[i - 1], "--debug")) {
				debug = true;
				cerr << "Running with debugging info." << endl;
			} else if (!strcmp(argv[i - 1], "-b")) {
			}
		}
	}
	if (debug)
		cerr << "Number of arguments: " << argc << endl;
	string s;
	while (getline(cin, s)) {
		if (debug)
			cerr << "processing " << s << " ...\n";
		if (s != "") {
			s = chkhead(s);
			s = chkrem(s);
			if (!nev)
				s = eval(s);
		}
		cout << s << endl;
		ext = wchk(s);
		if (mapp > 0 && ext && !kcs && !typ && debug)
			cerr << "genarating waste...\n";
		if (mapp > 0 && ext && !kcs && !typ)
			wstgen(wnm, wnm, wnm);
		if (debug)
			cerr << "*********" << mapp << "**********" << endl;
	}
	fclose(stdin);
	fclose(stdout);
	cerr << "Calling formatter..." << endl;
#ifdef __WIN32__
	t = string("bin\\astyle.exe ") + argv[2];
#else
	t = string("./bin/astyle") + argv[2];
#endif
	system(t.c_str());
	cerr << "All Done, Have Fun!" << endl;
	return 0;
}

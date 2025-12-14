#include <bits/stdc++.h>

using ll = long long;
using ull = unsigned long long;
using namespace std;

int part1(const string& s) {
    int bal = 0;
    for (char c : s)
        bal += (c == '(') - (c == ')');
    return bal;
}

int part2(const std::string& s) {
    int bal = 0;
    for (int i = 0; i < (int)s.size(); ++i) {
        bal += (s[i] == '(') - (s[i] == ')');
        if (bal < 0) {
            return i + 1;
        }
    }
    return -1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    ifstream fin("input.txt");
    if (!fin) {
        cerr << "Broken file" << endl;
        throw;
    }
    string str;
    getline(fin, str);
    cout << part1(str) << endl;
    cout << part2(str) << endl;
    return 0;
}
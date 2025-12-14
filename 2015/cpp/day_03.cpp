#include <bits/stdc++.h>

using ll = long long;
using ull = unsigned long long;
using namespace std;

int64_t encode(int x, int y) {
    return (int64_t(x) << 32) | uint32_t(y);
}

int part1(const string& s) {
    unordered_set<int64_t> set;
    int x = 0, y = 0;
    set.insert(encode(x, y));
    for (char c : s) {
        if (c == '^') y++;
        if (c == 'v') y--;
        if (c == '>') x++;
        if (c == '<') x--;
        set.insert(encode(x, y));
    }
    return set.size();
}

int part2(const string& s) {
    int x1 = 0, y1 = 0;
    int x2 = 0, y2 = 0;
    unordered_set<int64_t> set;
    set.insert(encode(0, 0));
    for (int i = 0; i < s.size(); ++i) {
        int& x = (i % 2 == 0) ? x1 : x2;
        int& y = (i % 2 == 0) ? y1 : y2;
        switch (s[i]) {
            case '^': y++; break;
            case 'v': y--; break;
            case '>': x++; break;
            case '<': x--; break;
        }
        set.insert(encode(x, y));
    }
    return set.size();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    ifstream fin("input.txt");
    string str;
    getline(fin, str);
    cout << part1(str) << endl;
    cout << part2(str) << endl;
    return 0;
}
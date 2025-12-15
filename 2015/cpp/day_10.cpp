#include <bits/stdc++.h>

using ll = long long;
using ull = unsigned long long;
using namespace std;

string transform(string s) {
    char start = s[0];
    int amount = 1;
    string result;
    for (int i = 0; i < s.size() - 1; ++i) {
        if (s[i + 1] == start) {
            amount++;
        }
        else {
            result += to_string(amount);
            result.push_back(start);
            start = s[i + 1];
            amount = 1;
        }
    }
    result += to_string(amount);
    result.push_back(start);
    return result;
}

int part1(string s) {
    string result = s;
    for (int i = 0; i < 40; i++) {
        result = transform(result);
    }
    return result.size();
}

int part2(string s) {
    string result = s;
    for (int i = 0; i < 50; i++) {
        result = transform(result);
    }
    return result.size();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << part1("11") << endl;
    cout << part2("11") << endl;
    return 0;
}
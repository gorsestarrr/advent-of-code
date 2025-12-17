#include <bits/stdc++.h>

using ll = long long;
using ull = unsigned long long;
using namespace std;

bool checkIncreasing(const string& s) {
    int n = s.length();
    for (int i = 0; i < n - 2; ++i) {
        if (s[i + 1] == s[i] + 1 && s[i + 2] == s[i] + 2) {
            return true;
        }
    }
    return false;
}

bool checkPairs(const string& s) {
    int size = 0;
    for (int i = 0; i < s.size() - 1; ++i) {
        if (s[i] == s[i + 1]) {
            size++;
            i++;
        }
    }
    return size >= 2;
}

bool validPassword(const string& s) {
    return checkIncreasing(s) && checkPairs(s);
}

char nextChar(char a) {
    if (a == 'z') {
        return 'a';
    }
    char next = a + 1;
    if (next == 'i' || next == 'o' || next == 'l') {
        return next + 1;
    }
    return next;
}

void increment(string& s, const string& given, int n) {
    if (n < 0) return;
    char c = nextChar(s[n]);
    s[n] = c;
    if (s[n] == 'a') {
        increment(s, given, n - 1);
    }
}

string solve(const string& s) {
    string current = s;
    increment(current, s,  s.length() - 1);
    while (!validPassword(current)) {
        increment(current, s,  s.length() - 1);
    }
    return current;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << solve("input") << endl;
    cout << solve(solve("input")) << endl;
    return 0;
}
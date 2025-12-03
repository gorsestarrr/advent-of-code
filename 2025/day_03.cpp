#include <bits/stdc++.h>

using ll = long long;
using ull = unsigned long long;
using namespace std;

int findMax(const string& s) {
    int maxDigit = -1;
    int maxIdx = -1;
    for (int i = 0; i < (int)s.size() - 1; i++) {
        int d = s[i] - '0';
        if (d > maxDigit) {
            maxDigit = d;
            maxIdx = i;
        }
    }
    int bestVal = -1;
    for (int j = maxIdx + 1; j < (int)s.size(); j++) {
        int b = s[j] - '0';
        int cur = maxDigit * 10 + b;
        if (cur > bestVal) {
            bestVal = cur;
        }
    }
    return bestVal;
}

ull find12Max(const string& s) {
    int n = s.size();
    int need = 12;
    int toRemove = n - need;
    string st;
    for (char c : s) {
        while (!st.empty() && st.back() < c && toRemove > 0) {
            st.pop_back();
            toRemove--;
        }
        st.push_back(c);
    }
    while (st.size() > need) st.pop_back();
    return stoll(st);
}

int part1(const vector<string>& batteries) {
    int result = 0;
    for (auto& battery : batteries) {
        result += findMax(battery);
    }
    return result;
}

ull part2(const vector<string>& batteries) {
    ull result = 0;
    for (auto& battery : batteries) {
        result += find12Max(battery);
    }
    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    ifstream fin("input.txt");
    if (!fin) {
        cerr << "Broken file" << endl;
        throw;
    }
    string line;
    vector<string> lights;
    while (getline(fin, line)) {
        lights.push_back(line);
    }
    cout << part2(lights);
    return 0;
}
#include <bits/stdc++.h>

using ll = long long;
using ull = unsigned long long;
using namespace std;

ll digitsToNumber(const vector<int>& digits) {
    ll x = 0;
    for (int d : digits) {
        x = x * 10 + d;
    }
    return x;
}

vector<string> splitBySpaces(const string& s) {
    istringstream in(s);
    vector<string> tokens;
    string token;
    while (in >> token) {
        tokens.push_back(token);
    }
    return tokens;
}

ll part1(const vector<vector<string>>& input) {
    int n = input.size();
    int m = input[0].size();
    ll result = 0;
    for (int i = 0; i < m; ++i) {
        ll lineResult = 0;
        string op = input[n - 1][i];
        if (op == "*") {
            lineResult = 1;
        }
        for (int j = 0; j < n - 1; j++) {
            if (op == "+") {
                lineResult += stoi(input[j][i]);
            }
            else if (op == "*") {
                lineResult *= stoi(input[j][i]);
            }
        }
        result += lineResult;
    }
    return result;
}

ll part2(const vector<vector<char>>& map) {
    int n = map.size();
    int m = map[0].size();
    vector<ll> columnNumbers;
    ll result = 0;
    for (int i = m - 1; i >= 0; i--) {
        vector<int> column;
        bool add = false;
        bool multiply = false;
        for (int j = 0; j < n; j++) {
            if (std::isdigit(map[j][i])) {
                column.push_back(map[j][i] - '0');
            }
            else if (map[j][i] == '+') {
                add = true;
            }
            else if (map[j][i] == '*') {
                multiply = true;
            }
        }
        if (column.size() > 0) {
            columnNumbers.push_back(digitsToNumber(column));
        }
        if (add) {
            ll crv = 0;
            for (auto& val : columnNumbers) {
                crv += val;
            }
            result += crv;
            columnNumbers.clear();
        }
        else if (multiply) {
            ll crv = 1;
            for (auto& val : columnNumbers) {
                crv *= val;
            }
            result += crv;
            columnNumbers.clear();
        }
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
    string str;
    vector<vector<string>> map1;
    vector<vector<char>> map2;
    while (getline(fin, str) && !str.empty()) {
        map1.push_back(  splitBySpaces(str));
        vector<char> line2;
        for (char c : str) {
            line2.push_back(c);
        }
        map2.push_back(line2);
    }
    cout << part1(map1) << endl;
    cout << part2(map2);
    return 0;
}
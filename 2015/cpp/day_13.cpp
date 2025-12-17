#include <bits/stdc++.h>

using ll = long long;
using ull = unsigned long long;
using namespace std;

int part1 (unordered_map<string, vector<pair<string, int>>>& m) {
    vector<string> keys;
    for (const auto& [k, _] : m) {
        keys.push_back(k);
    }

    sort(keys.begin(), keys.end());

    int best = 0;
    int n = keys.size();

    do {
        int sum = 0;
        for (int i = 0; i < n; ++i) {
            const string& cur = keys[i];
            const string& left  = keys[(i + n - 1) % n];
            const string& right = keys[(i + 1) % n];

            for (const auto& [name, val] : m[cur]) {
                if (name == left || name == right) {
                    sum += val;
                }
            }
        }
        best = max(best, sum);
    } while (next_permutation(keys.begin(), keys.end()));

    return best;
}

int part2(unordered_map<string, vector<pair<string, int>>>& m) {
    for (const auto& [k, _] : m) {
        m[k].emplace_back("Me", 0);
        m["Me"].emplace_back(k, 0);
    }
    return part1(m);
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    ifstream fin("input.txt");
    string str;
    unordered_map<string, vector<pair<string, int>>> map;
    while (getline(fin, str)) {
        char from[32];
        char type[8];
        char to[32];
        int value;
        sscanf(str.c_str(),
               "%31s would %7s %d happiness units by sitting next to %31[^.]",
               from, type, &value, to);
        string from_s(from);
        string to_s(to);
        string type_s(type);
        if (type_s == "lose") {
            value = -value;
        }
        map[from].push_back(make_pair(to, value));
    }
    cout << part1(map) << endl;
    cout << part2(map);
    return 0;
}
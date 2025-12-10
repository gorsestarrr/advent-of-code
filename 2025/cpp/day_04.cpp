#include <bits/stdc++.h>

using ll = long long;
using ull = unsigned long long;
using namespace std;

int checkNeighbor(int i, int j, const vector<vector<char>>& map) {
    if (i < 0 || i >= map.size() || j < 0 || j >= map[0].size()) {
        return 0;
    }
    return map[i][j] == '@' ? 1 : 0;
}

int calculateNeighbors(int i, int j, const vector<vector<char>>& map) {
    int result = 0;
    static const int dx[8] = { -1, -1, -1,  0, 0, 1, 1, 1 };
    static const int dy[8] = { -1,  0,  1, -1, 1,-1, 0, 1 };
    for (int k = 0; k < 8; ++k) {
        result += checkNeighbor(i + dx[k], j + dy[k], map);
    }
    return result;
}

vector<pair<int,int>> findAccessible(const vector<vector<char>>& map) {
    int n = map.size();
    int m = map[0].size();
    vector<pair<int,int>> pairs;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (map[i][j] == '@' && calculateNeighbors(i, j, map) < 4) {
                pairs.emplace_back(i, j);
            }
        }
    }
    return pairs;
}

int part1(vector<vector<char>> map) {
    return findAccessible(map).size();
}

int part2(vector<vector<char>> map) {
    int removed = 0;
    while (true) {
        auto toRemove = findAccessible(map);
        if (toRemove.empty()) {
            return removed;
        }
        for (auto& [i, j] : toRemove) {
            map[i][j] = 'x';
            removed++;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    ifstream fin("input.txt");
    if (!fin) {
        cerr << "Broken file" << endl;
        throw;
    }
    vector<vector<char>> map;
    string str;
    while (getline(fin, str)) {
        vector<char> line;
        for (char c : str) {
            line.push_back(c);
        }
        map.push_back(line);
    }
    cout << part1(map) << endl;
    cout << part2(map);
    return 0;
}
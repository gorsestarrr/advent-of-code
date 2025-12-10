#include <bits/stdc++.h>

using ll = long long;
using ull = unsigned long long;
using namespace std;

bool inBounds(int i, int j, int n, int m) {
    return i > 0 && i < n && j > 0 && j < m;
}

int H, W;
vector<vector<char>> mp;
vector<vector<ll>> dp;
vector<vector<bool>> vis;

ll solve(int i, int j) {
    if (j < 0 || j >= W) return 0;
    if (i == H - 1) return 1;
    if (vis[i][j]) return dp[i][j];
    vis[i][j] = true;
    ll res = 0;
    if (mp[i + 1][j] == '^') {
        res =  solve(i + 1, j - 1) + solve(i + 1, j + 1);
    } else {
        res = solve(i + 1, j);
    }
    dp[i][j] = res;
    return res;
}

ll part2(vector<vector<char>> map) {
    mp = map;
    H = mp.size();
    W = mp[0].size();
    dp.assign(H, vector<ll>(W, 0));
    vis.assign(H, vector<bool>(W, false));
    int startJ;
    for (int j = 0; j < W; j++) {
        if (map[0][j] == 'S') {
            startJ = j;
        }
    }
    return solve(0, startJ);
}

int part1(vector<vector<char>> map) {
    int n = map.size();
    int m = map[0].size();
    int split = 0;
    for (int i = 1; i < n - 1; ++i) {
        for (int j = 0; j < m; ++j) {
            if (map[i][j] == '|') {
                char under = map[i + 1][j];
                if (under == '.') {
                    map[i + 1][j] = '|';
                }
                else if (under == '^') {
                    if (inBounds(i + 1, j - 1, n, m)) {
                        map[i + 1][j - 1] = '|';
                    }
                    if (inBounds(i + 1, j + 1, n, m)) {
                        map[i + 1][j + 1] = '|';
                    }
                    split++;
                }
            }
        }
    }
    return split;
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
    vector<vector<char>> map;
    while (getline(fin, str) && !str.empty()) {
        vector<char> line;
        for (char c : str) {
            line.push_back(c);
        }
        map.push_back(line);
    }
    cout << part2(map);
    return 0;
}
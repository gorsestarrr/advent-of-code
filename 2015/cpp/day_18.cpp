#include <bits/stdc++.h>

using ll = long long;
using ull = unsigned long long;
using namespace std;

void print(const vector<vector<char>>& matrix) {
    int n = matrix.size();
    int m = matrix[0].size();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cout << matrix[i][j];
            if (j == m - 1) {
                cout << endl;
            }
        }
    }
    cout << endl;
}

vector<vector<char>> parseInput(const string& filename) {
    ifstream fin(filename);
    vector<vector<char>> grid;
    string line;
    while (getline(fin, line)) {
        vector<char> row;
        for (char c : line) {
            row.push_back(c);
        }
        grid.push_back(row);
    }
    return grid;
}

bool checkBorders(int i, int j, const vector<vector<char>>& matrix) {
    return (i >= 0 && i < matrix.size()) && (j >= 0 && j < matrix[0].size());
}

bool checkCorner(int i, int j, const vector<vector<char>>& matrix) {
    int n = matrix.size();
    int m = matrix[0].size();
    bool tl = (i == 0 && j == 0);
    bool tr = (i == 0 && j == m - 1);
    bool bl = (i == n - 1 && j == 0);
    bool br = (i == n - 1 && j == m - 1);
    return tl || tr || bl || br;
}

int part1(vector<vector<char>>& grid, int steps) {
    int n = grid.size();
    int m = grid[0].size();
    const int dx[8] = {1, -1, 0, 0, 1, 1, -1, -1};
    const int dy[8] = {0, 0, 1, -1, 1, -1, 1, -1};
    for (int s = 0; s < steps; ++s) {
        vector<vector<char>> next = grid;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                int onCount = 0;
                for (int k = 0; k < 8; ++k) {
                    int y = i + dy[k];
                    int x = j + dx[k];
                    if (checkBorders(x, y, grid) && grid[y][x] == '#') {
                        onCount++;
                    }
                }
                if (grid[i][j] == '#' && (onCount != 2 && onCount != 3)) {
                    next[i][j] = '.';
                }
                else if (grid[i][j] == '.' && onCount == 3) {
                    next[i][j] = '#';
                }
            }
        }
        grid = next;
    }
    int lightsOn = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (grid[i][j] == '#') {
                lightsOn++;
            }
        }
    }
    return lightsOn;
}

int part2(vector<vector<char>>& grid, int steps) {
    int n = grid.size();
    int m = grid[0].size();
    const int dx[8] = {1, -1, 0, 0, 1, 1, -1, -1};
    const int dy[8] = {0, 0, 1, -1, 1, -1, 1, -1};
    grid[0][0] = '#';
    grid[0][m - 1] = '#';
    grid[n - 1][0] = '#';
    grid[n - 1][m - 1] = '#';
    for (int s = 0; s < steps; ++s) {
        vector<vector<char>> next = grid;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                int onCount = 0;
                for (int k = 0; k < 8; ++k) {
                    int y = i + dy[k];
                    int x = j + dx[k];
                    if (checkBorders(x, y, grid) && grid[y][x] == '#') {
                        onCount++;
                    }
                }
                if (checkCorner(i, j , grid)) {
                    continue;
                }
                if (grid[i][j] == '#' && (onCount != 2 && onCount != 3)) {
                    next[i][j] = '.';
                }
                else if (grid[i][j] == '.' && onCount == 3) {
                    next[i][j] = '#';
                }
            }
        }
        grid = next;
    }
    int lightsOn = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (grid[i][j] == '#') {
                lightsOn++;
            }
        }
    }
    return lightsOn;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    auto grid = parseInput("input.txt");
    //cout << part1(grid, 5) << endl;
    cout << part2(grid, 100);
    return 0;
}
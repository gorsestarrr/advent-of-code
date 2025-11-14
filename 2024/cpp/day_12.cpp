#include <bits/stdc++.h>
#include <cmath>
#define ull unsigned long long
using namespace std;


struct Region {
    char ch;
    vector<pair<int,int>> cells;
};

bool checkBorders(int i, int j, const vector<vector<char>>& matrix) {
    return (i >= 0 && i < matrix.size()) && (j >= 0 && j < matrix[0].size());
}

vector<vector<char>> readMatrix(istream& fin) {
    vector<vector<char>> matrix;
    string line;
    while (getline(fin, line)) {
        vector<char> row;
        for (char c : line) {
            row.push_back(c);
        }
        matrix.push_back(row);
    }
    return matrix;
}

vector<Region> findRegions(const vector<vector<char>>& field) {
    int n = field.size();
    int m = field[0].size();
    vector<vector<bool>> visited(n, vector<bool>(m, false));
    vector<Region> regions;
    const int dx[4] = {1, -1, 0, 0};
    const int dy[4] = {0, 0, 1, -1};

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (visited[i][j]) {
                continue;
            }
            char cur = field[i][j];
            visited[i][j] = true;
            queue<pair<int, int>> queue;
            queue.push({i, j});
            Region region;
            region.ch = cur;
            while (!queue.empty()) {
                auto [x, y] = queue.front();
                queue.pop();
                region.cells.push_back({x, y});
                for (int k = 0; k < 4; ++k) {
                    int nx = x + dx[k];
                    int ny = y + dy[k];
                    if (nx < 0 || nx >= n || ny < 0 || ny >= m) {
                        continue;
                    }
                    if (visited[nx][ny]) {
                        continue;
                    }
                    if (field[nx][ny] != cur) {
                        continue;;
                    }
                    queue.push({nx, ny});
                    visited[nx][ny] = true;
                }
            }
            regions.push_back(move(region));
        }
    }
    return regions;
}

int calcArea(Region region) {
    return region.cells.size();
}

int checkCorner(pair<int,int> cell, const vector<vector<char>>& field) {
    auto [x, y] = cell;
    char c = field[x][y];
    
    bool N = checkBorders(x, y - 1, field) && field[x][y-1] == c;
    bool S = checkBorders(x, y + 1, field) && field[x][y+1] == c;
    bool W = checkBorders(x - 1, y, field) && field[x-1][y] == c;
    bool E = checkBorders(x + 1, y, field) && field[x+1][y] == c;
    bool NW = checkBorders(x-1, y-1, field) && field[x-1][y-1] == c;
    bool NE = checkBorders(x+1, y-1, field) && field[x+1][y-1] == c;
    bool SW = checkBorders(x-1, y+1, field) && field[x-1][y+1] == c;
    bool SE = checkBorders(x+1, y+1, field) && field[x+1][y+1] == c;

    int corners = 0;
    if (E && S && !SE) corners++;
    if (W && S && !SW) corners++;
    if (W && N && !NW) corners++;
    if (E && N && !NE) corners++;

    if (!(S || W)) corners++;
    if (!(S || E)) corners++;
    if (!(N || W)) corners++;
    if (!(N || E)) corners++;

    return corners;
}

int calcCorners(Region region, const vector<vector<char>>& field) {
    int corners = 0 ;
    for (auto& cell : region.cells) {
        corners+=checkCorner(cell, field);
    }
    return corners;
}

int calcPerimeter(Region region, vector<vector<char>> field) {
    int n = field.size();
    int m = field[0].size();
    int perimeter = 0;
    const int dx[4] = {1, -1, 0, 0};
    const int dy[4] = {0, 0, 1, -1};
    for (auto& cell : region.cells) {
        int x = cell.first;
        int y = cell.second;
        for (int k = 0; k < 4; ++k) {
            int nx = x + dx[k];
            int ny = y + dy[k];
            if (nx < 0 || nx >= n || ny < 0 || ny >= m) {
                perimeter++;
            }
            else if (field[nx][ny] != region.ch) {
                perimeter++;
            }
        }
    }
    return perimeter;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    ifstream fin("input.txt");
    if (!fin) {
        cerr << "Error while opening input file\n";
        return 1;
    }
    vector<vector<char>> field = readMatrix(fin);
    vector<Region> regions = findRegions(field);
    int sum = 0;
    for (auto& r : regions) {
        sum += calcArea(r) * calcCorners(r, field);
    }
    cout << sum;
    return 0;
}
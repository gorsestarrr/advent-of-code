#include <bits/stdc++.h>

using ll = long long;
using ull = unsigned long long;
using namespace std;

enum class MoveType {
    UP, RIGHT, DOWN, LEFT
};

struct Move {
    MoveType type;
    int dx;
    int dy;
};

pair<vector<vector<char>>, vector<Move>> parseMap(string filename) {
    ifstream fin(filename);
    if (!fin) {
        cerr << "Broken file" << endl;
        throw;
    }

    vector<vector<char>> map;
    vector<Move> moves;

    string str;
    while (getline(fin, str) && !str.empty()) {
        vector<char> line;
        for (char c : str) {
            line.push_back(c);
        }
        map.push_back(line);
    }

    while (getline(fin, str)) {
        for (char c : str) {
            switch (c) {
                case '^':
                    moves.push_back({MoveType::UP, 0, -1});
                    break;
                case '>':
                    moves.push_back({MoveType::RIGHT, 1, 0});
                    break;
                case 'v':
                    moves.push_back({MoveType::DOWN, 0, 1});
                    break;
                case '<':
                    moves.push_back({MoveType::LEFT, -1, 0});
                    break;
                default:
                    break;
            }
        }
    }
    return {map, moves};
}

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

pair<int, int> getRobotPosition(const vector<vector<char>>& map) {
    int n = map.size();
    int m = map[0].size();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (map[i][j] == '@') {
                return {j, i};
            }
        }
    }
}

vector<pair<int, int>> getBoxesPositions(const vector<vector<char>>& map) {
    int n = map.size();
    int m = map[0].size();
    vector<pair<int, int>> result;
    for (int i = 0; i < n; ++i) {
        pair<int, int> box;
        for (int j = 0; j < m; ++j) {
            if (map[i][j] == '[') {
                result.push_back({j, i});
            }
        }
    }
    return result;
}

void part1(vector<vector<char>>& map, const vector<Move>& moves) {
    auto [x, y] = getRobotPosition(map);
    for (const auto& move: moves) {
        int nx = x + move.dx;
        int ny = y + move.dy;
        if (map[ny][nx] == '#') {
            continue;
        }
        if (map[ny][nx] == '.') {
            map[y][x] = '.';
            map[ny][nx] = '@';
            x = nx;
            y = ny;
            continue;
        }
        if (map[ny][nx] == 'O') {
            int firstBlockX = nx;
            int firstBlockY = ny;
            while (map[ny][nx] == 'O') {
                nx += move.dx;
                ny += move.dy;
            }
            if (map[ny][nx] == '#') {
                continue;
            }
            swap(map[firstBlockY][firstBlockX], map[ny][nx]);
            map[y][x] = '.';
            map[firstBlockY][firstBlockX] = '@';
            x = firstBlockX;
            y = firstBlockY;
        }
    }
}

int gps1(const vector<vector<char>>& map) {
    int gps = 0;
    int n = map.size();
    int m = map[0].size();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (map[i][j] == 'O') {
                gps += 100 * i + j;
            }
        }
    }
    return gps;
}

int gps2(const vector<vector<char>>& map) {
    int gps = 0;
    int n = map.size();
    int m = map[0].size();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (map[i][j] == '[') {
                gps += 100 * i + j;
            }
        }
    }
    return gps;
}

vector<vector<char>> transform(vector<vector<char>>& map) {
    vector<vector<char>> transformed;
    int n = map.size();
    int m = map[0].size();
    for (int i = 0; i < n; ++i) {
        vector<char> newRow;
        for (int j = 0; j < m; ++j) {
            if (map[i][j] == '#' || map[i][j] == '.') {
                newRow.push_back(map[i][j]);
                newRow.push_back(map[i][j]);
            }
            else if (map[i][j] == 'O') {
                newRow.push_back('[');
                newRow.push_back(']');
            }
            else if (map[i][j] == '@') {
                newRow.push_back('@');
                newRow.push_back('.');
            }
        }
        transformed.push_back(newRow);
    }
    return transformed;
}

void moveBox(int x, int y, const Move& move, vector<vector<char>>& map) {
    int nxl = x + move.dx;
    int nxr = x + 1 + move.dx;
    int nyl = y + move.dy;
    int nyr = y + move.dy;
    map[y][x] = '.';
    map[y][x+1]='.';
    map[nyl][nxl] = '[';
    map[nyr][nxr] = ']';
}

void tryMovingBox(int x, int y, const Move& move, vector<vector<char>>& map,
    vector<pair<int,int>>& toMove,
    unordered_set<long long>& visited,
    bool& failed) {
    long long key = ((long long)y << 32) | x;
    if (visited.count(key)) return;
    visited.insert(key);
    if (move.type == MoveType::LEFT) {
        char adj = map[y][x-1];
        if (adj == '.' && !failed) {
            toMove.push_back({x, y});
            return;
        }
        if (adj == '#') {
            failed = true;
            return;
        }
        if (adj == ']') {
            tryMovingBox(x-2, y, move, map, toMove,visited, failed);
        }
        if (toMove.size() > 0 && !failed) {
            toMove.push_back({x, y});
        }
    }
    if (move.type == MoveType::RIGHT) {
        char adj = map[y][x+2];
        if (adj == '.' && !failed) {
            toMove.push_back({x, y});
            return;
        }
        if (adj == '#') {
            failed = true;
            return;
        }
        if (adj == '[') {
            tryMovingBox(x+2, y, move, map, toMove, visited, failed);
        }
        if (toMove.size() > 0 && !failed) {
            toMove.push_back({x, y});
        }
    }
    if (move.type == MoveType::UP) {
        char adj1 = map[y-1][x];
        char adj2 = map[y-1][x+1];
        if (adj1 == '.' && adj2 == '.' && !failed) {
            toMove.push_back({x, y});
            return;
        }
        if (adj1 == '#' || adj2 == '#') {
            failed = true;
            return;
        }
        if (adj1 == '[') {
            tryMovingBox(x, y - 1, move, map, toMove, visited, failed);
        }
        if (adj1 == ']') {
            tryMovingBox(x - 1, y - 1, move, map, toMove, visited, failed);
        }
        if (adj2 == '[') {
            tryMovingBox(x + 1, y - 1, move, map, toMove, visited, failed);
        }
        if (toMove.size() > 0) {
            toMove.push_back({x, y});
        }
    }
    if (move.type == MoveType::DOWN) {
        char adj1 = map[y+1][x];
        char adj2 = map[y+1][x+1];
        if (adj1 == '.' && adj2 == '.' && !failed) {
            toMove.push_back({x, y});
            return;
        }
        if (adj1 == '#' || adj2 == '#') {
            toMove.clear();
            failed = true;
            return;
        }
        if (adj1 == '[') {
            tryMovingBox(x, y + 1, move, map, toMove, visited, failed);
        }
        if (adj1 == ']') {
            tryMovingBox(x - 1, y + 1, move, map, toMove, visited, failed);
        }
        if (adj2 == '[') {
            tryMovingBox(x + 1, y + 1, move, map, toMove, visited, failed);
        }
        if (toMove.size() > 0 &&!failed) {
            toMove.push_back({x, y});
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    auto [map, moves] = parseMap("input.txt");
    map = transform(map);

    auto [x, y] = getRobotPosition(map);
    for (const auto& move: moves) {
        int nx = x + move.dx;
        int ny = y + move.dy;
        if (map[ny][nx] == '#') {
            continue;
        }
        if (map[ny][nx] == '.') {
            map[y][x] = '.';
            map[ny][nx] = '@';
            x = nx;
            y = ny;
            continue;
        }
        int boxX;
        int boxY = ny;
        if (map[ny][nx] == '[') {
            boxX = nx;
            boxY = ny;
        }
        else if (map[ny][nx] == ']') {
            boxX = nx - 1;
            boxY = ny;
        }
        vector<pair<int,int>> toMove;
        unordered_set<long long> visited;
        bool failed = false;
        tryMovingBox(boxX, boxY, move, map, toMove, visited, failed);
        if (toMove.size() > 0 && !failed) {
            for (auto& m : toMove) {
                moveBox(m.first, m.second, move, map);
            }
            map[y][x] = '.';
            map[ny][nx] = '@';
            x = nx;
            y = ny;
        }
    }
    print(map);
    cout << gps2(map);
    return 0;
}
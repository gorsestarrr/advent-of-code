#include <bits/stdc++.h>

using ll = long long;
using ull = unsigned long long;
using namespace std;

struct Pos {
    int x;
    int y;
};

struct Robot {
    Pos pos;
    Pos vel;
};

vector<Robot> parseRobots(string filename) {
    vector<Robot> moves;
    ifstream fin(filename);
    if (!fin) {
        cerr << "Error while opening input file\n";
        return {};
    }
    string line;
    while (getline(fin, line)) {
        int px, py, vx, vy;
        sscanf(line.c_str(), "p=%d,%d v=%d,%d", &px, &py, &vx, &vy);
        moves.push_back({{px, py}, {vx, vy}});
    }
    return moves;
}

int countQuadrant(int sw, int ew, int sh, int eh,  vector<vector<int>> amounts) {
    int result = 0;
    for (int i = sw; i < ew; ++i) {
        for (int j = sh; j < eh; ++j) {
            result += amounts[i][j];
        }
    }
    return result;
}

void print(const vector<vector<int>>& amounts) {
    cout << "---------------------------------------------------" << endl;
    int n = amounts.size();
    int m = amounts[0].size();
    for (int j = 0; j < m; ++j) {
        for (int i = 0; i < n; ++i) {
            if (amounts[i][j] == 0) {
                cout << ".";
            }
            else {
                cout << "*";
            }
            if (i == n - 1) {
                cout << endl;
            }
        }
    }
    cout << endl;
}

int part1(int W, int H, const vector<Robot>& robots) {
    vector<vector<int>> amounts(W, vector<int>(H, 0));
    for (const auto& robot: robots) {
      amounts[robot.pos.x][robot.pos.y]++;
    }
    int q1 = countQuadrant(0, W / 2, 0, H / 2, amounts);
    int q2 = countQuadrant(W / 2 + 1, W, 0, H / 2, amounts);
    int q3 = countQuadrant(0, W / 2, H / 2 + 1, H, amounts);
    int q4 = countQuadrant(W / 2 + 1, W, H / 2 + 1, H, amounts);
    return  q1 * q2 * q3 * q4;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    vector<Robot> robots = parseRobots("input.txt");

    const int W = 101;
    const int H = 103;
    const int seconds = 1000;

    for (int i = 0; i < seconds; ++i) {
        for (auto& robot: robots) {
            int nx = (robot.pos.x + robot.vel.x + W) % W;
            int ny = (robot.pos.y + robot.vel.y + H) % H;
            robot.pos.x = nx;
            robot.pos.y = ny;
        }
        vector<vector<int>> amounts(W, vector<int>(H, 0));
        for (const auto& robot: robots) {
            amounts[robot.pos.x][robot.pos.y]++;
        }
        print(amounts);
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    return 0;
}
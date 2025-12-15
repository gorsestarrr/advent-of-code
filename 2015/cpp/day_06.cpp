#include <bits/stdc++.h>

using ll = long long;
using ull = unsigned long long;
using namespace std;

struct Point {
    int x;
    int y;
};

struct Command {
    string action;
    Point from;
    Point to;
};

void setLight(vector<vector<bool>>& grid, Command command, bool value) {
    for (int y = command.from.y; y <= command.to.y; ++y) {
        for (int x = command.from.x; x <= command.to.x; ++x) {
            grid[x][y] = value;
        }
    }
}

void changeLight(vector<vector<bool>>& grid, Command command) {
    for (int y = command.from.y; y <= command.to.y; ++y) {
        for (int x = command.from.x; x <= command.to.x; ++x) {
            grid[x][y] = !grid[x][y];
        }
    }
}

void setBrightness(vector<vector<int>>& grid, Command command, int dvalue) {
    for (int y = command.from.y; y <= command.to.y; ++y) {
        for (int x = command.from.x; x <= command.to.x; ++x) {
            grid[x][y] += dvalue;
            if (grid[x][y] < 0) {
                grid[x][y] = 0;
            }
        }
    }
}

string trim(std::string& s) {
    auto not_space = [](unsigned char c) {
        return !std::isspace(c);
    };

    s.erase(s.begin(), std::find_if(s.begin(), s.end(), not_space));
    s.erase(std::find_if(s.rbegin(), s.rend(), not_space).base(), s.end());
    return s;
}

int part1(const vector<Command>& commands) {
    vector<vector<bool>> grid(1000, vector<bool>(1000, false));
    for (Command command : commands) {
        if (trim(command.action) == "turn on") {
            setLight(grid, command, true);
        }
        else if (trim(command.action) == "turn off") {
            setLight(grid, command, false);
        }
        else {
            changeLight(grid, command);
        }
    }
    int cnt = 0;
    for (const auto& row : grid) {
        for (bool v : row) {
            if (v) ++cnt;
        }
    }
    return cnt;
}

int part2(const vector<Command>& commands) {
    vector<vector<int>> grid(1000, vector<int>(1000, 0));
    for (Command command : commands) {
        if (trim(command.action) == "turn on") {
            setBrightness(grid, command, 1);
        }
        else if (trim(command.action) == "turn off") {
            setBrightness(grid, command, -1);
        }
        else {
            setBrightness(grid, command, 2);
        }
    }
    int cnt = 0;
    for (const auto& row : grid) {
        for (int v : row) {
            cnt += v;
        }
    }
    return cnt;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    ifstream fin("input.txt");
    string str;
    vector<Command> commands;
    while (getline(fin, str)) {
        char action[32];
        int fromX, fromY, toX, toY;
        sscanf(str.c_str(),
               "%31[^0-9]%d,%d %*s %d,%d", action, &fromX, &fromY, &toX, &toY);
        commands.push_back({action, {fromX, fromY}, {toX, toY}});
    }
    cout << part1(commands) << endl;
    cout << part2(commands) << endl;
    return 0;
}
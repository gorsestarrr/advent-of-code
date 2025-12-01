#include <bits/stdc++.h>

using ll = long long;
using ull = unsigned long long;
using namespace std;

struct Move {
    char direction;
    int step;
};

int norm(int x) {
    x %= 100;
    if (x < 0) x += 100;
    return x;
}

int part1(const vector<Move>& moves, int current) {
    int password = 0;
    for (auto& move : moves) {
        int partial = move.step % 100;
        if (move.direction == 'R') {
            int raw_end = current + partial;
            current = norm(raw_end);
        }
        else {
            int raw_end = current - partial;
            current = norm(raw_end);
        }
        if (current == 0) {
            password++;
        }
    }
    return password;
}

int part2(const vector<Move>& moves, int current) {
    int password = 0;
    for (auto& move : moves) {
        int old = current;
        password += move.step / 100;
        int partial = move.step % 100;
        if (move.direction == 'R') {
            int raw_end = old + partial;
            if (old < 100 && raw_end > 100) {
                password++;
            }
            current = norm(raw_end);
        }
        else {
            int raw_end = old - partial;
            if (old > 0 && raw_end < 0) {
                password++;
            }
            current = norm(raw_end);
        }
        if (current == 0) {
            password++;
        }
    }
    return password;
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
    vector<Move> moves;
    while (getline(fin, line)) {
        char direction;
        int step;
        sscanf(line.c_str(), "%c%d", &direction, &step);
        moves.push_back({direction, step});
    }

    cout << part1(moves, 50) << endl;
    cout << part2(moves, 50) << endl;

    return 0;
}
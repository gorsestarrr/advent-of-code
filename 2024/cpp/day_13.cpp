#include <bits/stdc++.h>
#include <cmath>
#define ll long long
using namespace std;

struct Puzzle {
    ll ax, ay;
    ll bx, by;
    ll px, py;
};

struct PuzzleResult {
    bool hasSolution;
    pair<ll, ll> solution;
};

bool parseButtonLine(const std::string& line, ll& x, ll& y) {
    return sscanf(line.c_str(),
                       "Button %*c: X+%lld, Y+%lld",
                       &x, &y) == 2;
}

bool parsePrizeLine(const std::string& line, ll& x, ll& y) {
    return sscanf(line.c_str(),
                       "Prize: X=%lld, Y=%lld",
                       &x, &y) == 2;
}

vector<Puzzle> parseFile(const std::string& filename) {
    ifstream in(filename);
    vector<Puzzle> puzzles;

    if (!in) {
        std::cerr << "Cannot open file: " << filename << std::endl;
        return puzzles;
    }

    string lineA, lineB, lineP;
    while (true) {
        if (!getline(in, lineA)) break;
        if (lineA.empty()) continue;
        if (!getline(in, lineB)) break;
        if (!getline(in, lineP)) break;
        Puzzle p{};
        if (!parseButtonLine(lineA, p.ax, p.ay)) {
            continue;
        }
        if (!parseButtonLine(lineB, p.bx, p.by)) {
            continue;
        }
        if (!parsePrizeLine(lineP, p.px, p.py)) {
            continue;
        }
        puzzles.push_back(p);
    }
    return puzzles;
}

PuzzleResult solve(Puzzle puzzle) {
    const ll a1 = puzzle.ax, b1 = puzzle.bx, c1 = puzzle.px + 10000000000000;
    const ll a2 = puzzle.ay, b2 = puzzle.by, c2 = puzzle.py + 10000000000000;
    ll D  = a1*b2 - a2*b1;
    ll Dx = c1*b2 - c2*b1;
    ll Dy = a1*c2 - a2*c1;
    PuzzleResult result;
    if (D != 0) {
        long double A = static_cast<long double>(Dx) / D;
        long double B = static_cast<long double>(Dy) / D;
        result.hasSolution = (A - static_cast<ll>(A) == 0) && (B - static_cast<ll>(B) == 0);
        result.solution = {static_cast<ll>(A), static_cast<ll>(B)};
    }
    else {
        result.hasSolution = false;
    }
    return result;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    vector<Puzzle> puzzles = parseFile("input.txt");
    ll tokens = 0;
    for (const auto& p: puzzles) {
        PuzzleResult result = solve(p);
        if (result.hasSolution) {
            tokens += result.solution.first * 3;
            tokens += result.solution.second * 1;
        }
    }
    cout << tokens;
    return 0;
}
#include <bits/stdc++.h>

using namespace std;

struct Puzzle {
    vector<bool> lamps;
    vector<vector<int>> buttons;
    vector<int> joltage;
};

Puzzle parsePuzzle(string s) {
    vector<bool> lamps;
    vector<vector<int>> buttons;
    vector<int> joltage;

    enum Mode { NONE, LAMPS, BUTTONS, JOLTAGE };
    Mode mode = NONE;

    string buffer;

    for (char c : s) {
        if (c == '[') {
            mode = LAMPS;
            buffer.clear();
            continue;
        }
        if (c == '(') {
            mode = BUTTONS;
            buffer.clear();
            continue;
        }
        if (c == '{') {
            mode = JOLTAGE;
            buffer.clear();
            continue;
        }
        if (c == ']' || c == ')' || c == '}') {
            if (mode == LAMPS) {
                for (char x : buffer) {
                    lamps.push_back(x == '#');
                }
            }
            else if (mode == BUTTONS) {
                vector<int> nums;
                string num;
                stringstream ss(buffer);
                while (getline(ss, num, ',')) {
                    nums.push_back(stoi(num));
                }
                buttons.push_back(nums);
            }
            else if (mode == JOLTAGE) {
                string num;
                stringstream ss(buffer);
                while (getline(ss, num, ',')) {
                    joltage.push_back(stoi(num));
                }
            }
            mode = NONE;
            continue;
        }
        if (mode != NONE) buffer += c;
    }
    return {lamps, buttons, joltage};
}

int solvePuzzle(const Puzzle& puzzle) {
    int n = puzzle.buttons.size();
    for (int i = 1; i <=n; ++i) {
        vector<bool> mask(n, false);
        fill(mask.begin(), mask.begin() + i, true);
        do {
            vector<vector<int>> group;
            for (int i = 0; i < n; i++) {
                if (mask[i]) {
                    group.push_back(puzzle.buttons[i]);
                }
            }
            vector<bool> lamps(puzzle.lamps.size(), false);
            for (auto &vec : group) {
                for (int lamp : vec) {
                    lamps[lamp] = !lamps[lamp];
                }
                if (lamps == puzzle.lamps) {
                    return group.size();
                }
            }
        } while (prev_permutation(mask.begin(), mask.end()));
    }
}

int part1(const vector<Puzzle>& puzzles) {
    int sum = 0;
    for (auto& puzzle : puzzles) {
        sum += solvePuzzle(puzzle);
    }
    return sum;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    ifstream fin("input.txt");
    if (!fin) {
        cerr << "Broken file" << endl;
        throw;
    }
    vector<Puzzle> puzzles;
    string str;
    while (getline(fin, str)) {
        puzzles.push_back(parsePuzzle(str));
    }
    cout << part1(puzzles);
}

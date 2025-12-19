#include <bits/stdc++.h>

using ll = long long;
using ull = unsigned long long;
using namespace std;

struct Sue {
    int id;
    map<string, int> props;
};

vector<string> split(const string& s, const string& delim) {
    vector<string> result;
    size_t pos = 0, prev = 0;
    while ((pos = s.find(delim, prev)) != string::npos) {
        result.push_back(s.substr(prev, pos - prev));
        prev = pos + delim.size();
    }
    result.push_back(s.substr(prev));
    return result;
}

Sue parseSue(const std::string& line) {
    Sue sue;

    auto pos = line.find(": ");
    sue.id = stoi(line.substr(4, pos - 4));

    std::string tail = line.substr(pos + 2);
    auto items = split(tail, ", ");

    for (const auto& item : items) {
        auto kv = split(item, ": ");
        sue.props[kv[0]] = stoi(kv[1]);
    }

    return sue;
}

unordered_map<string, int> getTape() {
    unordered_map<string, int> tape;
    tape.insert({"children", 3});
    tape.insert({"cats", 7});
    tape.insert({"samoyeds", 2});
    tape.insert({"pomeranians", 3});
    tape.insert({"akitas", 0});
    tape.insert({"vizslas", 0});
    tape.insert({"goldfish", 5});
    tape.insert({"trees", 3});
    tape.insert({"cars", 2});
    tape.insert({"perfumes", 1});
    return tape;
}

bool checkKey(const string& key, int actual, int ref, bool isPart2) {
    if (isPart2) {
        if (key == "cats" || key == "trees") {
            return actual > ref;
        }
        if (key == "pomeranians" || key == "goldfish") {
            return actual < ref;
        }
    }
    return actual == ref;
}

int solve(const vector<Sue>& sues, const unordered_map<string, int>& tape, int isPart2) {
    for (const auto& sue :sues) {
        auto [id, props] = sue;
        int counter = 0;
        for (auto& [key, value] : props) {
            if (tape.count(key) && !checkKey(key, value, tape.at(key), isPart2)) {
                break;
            }
            counter++;
        }
        if (counter == props.size()) {
            return id;
        }
    }
    return -1;
}

int part1(const vector<Sue>& sues, const unordered_map<string, int>& tape) {
    return solve(sues, tape, false);
}

int part2(const vector<Sue>& sues, const unordered_map<string, int>& tape) {
    return solve(sues, tape, true);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    ifstream fin ("input.txt");
    string line;
    vector<Sue> sues;
    while (getline(fin, line)) {
        sues.push_back(parseSue(line));
    }
    cout << part1(sues, getTape()) << endl;
    cout << part2(sues, getTape()) << endl;
    return 0;
}
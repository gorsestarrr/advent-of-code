#include <bits/stdc++.h>

using ll = long long;
using ull = unsigned long long;
using namespace std;

vector<string> splitLine(const string& s, const string& delim) {
    vector<string> result;
    size_t pos = 0, prev = 0;
    while ((pos = s.find(delim, prev)) != string::npos) {
        result.push_back(s.substr(prev, pos - prev));
        prev = pos + delim.size();
    }
    result.push_back(s.substr(prev));
    return result;
}

string trim(std::string& s) {
    auto not_space = [](unsigned char c) {
        return !std::isspace(c);
    };

    s.erase(s.begin(), std::find_if(s.begin(), s.end(), not_space));
    s.erase(std::find_if(s.rbegin(), s.rend(), not_space).base(), s.end());
    return s;
}

pair<unordered_map<string, vector<string>>, string> parseInput(string filename) {
    pair<unordered_map<string, vector<string>>, string> result;
    unordered_map<string, vector<string>> mp;
    string molecule;
    ifstream fin(filename);
    string line;
    while (getline(fin, line)) {
        if (line.empty()) {
            break;
        }
        auto split = splitLine(line, "=>");
        string key = trim(split[0]);
        string value = trim(split[1]);
        mp[key].push_back(value);
    }
    while (getline(fin, line)) {
        molecule = line;
    }
    return make_pair(mp, molecule);
}

int countOccurrences(const string& text, const string& sub) {
    if (sub.empty()) {
        return 0;
    }
    int count = 0;
    size_t pos = 0;
    while ((pos = text.find(sub, pos)) != string::npos) {
        ++count;
        pos += sub.length();
    }
    return count;
}

bool replaceNth(string& text, const string& target, const string& replacement, int index) {
    if (target.empty() || index < 0) {
        return false;
    }
    size_t pos = 0;
    int count = 0;
    while ((pos = text.find(target, pos)) != string::npos) {
        if (count == index) {
            text.replace(pos, target.length(), replacement);
            return true;
        }
        pos += target.length();
        count++;
    }
    return false;
}

int part1(unordered_map<string, vector<string>> mp, string molecule) {
    unordered_set<string> set;
    for (const auto& [key, values] : mp) {
        int count = countOccurrences(molecule, key);
        for (int i = 0; i < count; i++) {
            for (string val: values) {
                string copy(molecule);
                replaceNth(copy, key, val, i);
                set.insert(copy);
            }
        }
    }
    return set.size();
}

pair<vector<pair<string, string>>, string> parseInput2(const string& filename) {
    ifstream fin(filename);
    vector<pair<string, string>> rules;
    string molecule;
    string line;
    bool readingRules = true;
    while (getline(fin, line)) {
        if (line.empty()) {
            readingRules = false;
            continue;
        }
        if (readingRules) {
            size_t pos = line.find(" => ");
            if (pos != string::npos) {
                string left = line.substr(0, pos);
                string right = line.substr(pos + 4);
                rules.emplace_back(left, right);
            }
        } else {
            molecule = line;
            break;
        }
    }
    return {rules, molecule};
}

int countSubstr(const string& str, const string& sub) {
    int count = 0;
    size_t pos = 0;

    while ((pos = str.find(sub, pos)) != string::npos) {
        ++count;
        pos += sub.length();
    }

    return count;
}

int part2(string molecule) {
    int countUpper = 0;
    for (char c : molecule)
        if (isupper(c))
            countUpper++;

    int result =
        countUpper
        - countSubstr(molecule, "Rn")
        - countSubstr(molecule, "Ar")
        - 2 * countSubstr(molecule, "Y")
        - 1;
    return result;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    const auto pair = parseInput("input.txt");
    cout << part1(pair.first, pair.second) << endl;
    cout << part2(pair.second);
    return 0;
}
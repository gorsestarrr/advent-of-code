#include <bits/stdc++.h>

using ll = long long;
using ull = unsigned long long;
using namespace std;

int part1(const vector<string>& literals) {
    int symbols = 0;
    int memory = 0;
    for (auto& l : literals) {
        symbols += l.size();
        int mem = -2;
        for (int i = 0; i < l.size();++i) {
            if (l[i] == '\\') {
                if (i + 1 < l.size()) {
                    char next = l[i + 1];
                    if (next == '\\' || next == '\"') {
                        i++;
                    }
                    else if (next == 'x') {
                        int step = 0;
                        if (i + 2 < l.size()) {
                            if (isxdigit((unsigned char)l[i+2])) {
                                step++;
                            }
                        }
                        if (i + 3 < l.size()) {
                            if (isxdigit((unsigned char)l[i+3])) {
                                step++;
                            }
                        }
                        i++;
                        i += step;
                    }
                }
            }
            mem++;
        }
        memory += mem;
    }
    return symbols - memory;
}

int part2(const vector<string>& literals) {
    int symbols = 0;
    int memory = 0;
    for (auto& l : literals) {
        symbols += l.size();
        int specialSymb = 0;
        for (int i = 0; i < l.size();++i) {
            if (l[i] == '\"' || l[i] == '\\') {
                specialSymb++;
            }
        }
        memory += specialSymb * 2 + l.size() - specialSymb + 2;;
    }
    return memory - symbols;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    ifstream fin("input.txt");
    string str;
    vector<string> literals;
    while (getline(fin, str)) {
        literals.push_back(str);
    }
    cout << part2(literals) << endl;
    return 0;
}
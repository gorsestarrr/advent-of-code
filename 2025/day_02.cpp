#include <bits/stdc++.h>

using ll = long long;
using ull = unsigned long long;
using namespace std;

struct Range {
    ll start;
    ll end;
};

ll checkNumber(ll number) {
    string s = to_string(number);
    ll n = s.size();
    if (n % 2 != 0) {
        return 0;
    }
    for (ll i = 0; i < n / 2; i++) {
        if (s[i] != s[n / 2 + i]) {
            return 0;
        }
    }
    return number;
}

ll part1(const vector<Range>& ranges) {
    ll result = 0;
    for (auto& range: ranges) {
        for (ll i = range.start; i <= range.end; ++i) {
            result += checkNumber(i);
        }
    }
    return result;
}

bool isRepeated2(const string& s) {
    string t = s + s;
    return t.find(s, 1) != string::npos && t.find(s, 1) < s.size();
}

ll part2(const vector<Range>& ranges) {
    ll result = 0;
    for (auto& range : ranges) {
        for (ll i = range.start; i <= range.end; ++i) {
            string s = to_string(i);
            if (isRepeated2(s)) {
                result += i;
            }
        }
    }
    return result;
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
    getline(fin, line);
    vector<Range> ranges;
    stringstream ss(line);
    string token;
    while (getline(ss, token, ',')) {
        if (token.empty()) continue;
        auto dashPos = token.find('-');
        if (dashPos == std::string::npos) continue;
        ll start = std::stoll(token.substr(0, dashPos));
        ll end   = std::stoll(token.substr(dashPos + 1));
        ranges.push_back({start, end});
    }
    cout << part2(ranges);
    return 0;
}
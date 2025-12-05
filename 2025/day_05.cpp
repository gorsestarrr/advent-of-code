#include <bits/stdc++.h>

using ll = long long;
using ull = unsigned long long;
using namespace std;

struct Range {
    ull start;
    ull end;
};

ull part1(const vector<Range>& ranges, const vector<ull>& products) {
    ull fresh = 0;
    for (auto& product: products) {
        for (auto& range : ranges) {
            if (product >= range.start && product <= range.end) {
                fresh++;
                break;
            }
        }
    }
    return fresh;
}

ull part2(vector<Range> ranges) {
    sort(ranges.begin(), ranges.end(),
    [](const Range& a, const Range& b) {
        return a.start < b.start;
    });
    ull prevEnd = 0;
    ull result = 0;
    for (auto& range: ranges) {
        if (range.start > prevEnd) {
            result += range.end - range.start + 1;
            prevEnd = range.end;
        }
        else if (range.start < prevEnd && range.end > prevEnd) {
            result += range.end - prevEnd;
            prevEnd = range.end;
        }
    }
    return result;
}

ull part2Dummy(vector<Range> ranges) {
    unordered_set<ull> set;
    for (auto& range : ranges) {
        for (ull i = range.start; i <= range.end; ++i) {
            set.insert(i);
        }
    }
    return set.size();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    ifstream fin("input.txt");
    if (!fin) {
        cerr << "Broken file" << endl;
        throw;
    }
    vector<Range> ranges;
    string line;
    while (getline(fin, line)) {
        if (line.empty()) {
            break;
        }
        ull start;
        ull end;
        sscanf(line.c_str(), "%lld-%lld", &start, &end);
        ranges.push_back({start, end});
    }
    vector<ull> products;
    while (getline(fin, line)) {
        ull value;
        sscanf(line.c_str(), "%lld", &value);
        products.push_back(value);
    }
    cout << part2(ranges) << endl;
    return 0;
}
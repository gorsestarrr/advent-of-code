#include <bits/stdc++.h>
#include <cmath>
#define ull unsigned long long
using namespace std;

ull blink(ull stone, int depth, map<pair<ull, int>, ull>& dp) {
    if (dp.count({stone, depth})) {
        return dp[{stone, depth}];
    }
    if (stone == -1) {
        return 0;
    }
    if (depth == 0) {
        return 1;
    }
    ull left, right = -1;
    ull digits = (ull)(floor(log10(fabsl((long double)stone))) + 1);
    if (stone == 0) {
        left = 1;
    }
    else if (digits % 2 == 0) {
        ull divisor = (ull)pow(10, digits / 2);
        left = stone / divisor;
        right = stone % divisor;
    }
    else {
        left = stone * 2024;
    }
    dp[{stone, depth}] = blink(left, depth - 1, dp) + blink(right, depth - 1, dp);
    return dp[{stone, depth}];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    ifstream fin("input.txt");
    if (!fin) {
        cerr << "Error while opening input file\n";
        return 1;
    }
    vector<ull> stones (
        (std::istream_iterator<ull>(fin)),
        (std::istream_iterator<ull>())
    );
    ull count = 0;
    map<pair<ull, int>, ull> dp;
    for (auto& stone : stones) {
        count += blink(stone, 75, dp);
    }
    cout << count;
    return 0;
}
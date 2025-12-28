#include <bits/stdc++.h>

using ll = long long;
using ull = unsigned long long;
using namespace std;

int part1(int num) {
    const int capacity = 1'000'000;
    vector<int> dp(capacity + 1, 0);
    for (int i = 1; i <= capacity; i++) {
        for (int house = i; house <= capacity; house += i) {
            dp[house] += i * 10;
        }
    }
    for (int i = 1; i <= capacity; i++) {
        if (dp[i] >= num) {
            return i;
        }
    }
    return -1;
}


ll part2(int num) {
    ll capacity = 100'000'000;
    vector<ll> dp(capacity + 1, 0);
    for (ll i = 1; i < capacity / 50; i++) {
        for (int k = 1; k <= 50; k++) {
            ll idx = i * k;
            dp[idx] += i * 11;
        }
    }
    for (ll i = 1; i < capacity; i++) {
        if (dp[i] >= num) {
            return i;
        }
    }
    return -1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << part1(29000000) << endl;
    cout << part2(29000000);
    return 0;
}
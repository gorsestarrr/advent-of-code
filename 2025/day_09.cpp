#include <bits/stdc++.h>

using ll = long long;
using ull = unsigned long long;
using namespace std;

struct Tile {
    ll x, y;
};

ll area(const Tile& first, const Tile& second) {
    return (abs(first.x - second.x ) + 1) * ( abs(first.y - second.y) + 1 );
}

ll part1(const vector<Tile>& tiles) {
    int n = tiles.size();
    ll maxArea = -1;
    ll at = 0;
    for (int i = 0; i < n  - 1; ++i) {
        for (int j = i + 1; j < n; ++j) {
            Tile first = tiles[i];
            Tile second = tiles[j];
            maxArea = max(maxArea, area(first, second));
            at++;
        }
    }
    cout << "At = " << at << endl;
    return maxArea;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    ifstream fin("input.txt");
    if (!fin) {
        cerr << "Broken file" << endl;
        throw;
    }
    string str;
    vector<Tile> tiles;
    while (getline(fin, str)) {
        ll x,y;
        sscanf(str.c_str(), "%lld,%lld", &x, &y);
        tiles.push_back({x, y});
    }
    cout << part1(tiles);
    return 0;
}
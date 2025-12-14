#include <bits/stdc++.h>

using ll = long long;
using ull = unsigned long long;
using namespace std;

struct Box {
    int l;
    int w;
    int h;
};

int part1(const vector<Box>& boxes) {
    int total = 0;
    for (Box box : boxes) {
        int wl = box.l * box.w;
        int wh = box.w * box.h;
        int hl = box.h * box.l;
        total += 2 * (wl + wh + hl);
        total += min({wl, wh, hl});
    }
    return total;
}

int part2(const vector<Box>& boxes) {
    int total = 0;
    for (Box box : boxes) {
        int sides[3] = { box.l, box.w, box.h };
        sort(sides, sides + 3);
        total += 2 * (sides[0] + sides[1]) + box.l * box.w * box.h;
    }
    return total;
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
    vector<Box> boxes;
    while (getline(fin, str)) {
        int l,w,h;
        sscanf(str.c_str(), "%dx%dx%d", &l, &w, &h);
        boxes.push_back({l, w, h});
    }
    cout << part1(boxes) << endl;
    cout << part2(boxes) << endl;
    return 0;
}
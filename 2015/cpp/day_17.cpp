#include <bits/stdc++.h>

using ll = long long;
using ull = unsigned long long;
using namespace std;

int solveP1(const vector<int>& containers, int ptr, int sum) {
    constexpr int target = 150;
    if (sum == target) {
        return 1;
    }
    if (sum > target || ptr == containers.size()) {
        return 0;
    }
    int skip = solveP1(containers, ptr + 1, sum);
    int take = solveP1(containers, ptr + 1, sum + containers[ptr]);
    return skip + take;
}

void solveP2(const vector<int>& containers, int ptr, int sum, int takenCount, vector<int>& counts) {
    constexpr int target = 150;
    if (sum == target) {
        counts.push_back(takenCount);
        return;
    }
    if (sum > target || ptr == containers.size()) {
        return;
    }
    solveP2(containers, ptr + 1, sum, takenCount, counts);
    solveP2(containers, ptr + 1, sum + containers[ptr], takenCount + 1, counts);
}


int part1(const vector<int>& containers) {
    return solveP1(containers, 0, 0);
}

int part2(const vector<int>& containers) {
    vector<int> counts;
    solveP2(containers, 0, 0, 0, counts);
    int minCount = *min_element(counts.begin(), counts.end());
    return count(counts.begin(), counts.end(), minCount);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    ifstream fin("input.txt");
    string line;
    vector<int> containers;
    while (getline(fin, line)) {
        containers.push_back(stoi(line));
    }
    cout << part1(containers) << endl;
    cout << part2(containers) << endl;
    return 0;
}
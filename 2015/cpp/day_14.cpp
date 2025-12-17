#include <bits/stdc++.h>

using ll = long long;
using ull = unsigned long long;
using namespace std;

int part1(const vector<tuple<int, int, int>>& vec, int seconds) {
    int maxDistance = 0;
    for (const auto& [speed, flyTime, restTime] : vec) {
        int totalTime = flyTime + restTime;
        int cycles = seconds / totalTime;
        int remainder = seconds % totalTime;
        int distance = speed * (cycles * flyTime + min(remainder, flyTime));
        maxDistance = max(maxDistance, distance);
    }
    return maxDistance;
}

int part2(const vector<tuple<int, int, int>>& vec, int seconds) {
    int n = vec.size();
    vector<tuple<bool, int>> state(n);
    vector<int> distance (n, 0);
    vector<int> points (n, 0);
    for (int i = 0; i < n; i++) {
        state[i] = {true, get<1>(vec[i])};
    }
    for (int sec = 0; sec < seconds; sec++) {
        for (int i = 0; i < n; i++) {
            auto& [speed, flyTime, restTime] = vec[i];
            auto& [moving, counter] = state[i];
            if (moving) {
                distance[i] += speed;
            }
            counter--;
            if (counter == 0) {
                moving = !moving;
                counter = moving ? flyTime : restTime;
            }
        }
        int best = *max_element(distance.begin(), distance.end());
        for (int i = 0; i < n; i++) {
            if (distance[i] == best) {
                points[i]++;
            }
        }
    }
    return *max_element(points.begin(), points.end());
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    ifstream fin("input.txt");
    string str;
    vector<tuple<int,int,int>> vector;
    while (getline(fin, str)) {
        char name[32];
        int speed, fly, rest;
        sscanf(str.c_str(), "%31s can fly %d km/s for %d seconds, but then must rest for %d seconds.", name, &speed, &fly, &rest);
        string name_s(name);
        vector.push_back ({speed, fly, rest});
    }
    cout << part1(vector, 2503) << endl;
    cout << part2(vector, 2503);
    return 0;
}
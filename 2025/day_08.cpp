#include <bits/stdc++.h>

using ll = long long;
using ull = unsigned long long;
using namespace std;

struct Vec3 {
    ll x, y, z;
    Vec3() : x(0), y(0), z(0) {}
    Vec3(int x, int y, int z) : x(x), y(y), z(z) {}

    static long double distance(const Vec3& a, const Vec3& b) {
        long double dx = (long double)a.x - b.x;
        long double dy = (long double)a.y - b.y;
        long double dz = (long double)a.z - b.z;
        return sqrt(dx*dx + dy*dy + dz*dz);
    }
};

struct Box {
    int id;
    Vec3 position;
};

struct Connection {
    double distance;
    Box first;
    Box second;
};

void dfs(int v, const vector<unordered_set<int>>& graph, vector<char>& visited, vector<int>& comp) {
    visited[v] = true;
    comp.push_back(v);
    for (int to : graph[v]) {
        if (!visited[to]) {
            dfs(to, graph, visited, comp);
        }
    }
}

vector<vector<int>> findComponents(const vector<unordered_set<int>>& graph) {
    int n = graph.size();
    vector<char> visited(n, false);
    vector<vector<int>> components;

    for (int start = 0; start < n; ++start) {
        if (!visited[start]) {
            components.emplace_back();
            dfs(start, graph, visited, components.back());
        }
    }

    return components;
}

int part1(const vector<Box>& boxes, int wires) {
    vector<Connection> connections;
    int n = boxes.size();
    for (int i = 0; i < n - 1; ++i) {
        for (int j = i + 1; j < n; ++j) {
            double distance = Vec3::distance(boxes[i].position, boxes[j].position);
            connections.push_back({distance, boxes[i], boxes[j]});
        }
    }
    sort(connections.begin(), connections.end(),
          [](const Connection& a, const Connection& b) {
              return a.distance < b.distance;
          });
    vector<unordered_set<int>> graph;
    graph.resize(n);
    for (int i = 0; i < wires; ++i) {
        Connection b = connections[i];
        graph[b.first.id].insert(b.second.id);
        graph[b.second.id].insert(b.first.id);
    }
    auto components = findComponents(graph);
    sort(components.begin(), components.end(),
          [](const vector<int>& a, const vector<int>& b) {
              return a.size() > b.size();
          });
    return components[0].size() * components[1].size() * components[2].size();
}

ll part2(const vector<Box>& boxes) {
    vector<Connection> connections;
    int n = boxes.size();
    for (int i = 0; i < n - 1; ++i) {
        for (int j = i + 1; j < n; ++j) {
            double distance = Vec3::distance(boxes[i].position, boxes[j].position);
            connections.push_back({distance, boxes[i], boxes[j]});
        }
    }
    sort(connections.begin(), connections.end(),
          [](const Connection& a, const Connection& b) {
              return a.distance < b.distance;
          });
    vector<unordered_set<int>> graph;
    graph.resize(n);
    for (int i = 0;;++i) {
        Connection b = connections[i];
        graph[b.first.id].insert(b.second.id);
        graph[b.second.id].insert(b.first.id);
        if (findComponents(graph).size() == 1) {
            return b.first.position.x * b.second.position.x;
        }
    }
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
    int id = 0;
    while (getline(fin, str)) {
        ll x,y,z;
        sscanf(str.c_str(), "%lld,%lld,%lld", &x, &y, &z);
        boxes.push_back({id++, Vec3(x,y,z)});
    }
    cout << part1(boxes, 1000) << endl;
    cout << part2(boxes);
    return 0;
}
#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> readMatrix(istream& fin) {
    vector<vector<int>> matrix;
    string line;
    while (getline(fin, line)) {
        vector<int> row;
        for (char c : line) {
            row.push_back(c - '0');
        }
        matrix.push_back(row);
    }
    return matrix;
}

void print(const vector<vector<int>>& matrix) {
    for (const auto& row : matrix) {
        for (int num : row)
            cout << num;
        cout << "\n";
    }
}

int id (int i, int j, int cols) {
    return i * cols + j;
}

bool checkBorders(int i, int j, const vector<vector<int>>& matrix) {
    return (i >= 0 && i < matrix.size()) && (j >= 0 && j < matrix[0].size());
}

void move(int i, int j, const vector<vector<int>>& matrix, vector<vector<bool>>& visited, bool useVisited, int& score) {
    if (useVisited) {
        if (visited[i][j]) {
            return;
        }
        visited[i][j] = true;
    }
    if (matrix[i][j] == 9) {
        score++;
        return;
    }
    vector<pair<int,int>> directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    int current = matrix[i][j];
    for (auto& dir : directions) {
        int stepI = i + dir.first;
        int stepJ = j + dir.second;
        if (checkBorders(stepI, stepJ, matrix)
            && matrix[stepI][stepJ] == current + 1
        ) {
            move(stepI, stepJ, matrix, visited, useVisited, score);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    ifstream fin("input.txt");
    vector<vector<int>> matrix = readMatrix(fin);
    vector<vector<int>> vis;
    int sum = 0;
    for (size_t i = 0; i < matrix.size(); ++i) {
        for (size_t j = 0; j < matrix[i].size(); ++j) {
            if (matrix[i][j] == 0) {
                int score = 0;
                vector<vector<bool>> visited(matrix.size(), vector<bool>(matrix[i].size(), false));
                move(i, j, matrix, visited, false, score);
                sum += score;
            }
        }
    }

    cout << sum;
    return 0;
}
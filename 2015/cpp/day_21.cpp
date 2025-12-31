#include <bits/stdc++.h>

using ll = long long;
using ull = unsigned long long;
using namespace std;

struct Player {
    int health;
    int damage;
    int armor;
};

bool isFirstWinner(Player& first, Player& second) {
    int aDamage = first.damage - second.armor;
    if (aDamage <= 0) {
        aDamage = 1;
    }
    int bDamage = second.damage - first.armor;
    if (bDamage <= 0) {
        bDamage = 1;
    }
    int aRounds = ceil((double)second.health / aDamage);
    int bRounds = ceil((double)first.health / bDamage);
    return aRounds <= bRounds;
}

int part1(
    const vector<tuple<int, int, int>>& weapons,
    const vector<tuple<int, int, int>>& armor,
    const vector<tuple<int, int, int>>& rings,
    Player& boss) {

    int minPrice = INT_MAX;

    for (int w = 0; w < weapons.size(); ++w) {
        for (int a = 0; a < armor.size(); ++a) {
            for (int r1 = 0; r1 < rings.size();++r1) {
                for (int r2 = r1 + 1; r2 < rings.size(); ++r2) {
                    int totalDamage = get<1>(weapons[w]) + get<1>(rings[r1]) + get<1>(rings[r2]);
                    int totalArmor = get<2>(armor[a]) + get<2>(rings[r1]) + get<2>(rings[r2]);
                    Player me {100, totalDamage, totalArmor};
                    bool winner = isFirstWinner(me, boss);
                    if (winner) {
                        int price = get<0>(weapons[w]) + get<0>(armor[a]) + get<0>(rings[r1]) + get<0>(rings[r2]);
                        if (price < minPrice) {
                            minPrice = price;
                        }
                    }
                }
            }
        }
    }
    return minPrice;
}

int part2(
    const vector<tuple<int, int, int>>& weapons,
    const vector<tuple<int, int, int>>& armor,
    const vector<tuple<int, int, int>>& rings,
    Player& boss) {

    int maxPrice = 0;

    for (int w = 0; w < weapons.size(); ++w) {
        for (int a = 0; a < armor.size(); ++a) {
            for (int r1 = 0; r1 < rings.size();++r1) {
                for (int r2 = r1 + 1; r2 < rings.size(); ++r2) {
                    int totalDamage = get<1>(weapons[w]) + get<1>(rings[r1]) + get<1>(rings[r2]);
                    int totalArmor = get<2>(armor[a]) + get<2>(rings[r1]) + get<2>(rings[r2]);
                    Player me {100, totalDamage, totalArmor};
                    bool winner = isFirstWinner(me, boss);
                    if (!winner) {
                        int price = get<0>(weapons[w]) + get<0>(armor[a]) + get<0>(rings[r1]) + get<0>(rings[r2]);
                        if (price > maxPrice) {
                            maxPrice = price;
                        }
                    }
                }
            }
        }
    }
    return maxPrice;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    vector<tuple<int, int, int>> weapons = {{8,4,0}, {10,5,0}, {25, 6, 0}, {40, 7, 0}, {74, 8 ,0}};
    vector<tuple<int, int, int>> armor = {{13,0,1}, {31,0,2}, {53, 0, 3}, {75,0,4}, {102,0,5}, {0,0,0}};
    vector<tuple<int, int, int>> rings = {{25,1,0}, {50,2,0},{100,3,0}, {20,0,1},{40,0,2},{80,0,3}, {0,0,0}, {0,0,0}};
    Player boss {0, 0 ,0};
    cout << part1(weapons, armor, rings, boss) << endl;
    cout << part2(weapons, armor, rings, boss);
    return 0;
}
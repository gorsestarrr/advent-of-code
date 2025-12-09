#include <bits/stdc++.h>
#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/geometries/polygon.hpp>
#include <boost/geometry/geometries/box.hpp>

using ll = long long;
using ull = unsigned long long;
using namespace std;

namespace bg = boost::geometry;
using Point = bg::model::d2::point_xy<ll>;
using Polygon = bg::model::polygon<Point>;
using Box = bg::model::box<Point>;

ll area(const Point& first, const Point& second) {
    return (abs(first.x() - second.x() ) + 1) * ( abs(first.y() - second.y()) + 1 );
}

ll part1(const vector<Point>& tiles) {
    int n = tiles.size();
    ll maxArea = -1;
    for (int i = 0; i < n  - 1; ++i) {
        for (int j = i + 1; j < n; ++j) {
            Point first = tiles[i];
            Point second = tiles[j];
            maxArea = max(maxArea, area(first, second));
        }
    }
    return maxArea;
}

ll part2(const vector<Point>& tiles) {
    Polygon poly;
    for (auto &p : tiles) {
        bg::append(poly.outer(), p);
    }
    bg::correct(poly);
    int n = tiles.size();
    ll ans = - 1;
    for (int i = 0; i < n - 1; ++i) {
        for (int j = i + 1; j < n; ++j) {
            ll x1 = min(tiles[i].x(), tiles[j].x());
            ll x2 = max(tiles[i].x(), tiles[j].x());
            ll y1 = min(tiles[i].y(), tiles[j].y());
            ll y2 = max(tiles[i].y(), tiles[j].y());
            ll area = (llabs(x1 - x2) + 1) * (llabs(y1 - y2) + 1);
            Polygon rect;
            bg::append(rect.outer(), Point(x1, y1));
            bg::append(rect.outer(), Point(x1, y2));
            bg::append(rect.outer(), Point(x2, y2));
            bg::append(rect.outer(), Point(x2, y1));
            bg::append(rect.outer(), Point(x1, y1));
            bg::correct(rect);
            if (area > ans && bg::within(rect, poly)) {
                ans = area;
            }
        }
    }
    return ans;
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
    vector<Point> tiles;
    while (getline(fin, str)) {
        ll x,y;
        sscanf(str.c_str(), "%lld,%lld", &x, &y);
        tiles.push_back({x, y});
    }
    cout << part2(tiles);
    return 0;
}
#include <bits/stdc++.h>
using namespace std;

long long solve_part1(const string &s) {
    vector<long long> disk;
    int file_id = 0;

    for (int i = 0; i < (int)s.size(); i++) {
        int len = s[i] - '0';
        if (i % 2 == 0) {
            for (int k = 0; k < len; k++) disk.push_back(file_id);
            file_id++;
        } else {
            for (int k = 0; k < len; k++) disk.push_back(-1);
        }
    }

    long long L = 0;
    long long R = disk.size() - 1;

    while (L < R) {
        while (L < (long long)disk.size() && disk[L] != -1) L++;
        while (R >= 0 && disk[R] == -1) R--;

        if (L < R) {
            disk[L] = disk[R];
            disk[R] = -1;
            L++;
            R--;
        }
    }
    long long checksum = 0;
    for (long long i = 0; i < (long long)disk.size(); i++) {
        if (disk[i] != -1) checksum += i * disk[i];
    }
    return checksum;
}

struct Segment {
    long long start;
    long long length;
    long long id;
};

long long solve_part2(const string &s) {
    vector<Segment> segs;
    long long pos = 0;
    long long file_id = 0;

    for (int i = 0; i < (int)s.size(); i++) {
        long long len = s[i] - '0';
        if (len == 0) continue;
        if (i % 2 == 0) {
            segs.push_back({pos, len, file_id});
            file_id++;
        } else {
            segs.push_back({pos, len, -1});
        }
        pos += len;
    }

    long long max_file = file_id - 1;

    auto merge_free = [&]() {
        vector<Segment> t;
        for (auto &g : segs) {
            if (!t.empty() && t.back().id == -1 && g.id == -1) {
                t.back().length += g.length;
            } else {
                t.push_back(g);
            }
        }
        segs.swap(t);
    };

    for (long long fid = max_file; fid >= 0; fid--) {
        int i_file = -1;
        for (int i = 0; i < (int)segs.size(); i++) {
            if (segs[i].id == fid) {
                i_file = i;
                break;
            }
        }
        if (i_file == -1) continue;
        long long f_len = segs[i_file].length;
        int best = -1;
        for (int j = 0; j < i_file; j++) {
            if (segs[j].id == -1 && segs[j].length >= f_len) {
                best = j;
                break;
            }
        }
        if (best == -1) continue;

        long long new_start = segs[best].start;
        segs[best].length -= f_len;
        segs[best].start += f_len;

        segs.insert(segs.begin() + best,
                    {new_start, f_len, fid});

        segs[i_file + 1].id = -1;

        merge_free();
    }

    long long checksum = 0;
    for (auto &g : segs) {
        if (g.id == -1) continue;
        for (long long i = 0; i < g.length; i++) {
            long long pos = g.start + i;
            checksum += pos * g.id;
        }
    }
    return checksum;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ifstream in("input.txt");
    string s;
    in >> s;

    cout << solve_part1(s) << "\n";
    cout << solve_part2(s) << "\n";

    return 0;
}

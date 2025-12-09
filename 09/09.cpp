#include "../lib.hpp"

typedef pair<vec, vec> rect;

rect make_rect(vec v0, vec v1) {
    int x0 = min(v0[0], v1[0]), x1 = max(v0[0], v1[0]);
    int y0 = min(v0[1], v1[1]), y1 = max(v0[1], v1[1]);
    return make_pair(vec(x0, y0), vec(x1, y1));
}

bool overlap(int l1, int r1, int l2, int r2) {
    return (l1 <= r2) && (l2 <= r1);
}

bool intersect(rect &r1, rect &r2) {
    return overlap(r1.first[0], r1.second[0], r2.first[0], r2.second[0])
        && overlap(r1.first[1], r1.second[1], r2.first[1], r2.second[1]);
}

int main() {
    string s;
    vector<vec> tile;
    while (getline(cin, s)) {
        auto v = split_i(s, ",");
        tile.emplace_back(v[0], v[1]);
    }

    int n = tile.size();
    vector<rect> neg;
    for (int i = 0; i < n; i++) {
        vec v0 = tile[i], v1 = tile[(i + 1) % n], v2 = tile[(i + 2) % n];
        vec d0 = v1 - v0, d1 = v2 - v1;
        if (d0[0] * (long)d1[1] < d0[1] * (long)d1[0]) {
            // d0, d1 are counter-clockwise
            if (v0[0] == v1[0]) {
                // r0 is vertical
                if (v0[1] < v1[1]) { // DR
                    v0[0]++; v0[1]++; v1[0]++; v1[1]--; v2[0]--; v2[1]--;
                }
                else { // UL
                    v0[0]--; v0[1]--; v1[0]--; v1[1]++; v2[0]++; v2[1]++;
                }
            }
            else {
                // r0 is horizontal
                if (v0[0] < v1[0]) { // RU
                    v0[0]++; v0[1]--; v1[0]--; v1[1]--; v2[0]--; v2[1]++;
                }
                else { // LD
                    v0[0]--; v0[1]++; v1[0]++; v1[1]++; v2[0]++; v2[1]--;
                }
            }
            neg.push_back(make_rect(v0, v1));
            neg.push_back(make_rect(v1, v2));
        }
    }

    long result = 0, result2 = 0;
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++) {
            rect r = make_rect(tile[i], tile[j]);
            bool good = true;
            for (rect &t : neg)
                if (intersect(r, t)) {
                    good = false;
                    break;
                }

            vec d = r.second - r.first;
            long area = (d[0] + 1l) * (d[1] + 1l);
            result = max(result, area);
            if (good)
                result2 = max(result2, area);
        }
    cout << result << ' ' << result2 << endl;

    return 0;
}


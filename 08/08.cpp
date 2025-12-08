#include "../lib.hpp"

struct dist {
    long d;
    int i;
    int j;
};

vector<int> parent, sz;

int find(int x) {
    while (x != parent[x])
        x = parent[x] = parent[parent[x]];
    return x;
}

void join(int x, int y) {
    x = find(x);
    y = find(y);

    if (x == y)
        return;

    if (sz[x] < sz[y])
        swap(x, y);

    parent[y] = x;
    sz[x] += sz[y];
}

int main() {
    string s;
    vector<v3> box;
    while (getline(cin, s)) {
        auto v = split_i(s, ",");
        box.emplace_back(v[0], v[1], v[2]);
    }

    vector<dist> dst;
    for (int i = 0; i < box.size(); i++)
        for (int j = i + 1; j < box.size(); j++) {
            v3 vd = box[j] - box[i];
            long d2 = vd[0] * (long)vd[0] + vd[1] * (long)vd[1] + vd[2] * (long)vd[2];
            dst.push_back(dist { .d = d2, .i = i, .j = j });
        }

    sort(dst.begin(), dst.end(), [&](const dist &a, const dist &b) { return a.d < b.d; });

    int n = box.size();
    parent.resize(n);
    sz.resize(n);

    for (int i = 0; i < n; i++) {
        parent[i] = i;
        sz[i] = 1;
    }

    for (int t = 0; t < dst.size(); t++) {
        int i = dst[t].i, j = dst[t].j;
        join(i, j);

        if (t == 1000) {
            vector<int> sets;
            for (int k = 0; k < n; k++)
                if (parent[k] == k)
                    sets.push_back(sz[k]);

            long result = 1;
            sort(sets.begin(), sets.end(), greater());
            for (int k = 0; k < 3; k++)
                result *= sets[k];
            cout << result << endl;
        }

        if (sz[find(i)] == n) {
            cout << (box[i][0] * (long)box[j][0]) << endl;
            break;
        }
    }

    return 0;
}


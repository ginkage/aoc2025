#include "../lib.hpp"

int main() {
    string s;
    vector<pair<long, long>> fresh;
    while (getline(cin, s) && s.size()) {
        auto p = split_l(s, "-");
        fresh.emplace_back(p[0], p[1] + 1);
    }

    sort(fresh.begin(), fresh.end());

    long result = 0;
    while (getline(cin, s)) {
        long id = stol(s);
        for (auto &p : fresh)
            if (id >= p.first && id < p.second) {
                result++;
                break;
            }
    }

    long result2 = 0, last = -1;
    for (auto &p : fresh)
        if (last < p.second) {
            result2 += p.second - max(last, p.first);
            last = p.second;
        }
    cout << result << ' ' << result2 << endl;

    return 0;
}


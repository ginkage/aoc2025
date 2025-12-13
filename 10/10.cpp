#include "../lib.hpp"

__uint128_t tmp[12];

__uint128_t pack(int m) {
    __uint128_t result = 0;
    for (int i = 0; i < m; i++)
        result += tmp[i] << (10 * i);
    return result;
}

void unpack(__uint128_t k, int m) {
    __uint128_t mask = (1 << 10) - 1;
    for (int i = 0; i < m; i++)
        tmp[i] = (k >> (10 * i)) & mask;
}

unordered_map<__uint128_t, long> memo;

long iterate(vector<uint16_t> &button, __uint128_t state, int m, int n) {
    if (state == 0)
        return 0;

    auto it = memo.find(state);
    if (it != memo.end())
        return it->second;

    unpack(state, m);
    uint16_t target = 0;
    for (int i = 0; i < m; i++)
        if (tmp[i] & 1)
            target |= (1 << i);

    long result = 1000000;
    for (int t = 0; t < (1 << n); t++) {
        uint16_t pat = 0;
        for (int j = 0; j < n; j++)
            if (t & (1 << j))
                pat ^= button[j];

        if (pat == target) { // Parity matches
            int k = 0;
            bool good = true;
            unpack(state, m);
            for (int j = 0; j < n && good; j++) 
                if (t & (1 << j)) { // Go over pressed buttons
                    for (int i = 0; i < m && good; i++)
                        if (button[j] & (1 << i)) { // Go over jolts for this button
                            if (tmp[i] == 0)
                                good = false; // Overflow
                            else
                                tmp[i]--;
                        }
                    k++;
                }

            if (good) {
                for (int i = 0; i < m; i++)
                    tmp[i] /= 2;
                result = min(result, k + 2 * iterate(button, pack(m), m, n));
            }
        }
    }

    memo[state] = result;
    return result;
}

long solve(vector<uint16_t> &button, vector<int> &jolt, int m, int n) {
    memo.clear();
    for (int i = 0; i < m; i++)
        tmp[i] = jolt[i];
    long res = iterate(button, pack(m), m, n);
    return res;
}

int main() {
    long result = 0, result2 = 0;
    string s;
    smatch linematch;
    const regex linerex("\\[(.*)\\] (.*) \\{(.*)\\}");
    const regex butrex("\\((.*)\\)");
    while (getline(cin, s) && regex_match(s, linematch, linerex) && linematch.size() == 4) {
        string pat = linematch[1].str();
        uint16_t target = 0;
        for (int i = 0; i < pat.size(); i++)
            target |= (pat[i] == '#') << i;

        vector<uint16_t> button;
        auto but = split_s(linematch[2].str(), " ");
        auto jolt = split_i(linematch[3].str(), ",");
        int m = jolt.size(), n = but.size();

        for (int j = 0; j < n; j++) {
            uint16_t tog = 0;
            if (regex_match(but[j], linematch, butrex) && linematch.size() == 2) {
                auto v = split_i(linematch[1].str(), ",");
                for (int i : v)
                    tog |= 1 << i;
            }
            button.push_back(tog);
        }

        int best = n;
        for (int t = 0; t < (1 << n); t++) {
            int k = 0;
            uint16_t pat = 0;
            for (int j = 0; j < n; j++)
                if (t & (1 << j)) {
                    pat ^= button[j];
                    k++;
                }

            if (pat == target)
                best = min(best, k);
        }
        result += best;

        result2 += solve(button, jolt, m, n);
    }
    cout << result << ' ' << result2 << endl;

    return 0;
}


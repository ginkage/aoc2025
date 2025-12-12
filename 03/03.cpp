#include "../lib.hpp"

long memo[100][13], pw[13];

long dp(const char *s, int n, int pos, int dig) {
    long m = memo[pos][dig];
    if (m < 0) {
        for (int i = pos; i < n - dig + 1; i++)
            m = max(m, pw[dig] * (s[i] - '0') + dp(s, n, i + 1, dig - 1));
        memo[pos][dig] = m;
    }
    return m;
}

int main() {
    pw[1] = 1;
    for (int i = 2; i < 13; i++)
        pw[i] = 10 * pw[i - 1];

    string s;
    long result = 0, result2 = 0;
    while (getline(cin, s)) {
        for (int i = 0; i < 100; i++) {
            memo[i][0] = 0;
            for (int j = 1; j < 13; j++)
                memo[i][j] = -1;
        }

        result += dp(s.c_str(), s.size(), 0, 2);
        result2 += dp(s.c_str(), s.size(), 0, 12);
    }
    cout << result << ' ' << result2 << endl;

    return 0;
}


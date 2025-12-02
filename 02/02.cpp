#include "../lib.hpp"

int main() {
    long result = 0, result2 = 0;

    // I digits, repeated J times
    long pp[11][11], rr[11][11];
    for (long i = 1; i < 11; i++)
        for (long j = 2; j < 11; j++) {
            if (i * j > 10) {
                pp[i][j] = 0;
                rr[i][j] = 0;
                continue;
            }
            long r = pow(10, i - 1), p = 1; // 3 -> 100
            for (int t = 1; t < j; t++)
                p = p * 10 * r + 1; // 1 -> 1001 -> 1001001
            pp[i][j] = p;
            rr[i][j] = r;
        }

    string s;
    getline(cin, s);
    for (string t : split_s(s, ",")) {
        auto v = split_l(t, "-");
        long t1 = v[0], t2 = v[1];
        for (long t = t1; t <= t2; t++) {
            long k = log10(t) + 1;

            for (long j = 2; j < 11; j++)
                if (k % j == 0)
                    for (long i = 1; i < 11; i++) {
                        long p = pp[i][j], r = rr[i][j];
                        if (p > 0 && t % p == 0 && t / p >= r && t / p < 10 * r) {
                            if (j == 2)
                                result += t;
                            result2 += t;

                            j = 11;
                            break;
                        }
                    }
        }
    }

    cout << result << ' ' << result2 << endl;

    return 0;
}


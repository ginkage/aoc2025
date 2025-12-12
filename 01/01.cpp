#include "../lib.hpp"

int main() {
    int pos = 50, result = 0, result2 = 0;

    string s;
    smatch linematch;
    const regex linerex("([LR])(\\d+)");
    while (getline(cin, s) && regex_match(s, linematch, linerex) && linematch.size() == 3) {
        char dir = linematch[1].str()[0];
        int k = stoi(linematch[2].str());
        if (dir == 'R') {
            while (pos + k >= 100) {
                k -= 100;
                result2++;
            }
            pos = (pos + k) % 100;
            if (pos == 0)
                result++;
        }
        else {
            bool flag = (pos == 0);
            while (pos - k <= 0) {
                k -= 100;
                if (flag) flag = false;
                else result2++;
            }
            pos = (pos - k) % 100;
            if (pos == 0)
                result++;
        }
    }

    cout << result << ' ' << result2 << endl;

    return 0;
}


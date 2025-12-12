#include "../lib.hpp"

int main() {
    string s;
    for (int i = 0; i < 30; i++)
        getline(cin, s);

    long result = 0;
    smatch linematch;
    const regex linerex("(.*)x(.*): (.*)");
    while (getline(cin, s) && regex_match(s, linematch, linerex) && linematch.size() == 4) {
        int w = stoi(linematch[1].str()), h = stoi(linematch[2].str()), n = 0;
        for (int t : split_i(linematch[3].str(), " "))
            n += t;
        if (w * h >= n * 7)
            result++;
    }
    cout << result << endl;

    return 0;
}


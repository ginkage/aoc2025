#include "../lib.hpp"

int main() {
    string s;
    for (int i = 0; i < 30; i++)
        getline(cin, s);

    long result = 0;
    const regex linerex("(.*)x(.*): (.*) (.*) (.*) (.*) (.*) (.*)");
    while (getline(cin, s)) {
        smatch linematch;
        if (regex_match(s, linematch, linerex) && linematch.size() == 9) {
            int w = stoi(linematch[1].str()), h = stoi(linematch[2].str());
            int n = stoi(linematch[3].str()) + stoi(linematch[4].str()) + stoi(linematch[5].str()) + stoi(linematch[6].str()) + stoi(linematch[7].str()) + stoi(linematch[8].str());
            if (w * h >= n * 7)
                result++;
        }
    }
    cout << result << endl;

    return 0;
}


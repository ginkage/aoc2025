#include "../lib.hpp"

unordered_map<int, vector<int>> ins;
unordered_map<int, long> paths;

long iterate(int end) {
    auto it = paths.find(end);
    if (it != paths.end())
        return it->second;

    long res = 0;
    for (int in : ins[end])
        res += iterate(in);
    paths[end] = res;
    return res;
}

int main() {
    string s;
    smatch linematch;
    const regex linerex("(.*): (.*)");
    while (getline(cin, s) && regex_match(s, linematch, linerex) && linematch.size() == 3) {
        int st = remap(linematch[1].str());
        for (auto &e : split_s(linematch[2].str(), " "))
            ins[remap(e)].push_back(st);
    }

    int you = remap("you"), out = remap("out");
    paths[you] = 1;
    long result = iterate(out);
    cout << result << endl;

    int svr = remap("svr"), fft = remap("fft"), dac = remap("dac");
    paths.clear();
    paths[svr] = 1;
    paths[dac] = 0;
    paths[fft] = 0;
    long res00 = iterate(out);

    paths.clear();
    paths[svr] = 1;
    paths[dac] = 0;
    long res01 = iterate(out);

    paths.clear();
    paths[svr] = 1;
    paths[fft] = 0;
    long res10 = iterate(out);

    paths.clear();
    paths[svr] = 1;
    long res11 = iterate(out);

    long result2 = res11 - res01 - res10 + res00;
    cout << result2 << endl;

    return 0;
}


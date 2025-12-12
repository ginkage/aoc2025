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

long run(int start, int end) {
    paths[start] = 1;
    long res = iterate(end);
    paths.clear();
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
    long result = run(you, out);
    cout << result << endl;

    int svr = remap("svr"), fft = remap("fft"), dac = remap("dac");
    paths[dac] = 0;
    paths[fft] = 0;
    long res00 = run(svr, out);

    paths[dac] = 0;
    long res01 = run(svr, out);

    paths[fft] = 0;
    long res10 = run(svr, out);

    long res11 = run(svr, out), result2 = res11 - res01 - res10 + res00;
    cout << result2 << endl;

    return 0;
}


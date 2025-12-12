#include "../lib.hpp"

int main() {
    vector<vector<long>> nums;
    vector<string> ops;
    vector<string> grid;
    string s;
    while (getline(cin, s)) {
        if (s.find('+') != string::npos || s.find('*') != string::npos)
            ops = split_s(s, " ", true);
        else
            nums.push_back(split_l(s, " "));
        grid.push_back(s);
    }

    long result = 0;
    for (int j = 0; j < ops.size(); j++)
        if (ops[j][0] == '+')
            for (auto &v : nums)
                result += v[j];
        else {
            long res = 1;
            for (auto &v : nums)
                res *= v[j];
            result += res;
        }

    long result2 = 0;
    int m = grid.size() - 1, n = grid[0].size();
    for (int j = 0; j < n; j++) {
        char op = grid[m][j];

        vector<long> nums;
        while (j + 1 == n || grid[m][j + 1] == ' ') {
            long num = 0;
            for (int i = 0; i < m; i++)
                if (isdigit(grid[i][j]))
                    num = num * 10 + (grid[i][j] - '0');
            nums.push_back(num);
            j++;
        }

        if (op == '+')
            for (long num : nums)
                result2 += num;
        else {
            long res = 1;
            for (long num : nums)
                res *= num;
            result2 += res;
        }
    }

    cout << result << ' ' << result2 << endl;

    return 0;
}


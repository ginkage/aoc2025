#include "../lib.hpp"

int main() {
    vector<vector<long>> nums;
    vector<string> ops;
    string s;
    while (getline(cin, s))
        if (s.find('+') != string::npos || s.find('*') != string::npos)
            ops = split_s(s, " ", true);
        else
            nums.push_back(split_l(s, " "));

    long result = 0;
    for (int j = 0; j < ops.size(); j++)
        if (ops[j][0] == '+')
            for (int i = 0; i < nums.size(); i++)
                result += nums[i][j];
        else {
            long res = 1;
            for (int i = 0; i < nums.size(); i++)
                res *= nums[i][j];
            result += res;
        }
    cout << result << endl;

    return 0;
}


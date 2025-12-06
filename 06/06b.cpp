#include "../lib.hpp"

int main() {
    string s;
    vector<string> grid;
    while (getline(cin, s))
        grid.push_back(s);

    long result = 0;
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
                result += num;
        else {
            long res = 1;
            for (long num : nums)
                res *= num;
            result += res;
        }
    }
    cout << result << endl;

    return 0;
}


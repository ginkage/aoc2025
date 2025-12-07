#include "../lib.hpp"

int main() {
    string s;
    vector<string> grid;
    while (getline(cin, s))
        grid.push_back(s);

    long result = 0;
    int m = grid.size(), n = grid[0].size();
    vector<vector<long>> tl(m, vector<long>(n, 0));
    for (int i = 1; i < m; i++)
        for (int j = 0; j < n; j++)
            if (grid[i - 1][j] == 'S') {
                grid[i][j] = '|';
                tl[i][j] = 1;
            }
            else if (grid[i - 1][j] == '|') {
                if (grid[i][j] == '^') {
                    result++;
                    grid[i][j - 1] = '|';
                    grid[i][j + 1] = '|';
                    tl[i][j - 1] += tl[i - 1][j];
                    tl[i][j + 1] += tl[i - 1][j];
                }
                else {
                    grid[i][j] = '|';
                    tl[i][j] += tl[i - 1][j];
                }
            }

    long result2 = 0;
    for (int j = 0; j < n; j++)
        result2 += tl[m - 1][j];

    cout << result << ' ' << result2 << endl;

    return 0;
}


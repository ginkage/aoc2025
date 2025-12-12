#include "../lib.hpp"

static int di[] = { -1, -1, -1, 0, 0, 1, 1, 1 };
static int dj[] = { -1, 0, 1, -1, 1, -1, 0, 1 };

vector<string> grid;
vector<vector<int8_t>> cnt;
int m, n;

char get(int i, int j) { return (i < 0 || j < 0 || i >= m || j >= n) ? '.' : grid[i][j]; }

int main() {
    string s;
    while (getline(cin, s))
        grid.push_back(s);

    m = grid.size();
    n = grid[0].size();
    cnt.resize(m, vector<int8_t>(n, 0));

    queue<vec> q;
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < 8; k++)
                cnt[i][j] += get(i + di[k], j + dj[k]) == '@';

            if (grid[i][j] == '@' && cnt[i][j] < 4)
                q.emplace(i, j);
        }

    long result = q.size(), result2 = 0;
    while (!q.empty()) {
        auto t = q.front();
        q.pop();
        int i = t[0], j = t[1];
        grid[i][j] = '.';
        result2++;

        for (int k = 0; k < 8; k++) {
            int ii = i + di[k], jj = j + dj[k];
            if (get(ii, jj) == '@' && --cnt[ii][jj] == 3)
                q.emplace(ii, jj);
        }
    }
    cout << result << ' ' << result2 << endl;

    return 0;
}


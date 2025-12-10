#include "../lib.hpp"

#include <glpk.h>

int solve(vector<vector<int>> &A, vector<int> &b, int m, int n) {
    // Compute variable upper bounds based on participation.
    vector<int> ub(n, 0);
    for (int j = 0; j < n; ++j) {
        int ubj = numeric_limits<int>::max();
        bool appears = false;
        for (int i = 0; i < m; ++i) {
            if (A[i][j]) { appears = true; ubj = min(ubj, b[i]); }
        }
        if (!appears) ubj = 0;
        if (ubj < 0 || ubj == numeric_limits<int>::max()) ubj = 0;
        ub[j] = ubj;
    }

    // Create problem
    glp_term_out(GLP_OFF);
    glp_prob *lp = glp_create_prob();
    glp_set_prob_name(lp, "axeqb_min_sum");
    glp_set_obj_dir(lp, GLP_MIN);

    // Add rows (constraints)
    glp_add_rows(lp, m);
    for (int i = 1; i <= m; ++i) {
        glp_set_row_bnds(lp, i, GLP_FX, b[i-1], b[i-1]); // equality constraint
    }

    // Add columns (variables)
    glp_add_cols(lp, n);
    for (int j = 1; j <= n; ++j) {
        if (ub[j-1] == 0) {
            glp_set_col_bnds(lp, j, GLP_FX, 0, 0); // fixed
            glp_set_col_kind(lp, j, GLP_CV); // continuous
        }
        else {
            glp_set_col_bnds(lp, j, GLP_DB, 0, ub[j-1]); // 0 <= x_j <= ub_j
            glp_set_col_kind(lp, j, GLP_IV); // integer
        }
        glp_set_obj_coef(lp, j, 1.0);             // objective: sum_j x_j
    }

    // Build matrix in GLPK's sparse format
    // GLPK expects 1-based indexing
    int nz = 0;
    for (int i = 0; i < m; ++i)
        for (int j = 0; j < n; ++j)
            if (A[i][j]) nz++;

    // GLPK arrays indexed from 1..nz
    vector<int> ia(nz + 1), ja(nz + 1);
    vector<double> ar(nz + 1);

    int k = 1;
    for (int i = 0; i < m; ++i)
        for (int j = 0; j < n; ++j)
            if (A[i][j]) {
                ia[k] = i + 1;
                ja[k] = j + 1;
                ar[k] = 1.0;
                k++;
            }

    glp_load_matrix(lp, nz, ia.data(), ja.data(), ar.data());

    // Solve MIP
    glp_iocp params;
    glp_init_iocp(&params);
    params.msg_lev = GLP_MSG_ON;
    params.presolve = GLP_ON;

    glp_intopt(lp, &params);
    double obj = glp_mip_obj_val(lp);
    glp_delete_prob(lp);
    return obj;
}

int main() {
    long result = 0, result2 = 0;
    string s;
    smatch linematch;
    const regex linerex("\\[(.*)\\] (.*) \\{(.*)\\}");
    const regex butrex("\\((.*)\\)");
    while (getline(cin, s) && regex_match(s, linematch, linerex) && linematch.size() == 4) {
        string pat = linematch[1].str();
        uint16_t target = 0;
        for (int i = 0; i < pat.size(); i++)
            target |= (pat[i] == '#') << i;

        vector<uint16_t> button;
        auto but = split_s(linematch[2].str(), " ");
        auto jolt = split_i(linematch[3].str(), ",");
        int m = jolt.size(), n = but.size();

        vector<vector<int>> A(m, vector<int>(n, 0));
        for (int j = 0; j < n; j++) {
            uint16_t tog = 0;
            if (regex_match(but[j], linematch, butrex) && linematch.size() == 2) {
                auto v = split_i(linematch[1].str(), ",");
                for (int i : v) {
                    tog |= 1 << i;
                    A[i][j] = 1;
                }
            }
            button.push_back(tog);
        }

        int best = n;
        for (int t = 0; t < (1 << n); t++) {
            int k = 0;
            uint16_t pat = 0;
            for (int i = 0; i < n; i++)
                if (t & (1 << i)) {
                    pat ^= button[i];
                    k++;
                }

            if (pat == target)
                best = min(best, k);
        }
        result += best;

        result2 += solve(A, jolt, m, n);
    }
    cout << result << ' ' << result2 << endl;

    return 0;
}


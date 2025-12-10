#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <cmath>
#include <algorithm>
#include <climits>
#include <cfloat>
#include <functional>

using namespace std;

// parse {a,b,c}
vector<long long> parseTarget(const string &line) {
    vector<long long> t;
    size_t l = line.find('{'), r = line.find('}');
    if (l==string::npos || r==string::npos) return t;
    string inside = line.substr(l+1, r-l-1);
    stringstream ss(inside);
    string token;
    while (getline(ss, token, ',')) {
        if (!token.empty()) t.push_back(stoll(token));
    }
    return t;
}

// parse (i,j,k)
vector<vector<int>> parseButtons(const string &line) {
    vector<vector<int>> res;
    size_t pos = 0;
    while ((pos = line.find('(', pos)) != string::npos) {
        size_t end = line.find(')', pos);
        if (end == string::npos) break;
        string inside = line.substr(pos+1, end-pos-1);
        stringstream ss(inside);
        string token;
        vector<int> btn;
        while (getline(ss, token, ',')) {
            if (!token.empty()) btn.push_back(stoi(token));
        }
        res.push_back(btn);
        pos = end+1;
    }
    return res;
}

// Solve A x = b, x >= 0 integer, minimize sum(x).
// Uses gaussian elimination (rational via long double) to find pivot structure,
// then enumerates free variables within safe upper bounds.
long long solveMachine(const vector<long long>& target,
                       const vector<vector<int>>& rawButtons)
{
    int M = (int)target.size();
    int N = (int)rawButtons.size();
    if (M == 0) return 0;
    if (N == 0) {
        for (auto v : target) if (v != 0) return -1;
        return 0;
    }

    // Build A (M x N) as long double for elimination, and augmented column b
    vector<vector<long double>> aug(M, vector<long double>(N+1, 0.0L));
    for (int j = 0; j < N; ++j)
        for (int idx : rawButtons[j])
            if (0 <= idx && idx < M) aug[idx][j] = 1.0L;
    for (int i = 0; i < M; ++i) aug[i][N] = (long double) target[i];

    // Gaussian elimination to RREF (over reals)
    const long double EPS = 1e-12L;
    int row = 0;
    vector<int> pivot_col; pivot_col.assign(M, -1);

    for (int col = 0; col < N && row < M; ++col) {
        // find pivot row (abs value)
        int sel = -1;
        long double best = 0;
        for (int i = row; i < M; ++i) {
            long double v = fabsl(aug[i][col]);
            if (v > best + EPS) { best = v; sel = i; }
        }
        if (sel == -1) continue;
        swap(aug[sel], aug[row]);
        pivot_col[row] = col;
        // normalize pivot row to make pivot = 1
        long double pivot = aug[row][col];
        for (int j = col; j <= N; ++j) aug[row][j] /= pivot;
        // eliminate other rows
        for (int i = 0; i < M; ++i) {
            if (i == row) continue;
            long double factor = aug[i][col];
            if (fabsl(factor) <= EPS) continue;
            for (int j = col; j <= N; ++j) aug[i][j] -= factor * aug[row][j];
        }
        row++;
    }
    int R = row;

    // check inconsistency: 0 ... 0 | nonzero
    for (int i = R; i < M; ++i) {
        bool allzero = true;
        for (int j = 0; j < N; ++j) if (fabsl(aug[i][j]) > EPS) { allzero = false; break; }
        if (allzero && fabsl(aug[i][N]) > EPS) return -1; // inconsistent
    }

    // mark pivot columns
    vector<int> isPivot(N, 0);
    for (int i = 0; i < R; ++i) if (pivot_col[i] != -1) isPivot[pivot_col[i]] = 1;

    // list free variables
    vector<int> freeVars;
    for (int j = 0; j < N; ++j) if (!isPivot[j]) freeVars.push_back(j);
    int F = (int)freeVars.size();

    // safe upper bounds for free variables: ub_j = min_{i in S_j} target[i]
    vector<long long> ub(N, 0);
    for (int j = 0; j < N; ++j) {
        long long bound = LLONG_MAX;
        if (rawButtons[j].empty()) {
            bound = 0;
        } else {
            for (int idx : rawButtons[j]) {
                if (idx >= 0 && idx < M) bound = min(bound, target[idx]);
            }
            if (bound == LLONG_MAX) bound = 0;
        }
        ub[j] = bound;
    }

    // If there are no free vars, just read pivot solution
    if (F == 0) {
        vector<long long> sol(N, 0);
        for (int i = 0; i < R; ++i) {
            int pc = pivot_col[i];
            long double val = aug[i][N];
            long long iv = llround(val);
            // numeric safety: if val not near integer, return -1 (no integer sol)
            if (fabsl(val - (long double)iv) > 1e-6L) return -1;
            sol[pc] = iv;
            if (sol[pc] < 0) return -1;
        }
        long long s = 0;
        for (long long v : sol) s += v;
        return s;
    }

    // But F usually small. We'll enumerate free vars with their ub.
    // However product of (ub+1) might be huge; if so we need fallback.
    __int128 totalComb = 1;
    for (int f = 0; f < F; ++f) {
        int j = freeVars[f];
        totalComb *= ( (__int128)ub[j] + 1 );
        if (totalComb > (__int128)1e8) break; // too many combos
    }

    // If combinations too big, fallback: use greedy + LP relaxation lower bound
    if (totalComb > (__int128)1e8) {
        // We'll use a simple LP relaxation to get integer solution via greedy rounding + repair.
        // Build least-square-ish greedy: solve nonnegative real x by simple pseudo-inverse (via QR) is heavy.
        // Instead, we do a bounded greedy: iteratively pick button that reduces L1 residual most per press.
        vector<long long> sol(N, 0);
        vector<long long> rem = target;
        // Simple greedy loop with cutoff to avoid infinite loops
        long long steps = 0, maxsteps = 2000000;
        while (true) {
            bool done = true;
            for (long long v : rem) if (v > 0) { done = false; break; }
            if (done) break;
            // choose button j that covers some positive counters and maximizes (#positive covered)
            int bestj = -1;
            int bestcov = 0;
            for (int j = 0; j < N; ++j) {
                int cov = 0;
                for (int idx : rawButtons[j]) if (rem[idx] > 0) cov++;
                if (cov > bestcov) { bestcov = cov; bestj = j; }
            }
            if (bestj == -1) return -1; // impossible to proceed
            // how many times to press bestj without overshooting any covered counter
            long long can = LLONG_MAX;
            for (int idx : rawButtons[bestj]) can = min(can, rem[idx]);
            if (can <= 0) { // if cannot reduce, stop to avoid infinite loop
                return -1;
            }
            // press once at a time (safe)
            long long press = max(1LL, min( (long long)1, can ));
            for (int idx : rawButtons[bestj]) rem[idx] -= press;
            sol[bestj] += press;
            if (++steps > maxsteps) break;
        }
        long long total = 0;
        for (long long v : sol) total += v;
        return total;
    }

    // Enumerate all combinations of free variables within their ubs.
    long long best = LLONG_MAX;
    vector<long long> fv(F, 0);
    // iterative counters to prevent recursion overhead
    vector<long long> cur(F,0);
    vector<long long> limit(F,0);
    for (int f=0; f<F; ++f) limit[f] = ub[freeVars[f]];

    // Use recursion but prune quickly
    function<void(int)> dfs = [&](int idx) {
        if (idx == F) {
            // build solution vector with free vars
            vector<long long> sol(N, 0);
            for (int f = 0; f < F; ++f) sol[freeVars[f]] = cur[f];

            // Back-substitute pivot variables
            for (int i = 0; i < R; ++i) {
                int pc = pivot_col[i];
                long double rhs = aug[i][N];
                for (int j = 0; j < N; ++j) {
                    if (j == pc) continue;
                    long double coeff = aug[i][j];
                    if (fabsl(coeff) > 1e-15L) {
                        long double contrib = coeff * (long double) sol[j];
                        rhs -= contrib;
                    }
                }
                // rhs should be non-negative integer
                if (rhs < -1e-9L) return;
                long long iv = llround(rhs);
                if (fabsl(rhs - (long double)iv) > 1e-6L) return; // not integral
                if (iv < 0) return;
                sol[pc] = iv;
            }

            // compute cost
            long long s = 0;
            for (long long v : sol) {
                s += v;
                if (s >= best) return; // prune
            }
            if (s < best) best = s;
            return;
        }

        // try values 0..limit[idx]
        for (long long v = 0; v <= limit[idx]; ++v) {
            cur[idx] = v;
            // quick partial lower bound pruning: compute minimum possible sum so far + optimistic for rest
            // sum so far
            long long partial = 0;
            for (int p = 0; p <= idx; ++p) partial += cur[p];
            if (partial >= best) break;
            dfs(idx+1);
        }
        cur[idx] = 0;
    };

    dfs(0);
    if (best == LLONG_MAX) return -1;
    return best;
}

int main(int argc, char** argv) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string filename = argc > 1 ? argv[1] : "input.txt";
    ifstream in(filename);
    if (!in) { cerr << "Cannot open input\n"; return 1; }

    string line;
    long long total = 0;
    while (getline(in, line)) {
        if (line.empty()) continue;
        auto target = parseTarget(line);
        auto buttons = parseButtons(line);
        long long r = solveMachine(target, buttons);
        if (r < 0) {
            cerr << "Machine unsolvable or numerical failure; line:\n" << line << "\n";
            // treat as failure, but continue
            continue;
        }
        total += r;
    }
    cout << total << "\n";
    return 0;
}

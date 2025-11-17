/**
 * Author: Per Austrin, Simon Lindholm
 * Date: 2004-02-08
 * License: CC0
 * Description: Solves $A * x = b$. If there are multiple solutions, an arbitrary one is returned.
 *  Returns rank, or -1 if no solutions. Data in $A$ and $b$ is lost.
 * Time: O(n^2 m)
 * Status: tested on kattis:primonimo
 */

#pragma once

const int mod = 998244353;

int mInv(int a); // insert a modular inverse function here

int solveLinear(vector<vi>& A, vi& b, vi& x) {
    int n = sz(A), m = sz(x), rank = 0, br, bc;
    if (n) assert(sz(A[0]) == m);
    vi col(m); iota(all(col), 0);

    rep(i,0,n) {
        int v, bv = 0;
        rep(r,i,n) rep(c,i,m)
            if ((v = abs(A[r][c])) > bv)
                br = r, bc = c, bv = v;
        if (bv == 0) {
            rep(j,i,n) if (abs(b[j]) > 0) return -1;
            break;
        }
        swap(A[i], A[br]);
        swap(b[i], b[br]);
        swap(col[i], col[bc]);
        rep(j,0,n) swap(A[j][i], A[j][bc]);
        bv = mInv(A[i][i], mod);
        rep(j,i+1,n) {
            int fac = (A[j][i] * bv) % mod;
            b[j] -= fac * b[i];
            b[j] %= mod;
            rep(k,i+1,m) {
                A[j][k] -= fac*A[i][k];
                A[j][k] %= mod;
            }
        }
        rank++;
    }

    x.assign(m, 0);
    for (int i = rank; i--;) {
        b[i] *= mInv(A[i][i], mod);
        b[i] %= mod;
        x[col[i]] = (b[i] + mod) % mod;
        rep(j,0,i) {
            b[j] -= A[j][i] * b[i];
            b[j] %= mod;
        }
    }
    return rank; // (multiple solutions if rank < m)
}

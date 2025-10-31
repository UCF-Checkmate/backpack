/**
 * Author: Nic Washbourne
 * Date: 2025-09-26
 * Source: Tyler Marks
 * Description: Forms a basis of binary vectors, with buildback. get() returns a list of the
 * input values associated with vectors that XOR to v. If v is not in the span, or is the zero
 * vector, an empty vector is returned.
 * Time: O(MAXBIT^2 / 32)
 * Status: Tested on https://codeforces.com/gym/105789/problem/B
 */
#pragma once

const int MAXBIT = 64;
using B = bitset<MAXBIT>;

template<class T> struct Basis {
    B basis[MAXBIT], which[MAXBIT];
    optional<T> vals[MAXBIT];
    Basis() { memset(vals, 0, sizeof(vals)); }

    bool add(B v, T x) {
        if (v.none()) return false;
        B cur; int ind = -1;
        for (int i = 0; i < MAXBIT; i++) if (v[i]) {
            if(vals[i].has_value())
                v ^= basis[i], cur ^= which[i];
            else if (ind < 0) ind = i;
        }
        if (ind < 0) return false;
        basis[ind] = v, vals[ind] = x;
        which[ind] = cur, which[ind][ind] = 1;
        return true;
    }

    vector<T> get(B v) const {
        if (v.none()) return {{}};
        B w;
        for (int i = 0; i < MAXBIT; i++) if (v[i])
            v ^= basis[i], w ^= which[i];
        if (v.any()) return {};

        vector<T> res;
        for (int i = 0; i < MAXBIT; i++)
            if (w[i]) res.push_back(*vals[i]);
        return res;
    }
};

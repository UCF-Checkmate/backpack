/**
 * Author: Nic Washbourne
 * Date: 2025-09-26
 * Source: Tyler Marks
 * Description: Forms a basis of binary vectors, with buildback.
 * Time: O(MAXBIT^2 / 32)
 * Status: Probably works lol
 */
#pragma once

const int MAXBIT = 30;
using B = bitset<MAXBIT>;

template<class T> struct Basis {
    B basis[MAXBIT], which[MAXBIT];
    T vals[MAXBIT];
    Basis() { memset(vals, 0, sizeof(vals)); }

    bool put(B v, T x) {
        if(v.none()) return false;
        B cur;
        int ind = -1;
        for (int i = 0; i < p; i++) if (x[i]) {
            if(vals[i])
                v ^= basis[i], cur ^= which[i];
            else if (ind < 0) ind = i;
        }
        if (ind < 0) return false;

        basis[ind] = v, vals[ind] = x;
        which[ind] = cur, which[ind][ind] = 1;
        return true;
    }

    B get(B v) {
        if (v.none()) return v;
        B res;
        for (int i = 0; i < p; i++) if (v[i]) {
            assert(basis[i][i]);
            v ^= basis[i], res ^= which[i];
        }
        return res;
    }
};

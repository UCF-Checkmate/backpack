/**
 * Author: Nic Washbourne
 * Date: 2025-09-26
 * Source: Tyler Marks
 * Description: Forms a basis of binary vectors, with buildback. get() returns a list of the
 * input values associated with vectors that XOR to v. If v is not in the span, or is the zero
 * vector, an empty vector is returned.
 * Time: O(M^2 / 32)
 * Status: Tested on https://codeforces.com/gym/105789/problem/B
 */
#pragma once

const int M = 64;
using B = bitset<M>;

template<class T> struct Basis {
	B basis[M], which[M], has_val;
	T val[M];
	Basis() { memset(val, 0, sizeof(val)); }
	bool add(B v, T x) {
		if (v.none()) return false;
		B cur; int ind = -1;
		for (int i = 0; i < M; i++) if (v[i]) {
			if (has_val[i])
				v ^= basis[i], cur ^= which[i];
			else if (ind < 0) ind = i;
		}
		if (ind < 0) return false;
		basis[ind] = v, val[ind] = x, has_val[ind] = 1;
		which[ind] = cur, which[ind][ind] = 1;
		return true;
	}
	vector<T> get(B v) const {
		if (v.none()) return {{}};
		B w;
		for (int i = 0; i < M; i++)
			if (v[i]) v ^= basis[i], w ^= which[i];
		if (v.any()) return {};

		vector<T> res;
		for (int i = 0; i < M; i++)
			if (w[i]) res.push_back(val[i]);
		return res;
	}
};

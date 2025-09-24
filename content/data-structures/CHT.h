/**
 * Author: Brian Grana
 * Date: 2025-04-02
 * Source: own work
 * Description: Computes min/max at point for a set of linear functions.
 * Lines must be inserted in monotonic order of slopes, with increasing
 * giving max value and decreasing giving min value. Try to avoid inserting
 * two lines with the same slope. Queries must also be done in order of
 * non-decreasing x.
 * Time: O(1) per query
 * Status: tested on https://codeforces.com/contest/311/problem/B
 */
#pragma once

template<class T>
struct Line {
    T m, b;
    Line(T m, T b) : m(m), b(b) {}
    T isect(const Line<T>& o) {
        return (o.b-b) / (m-o.m);
    }
};

template<class T>
struct CHT {
    deque<Line<T>> q;
    void insert(T m, T b) {
        Line<T> v(m, b);
        while (sz(q) > 1 && v.isect(q[0]) <= q[0].isect(q[1])) 
            q.pop_front();
        q.push_front(v);
    }
    T query(T x) {
        int s = sz(q)-1;
        while (s > 0 && q[s].isect(q[--s]) < x) 
            q.pop_back();
        auto [m, b] = q.back();
        return m * x + b;
    }
};

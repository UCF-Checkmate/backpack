/**
 * Author: Luke Videckis
 * Date: unknown
 * License: CC0
 * Source: https://github.com/programming-team-code/programming_team_code/blob/main/graphs/uncommon/enumerate_triangles.hpp
 * Description: Runs a callback on all triangles in an undirected graph.
 * Usage:
 *  enumerate_triangles(edges, n, [\&](int u, int v, int w) {
 *    ...
 *  });
 * Time: O(V + E^{3/2})
 * Status: unknown
 */
void enumerate_triangles(
  const vector<pair<int, int>>& edges, int n, auto f) {
  vector<int> deg(n);
  for (auto [u, v] : edges) deg[u]++, deg[v]++;
  vector<vector<int>> adj(n);
  for (auto [u, v] : edges) {
    if (tie(deg[u], u) > tie(deg[v], v)) swap(u, v);
    adj[u].push_back(v);
  }
  vector<bool> seen(n);
  for (auto [u, v] : edges) {
    for (int w : adj[u]) seen[w] = 1;
    for (int w : adj[v])
      if (seen[w]) f(u, v, w);
    for (int w : adj[u]) seen[w] = 0;
  }
}

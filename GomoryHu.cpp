// Returns tree edges `[u, v, cap]`. Max flow between any pair = min edge on tree path.
// Add to Dinic struct:
// bool leftOfMinCut(ll v) { return D[v] != -1; }
using Edge3 = array<ll,3>;
vector<Edge3> gomoryHu(int N,
    vector<array<ll,3>>& ed) {
  vector<Edge3> tree;
  vector<int> par(N, 0);
  for (int i = 1; i < N; i++) {
    Dinic D(N);
    for (auto& [a,b,c] : ed)
      D.add_edge(a, b, c), D.add_edge(b, a, c);
    ll flow = D.max_flow(i, par[i]);
    tree.push_back({i, par[i], flow});
    for (int j = i+1; j < N; j++)
      if (par[j] == par[i] && D.D[j] != -1)
        par[j] = i;
  }
  return tree;
}

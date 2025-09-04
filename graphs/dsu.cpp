struct DisjointUnionSet {
  int n;
  vector<int> parent, size;

  DisjointUnionSet(int n) : n(n) {
    parent.resize(n);
    size.resize(n);

    for (int i = 0; i < n; i++) {
      parent[i] = i;
      size[i] = 1;
    }
  }

  int Find(int u) {
    if (parent[u] == u)
      return u;

    return parent[u] = Find(parent[u]);
  }
  int Size(int u) { return size[Find(u)]; }
  void Union(int u, int v) {
    u = Find(u);
    v = Find(v);

    if (u == v)
      return;

    if (size[u] < size[v])
      swap(u, v);

    parent[v] = u;
    size[u] += size[v];
  }
  bool areConnected(int u, int v) { return Find(u) == Find(v); }
};
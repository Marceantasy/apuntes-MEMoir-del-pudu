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

  int get(int u) {
    if (parent[u] == u)
      return u;

    return parent[u] = get(parent[u]);
  }
  int size(int u) { return size[get(u)]; }

  void Union(int u, int v) {
    u = get(u);
    v = get(v);

    if (u == v)
      return;

    if (size[u] < size[v])
      swap(u, v);

    parent[v] = u;
    size[u] += size[v];
  }
  bool sameSet(int u, int v) { return get(u) == get(v); }
};
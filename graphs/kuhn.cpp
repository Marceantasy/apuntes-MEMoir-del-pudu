struct Kuhn {
  vector<vector<int>> graph;
  vector<int> mt;
  vector<bool> used;
  int size = 0;

  bool tryKuhn(int node) {
    if (used[node])
      return false;

    used[node] = true;

    for (int to : graph[node]) {
      if (mt[to] != -1 && !tryKuhn(mt[to]))
        continue;

      mt[to] = node;
      return true;
    }

    return false;
  }

  Kuhn(vector<vector<int>> graph) : graph(graph) {
    int n = graph.size();
    mt.assign(n, -1);

    for (int i = 0; i < n; i++) {
      used.assign(n, false);
      size += tryKuhn(i);
    }
  }
};

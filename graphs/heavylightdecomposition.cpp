template <class ST, class T, T merge(T a, T b)> struct HeavyLightDecomposition {
  vector<vector<int>> tree;
  vector<int> parent, depth, heavy, head, position, size;
  int currentPosition;
  ST segmentTree;

  HeavyLightDecomposition() {}
  HeavyLightDecomposition(vector<vector<int>> &tree) : tree(tree) {
    int n = tree.size();

    parent.resize(n);
    depth.resize(n);
    heavy.assign(n, -1);
    head.resize(n);
    position.resize(n);
    size.resize(n);
    currentPosition = 0;

    dfs(0);
    decompose(0, 0);
  }

  int dfs(int node) {
    size[node] = 1;
    int maxSubtreeSize = 0;

    for (int child : tree[node]) {
      if (child == parent[node])
        continue;

      parent[child] = node;
      depth[child] = depth[node] + 1;

      int subtreeSize = dfs(child);
      size[node] += subtreeSize;

      if (subtreeSize <= maxSubtreeSize)
        continue;

      maxSubtreeSize = subtreeSize;
      heavy[node] = child;
    }

    return size[node];
  }

  void decompose(int node, int nodeHead) {
    head[node] = nodeHead;
    position[node] = currentPosition++;

    if (heavy[node] != -1)
      decompose(heavy[node], nodeHead);

    for (int child : tree[node])
      if (child != parent[node] && child != heavy[node])
        decompose(child, child);
  }

  int query(int a, int b) {
    T answer;
    bool hasValue = false;

    while (head[a] != head[b]) {
      if (depth[head[a]] > depth[head[b]])
        swap(a, b);

      T current = segmentTree.query(position[head[b]], position[b]);

      answer = hasValue ? merge(answer, current) : current;
      hasValue = true;

      b = parent[head[b]];
    }

    if (depth[a] > depth[b])
      swap(a, b);

    T last = segmentTree.query(position[a], position[b]);

    return hasValue ? merge(answer, last) : last;
  }

  vector<T> sorted(vector<T> &values) {
    int n = values.size();

    vector<T> result(n);

    for (int i = 0; i < n; i++)
      result[position[i]] = values[i];

    return result;
  }

  void update(int node, T value) { segmentTree.update(position[node], value); }

  // void update(int subtree, T value) {
  //   segmentTree.update(position[subtree], position[subtree] + size[subtree] -
  //   1,
  //                      value);
  // }
};
struct MergeSortTree {
  int n;
  vector<vector<int>> tree;

  vector<int> merge(const vector<int> &left, const vector<int> &right) {
    vector<int> result(left.size() + right.size());

    int i = 0, j = 0;

    for (int &x : result) {
      if (i == left.size())
        x = right[j++];
      else if (j == right.size())
        x = left[i++];
      else if (left[i] < right[j])
        x = left[i++];
      else
        x = right[j++];
    }

    return result;
  }

  void build(int i, int left, int right, const vector<int> &values) {
    if (left == right) {
      tree[i] = {values[left]};
      return;
    }

    int mid = (left + right) >> 1;

    build(i << 1, left, mid, values);
    build(i << 1 | 1, mid + 1, right, values);

    tree[i] = merge(tree[i << 1], tree[i << 1 | 1]);
  }

  MergeSortTree(const vector<int> &values) {
    n = values.size();
    tree.resize(n << 2 | 3);
    build(1, 0, n - 1, values);
  }

  int query(int i, int left, int right, int queryLeft, int queryRight, int min,
            int max) {
    if (left > queryRight or right < queryLeft)
      return 0;

    if (left >= queryLeft and right <= queryRight) {
      auto leftIterator = lower_bound(tree[i].begin(), tree[i].end(), min);
      auto rightIterator = upper_bound(tree[i].begin(), tree[i].end(), max);

      return distance(leftIterator, rightIterator);
    }

    int mid = (left + right) >> 1;

    return query(i << 1, left, mid, queryLeft, queryRight, min, max) +
           query(i << 1 | 1, mid + 1, right, queryLeft, queryRight, min, max);
  }

  int query(int left, int right, int min, int max) {
    return query(1, 0, n - 1, left, right, min, max);
  }
};

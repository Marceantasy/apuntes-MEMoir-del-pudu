
template <class T, T merge(T, T)> struct PersistentSegmentTree {
  vector<T> tree;
  vector<int> L, R;
  int n, root = 0;

  PersistentSegmentTree(int n) : n(n) {
    tree.resize(1);
    L = {0};
    R = {0};
  }

  int newNode(T value, int left = 0, int right = 0) {
    int id = tree.size();
    tree.push_back(value);
    L.push_back(left);
    R.push_back(right);
    return id;
  }

  int update(int id, int left, int right, int position, T value) {
    int newId = newNode(tree[id], L[id], R[id]);

    if (left == right) {
      tree[newId] = value;
      return newId;
    }

    int mid = (left + right) >> 1;

    if (position <= mid)
      L[newId] = update(L[newId], left, mid, position, value);
    else
      R[newId] = update(R[newId], mid + 1, right, position, value);

    tree[newId] = merge(tree[L[newId]], tree[R[newId]]);

    return newId;
  }
  T query(int id, int left, int right, int qLeft, int qRight) {
    if (left >= qLeft and right <= qRight)
      return tree[id];

    int mid = (left + right) >> 1;

    if (qRight <= mid)
      return query(L[id], left, mid, qLeft, qRight);

    if (qLeft > mid)
      return query(R[id], mid + 1, right, qLeft, qRight);

    return merge(query(L[id], left, mid, qLeft, qRight),
                 query(R[id], mid + 1, right, qLeft, qRight));
  }

  T query(int id, int left, int right) {
    return query(id, 0, n - 1, left, right);
  }

  int update(int id, int position, T value) {
    return root = update(id, 0, n - 1, position, value);
  }

  int update(int position, T value) { return update(root, position, value); }
};

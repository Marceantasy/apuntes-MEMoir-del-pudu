template <class T1, class T2, T1 merge(T1, T1),
          void pushUpdate(T2 parent, T2 &child, int, int, int, int),
          void applyUpdate(T2 update, T1 &node, int, int)>
struct SegmentTreeLazy {
  int n;
  vector<T1> tree;
  vector<T2> lazy;
  vector<bool> isUpdated;

  void build(int i, int left, int right, const vector<T1> &values) {
    if (left == right) {
      tree[i] = values[left];
      return;
    }

    int mid = (left + right) >> 1;

    build(i << 1, left, mid, values);
    build(i << 1 | 1, mid + 1, right, values);

    tree[i] = merge(tree[i << 1], tree[i << 1 | 1]);
  }

  SegmentTreeLazy(const vector<T1> &values) {
    n = values.size();
    int size = n << 2 | 3;

    tree.resize(size);
    lazy.resize(size);
    isUpdated.resize(size);

    build(1, 0, n - 1, values);
  }

  SegmentTreeLazy() {}

  void push(int i, int left, int right) {
    if (!isUpdated[i])
      return;

    applyUpdate(lazy[i], tree[i], left, right);

    if (left != right) {
      if (isUpdated[i << 1])
        pushUpdate(lazy[i], lazy[i << 1], left, right, left,
                   (left + right) / 2);
      else
        lazy[i << 1] = lazy[i];

      if (isUpdated[i << 1 | 1])
        pushUpdate(lazy[i], lazy[i << 1 | 1], left, right,
                   (left + right) / 2 + 1, right);
      else
        lazy[i << 1 | 1] = lazy[i];

      isUpdated[i << 1] = 1;
      isUpdated[i << 1 | 1] = 1;
    }

    isUpdated[i] = false;
  }

  void update(int i, int left, int right, int queryLeft, int queryRight,
              T2 &value) {
    if (left >= queryLeft and right <= queryRight) {
      if (isUpdated[i])
        pushUpdate(value, lazy[i], queryLeft, queryRight, left, right);
      else
        lazy[i] = value;

      isUpdated[i] = true;
    }

    push(i, left, right);

    if (left > queryRight or right < queryLeft)
      return;

    if (left >= queryLeft and right <= queryRight)
      return;

    update(i << 1, left, (left + right) >> 1, queryLeft, queryRight, value);
    update(i << 1 | 1, (left + right) / 2 + 1, right, queryLeft, queryRight,
           value);

    tree[i] = merge(tree[i << 1], tree[i << 1 | 1]);
  }

  void update(int left, int right, T2 value) {
    update(1, 0, n - 1, left, right, value);
  }

  T1 query(int i, int left, int right, int queryLeft, int queryRight) {
    push(i, left, right);

    if (queryLeft <= left and right <= queryRight)
      return tree[i];

    int mid = (left + right) >> 1;

    if (mid < queryLeft)
      return query(i << 1 | 1, mid + 1, right, queryLeft, queryRight);

    if (mid >= queryRight)
      return query(i << 1, left, mid, queryLeft, queryRight);

    return merge(query(i << 1, left, mid, queryLeft, queryRight),
                 query(i << 1 | 1, mid + 1, right, queryLeft, queryRight));
  }

  T1 query(int left, int right) { return query(1, 0, n - 1, left, right); }
};
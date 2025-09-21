// Not well tested
// Not works for too large n like 10^18
// Use when n is large but number of updates/queries is small

template <class Node,  // Value Type
          class Lazy,  // Lazy type
          class Index, // Range type
          Node (*merge)(Node, Node),
          void (*pushUpdate)(Lazy &parent, Lazy &child, Index a, Index b,
                             Index l, Index r),
          void (*applyUpdate)(Lazy &update, Node &values, Index l, Index r),
          Node (*createNewNode)(Index l, Index r),     // Create default value
          Node (*createNeutralNode)(Index l, Index r)> // Create neutral value
struct DynamicLazySegmentTree {
  vector<Node> values;
  vector<Lazy> lazy;
  vector<bool> hasUpdate;
  vector<int> L, R;
  int root, nodeCount;
  Index n;

  DynamicLazySegmentTree(Index maxIndex, int size = 1 << 20)
      : n(maxIndex), nodeCount(1) {
    values.reserve(size);
    lazy.reserve(size);
    hasUpdate.reserve(size);
    L.reserve(size);
    R.reserve(size);

    values.push_back(createNewNode(0, n - 1));
    lazy.push_back(Lazy());
    hasUpdate.push_back(false);
    L.push_back(0);
    R.push_back(0);
    root = 0;
  }

  int createNode(Index l, Index r) {
    int i = nodeCount++;
    values.push_back(createNewNode(l, r));
    lazy.push_back(Lazy());
    hasUpdate.push_back(false);
    L.push_back(0);
    R.push_back(0);
    return i;
  }

  void push(int i, Index l, Index r) {
    if (!hasUpdate[i])
      return;

    if (l != r) {
      Index mid = (l + r) >> 1;

      if (!L[i])
        L[i] = createNode(l, mid);

      if (!R[i])
        R[i] = createNode(mid + 1, r);

      pushUpdate(lazy[i], lazy[L[i]], l, r, l, mid);
      pushUpdate(lazy[i], lazy[R[i]], l, r, mid + 1, r);

      hasUpdate[L[i]] = true;
      hasUpdate[R[i]] = true;

      applyUpdate(lazy[i], values[L[i]], l, mid);
      applyUpdate(lazy[i], values[R[i]], mid + 1, r);
    }

    lazy[i] = Lazy();
    hasUpdate[i] = false;
  }

  void update(int i, Index l, Index r, Index a, Index b, Lazy &value) {
    if (r < a || l > b)
      return;

    if (a <= l && r <= b) {
      applyUpdate(value, values[i], l, r);

      if (l != r)
        if (hasUpdate[i])
          applyUpdate(lazy[i], values[i], l, r);
        else {
          lazy[i] = value;
          hasUpdate[i] = true;
        }

      return;
    }

    push(i, l, r);

    Index mid = (l + r) >> 1;

    if (!L[i])
      L[i] = createNode(l, mid);

    update(L[i], l, mid, a, b, value);

    if (!R[i])
      R[i] = createNode(mid + 1, r);

    update(R[i], mid + 1, r, a, b, value);

    values[i] = merge(values[L[i]], values[R[i]]);
  }

  void update(Index a, Index b, Lazy value) {
    update(root, 0, n - 1, a, b, value);
  }

  void update(Index i, Lazy value) { update(i, i, value); }

  Node query(int i, Index l, Index r, Index a, Index b) {
    push(i, l, r);

    if (r < a || l > b)
      return createNeutralNode(l, r);

    if (a <= l && r <= b)
      return values[i];

    Index mid = (l + r) >> 1;

    Node left = createNewNode(l, mid);
    Node right = createNewNode(mid + 1, r);

    if (L[i] != 0)
      left = query(L[i], l, mid, a, b);

    if (R[i] != 0)
      right = query(R[i], mid + 1, r, a, b);

    return merge(left, right);
  }

  Node query(Index a, Index b) { return query(root, 0, n - 1, a, b); }

  Node query(Index i) { return query(i, i); }
};
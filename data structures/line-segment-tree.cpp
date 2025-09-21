struct LineSegmentTree {
  int n;
  vector<LineContainer> tree;

  LineSegmentTree(int n) : n(n) { tree.resize(4 * n); }

  void add(int i, int left, int right, int queryLeft, int queryRight, ll a,
           ll b) {
    if (left > queryRight or right < queryLeft)
      return;

    if (queryLeft <= left && right <= queryRight) {
      tree[i].add(a, b);
      return;
    }

    int mid = (left + right) >> 1;

    add(i << 1, left, mid, queryLeft, queryRight, a, b);
    add(i << 1 | 1, mid + 1, right, queryLeft, queryRight, a, b);
  }

  void add(int left, int right, ll a, ll b) {
    add(1, 0, n - 1, left, right, a, b);
  }

  ll query(int i, int left, int right, ll x) {
    ll answer = tree[i].query(x);

    if (left == right)
      return answer;

    int mid = (left + right) >> 1;

    // change max to min for min
    if (x <= mid)
      answer = max(answer, query(i << 1, left, mid, x));
    else
      answer = max(answer, query(i << 1 | 1, mid + 1, right, x));

    return answer;
  }

  ll query(ll x) { return query(1, 0, n - 1, x); }
};
struct DynamicLineSegmentTree {
  vector<LineContainer> tree;
  vector<int> L, R;

  ll minX, maxX;

  DynamicLineSegmentTree(ll left, ll right) {
    tree.resize(1);
    L = {0};
    R = {0};
    minX = left;
    maxX = right;
  }

  int newNode() {
    int i = tree.size();
    tree.push_back(LineContainer());
    L.push_back(0);
    R.push_back(0);
    return i;
  }

  void add(int i, ll left, ll right, ll queryLeft, ll queryRight, ll a, ll b) {
    if (left > queryRight or right < queryLeft)
      return;

    if (queryLeft <= left && right <= queryRight) {
      tree[i].add(a, b);
      return;
    }

    int mid = (left + right) >> 1;

    if (L[i] == 0)
      L[i] = newNode();

    if (R[i] == 0)
      R[i] = newNode();

    add(L[i], left, mid, queryLeft, queryRight, a, b);
    add(R[i], mid + 1, right, queryLeft, queryRight, a, b);
  }

  void add(int left, int right, ll a, ll b) {
    add(0, minX, maxX, left, right, a, b);
  }

  ll query(int i, int left, int right, ll x) {
    ll answer = tree[i].query(x);

    if (left == right)
      return answer;

    int mid = (left + right) >> 1;

    // change max to min for min
    if (x <= mid && L[i] != 0)
      answer = max(answer, query(L[i], left, mid, x));

    if (x > mid && R[i] != 0)
      answer = max(answer, query(R[i], mid + 1, right, x));

    return answer;
  }

  ll query(ll x) { return query(0, minX, maxX, x); }
};
template <class T, T merge(T, T)> struct SegmentTree {
  int n;
  vector<T> tree;
  SegmentTree() {}
  SegmentTree(vector<T> &values) {
    n = values.size();
    tree.resize(n << 1);
    for (int i = 0; i < n; i++)
      tree[i + n] = values[i];
    for (int i = n - 1; i > 0; i--)
      tree[i] = merge(tree[i << 1], tree[i << 1 | 1]);
  }
  void update(int position, T value) {
    position += n;
    tree[position] = value;
    for (position >>= 1; position > 0; position >>= 1)
      tree[position] = merge(tree[position << 1], tree[position << 1 | 1]);
  }
  T query(int left,
          int right) // [left, right]
  {
    bool hasAnswer = false;
    T answer = T();
    for (left += n, right += n + 1; left < right; left >>= 1, right >>= 1) {
      if (left & 1) {
        answer = hasAnswer ? merge(answer, tree[left]) : tree[left];
        hasAnswer = true;
        left++;
      }
      if (right & 1) {
        right--;
        answer = hasAnswer ? merge(answer, tree[right]) : tree[right];
        hasAnswer = true;
      }
    }
    return answer;
  }
};
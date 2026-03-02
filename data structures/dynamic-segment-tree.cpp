template <class T, T merge(T, T)> struct SegmentTree {
  struct Node {
    T value;
    Node *leftChild, *rightChild;
    int left, right;

    // Use long long for ranges if needed
    Node(int left, int right) : left(left), right(right) {
      value = T(); // neutral value
      leftChild = nullptr;
      rightChild = nullptr;
    }
  };

  Node *root;

  SegmentTree(int n) { root = new Node(0, n - 1); }

  void createNode(Node *&node, int left, int right) {
    if (node == nullptr)
      node = new Node(left, right);
  }

  T get(Node *node) {
    return node == nullptr ? T() : node->value; // T() neutral value
  }

  void update(Node *node, int position, const T &value) {
    if (node->left == node->right) {
      node->value = value;
      return;
    }

    int mid = node->left + (node->right - node->left) / 2;

    if (position > mid) {
      createNode(node->rightChild, mid + 1, node->right);
      update(node->rightChild, position, value);
    } else {
      createNode(node->leftChild, node->left, mid);
      update(node->leftChild, position, value);
    }

    node->value = merge(get(node->leftChild), get(node->rightChild));
  }

  void update(int position, const T &value) { update(root, position, value); }

  T query(Node *node, int queryLeft, int queryRight) {
    if (node == nullptr)
      return T(); // neutral value

    if (queryLeft <= node->left && queryRight >= node->right)
      return node->value;

    int mid = node->left + (node->right - node->left) / 2;

    T answer;
    bool hasAnswer = false;

    if (mid >= queryLeft) {
      answer = query(node->leftChild, queryLeft, queryRight);
      hasAnswer = true;
    }

    if (mid + 1 <= queryRight) {
      T value = query(node->rightChild, queryLeft, queryRight);
      answer = hasAnswer ? merge(answer, value) : value;
    }

    return answer;
  }

  T query(int left, int right) { return query(root, left, right); }
};
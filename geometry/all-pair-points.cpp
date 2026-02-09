template <class OP> void all_pair_points(vector<Point> &points, OP op) {
  int n = points.size();
  sort(points.begin(), points.end(), [](Point a, Point b) {
    return make_pair(a.y, a.x) < make_pair(b.y, b.x);
  });

  vector<pair<int, int>> events;

  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      if (i != j)
        events.push_back({i, j});

  stable_sort(events.begin(), events.end(), [&](auto a, auto b) {
    auto point1 = (points[a.second] - points[a.first]);
    auto point2 = (points[b.second] - points[b.first]);

    return point1.angle_lt(point2);
  });

  vector<int> indexes(n);
  for (int i = 0; i < n; i++)
    indexes[i] = i;

  for (auto [i, j] : events) {
    op(indexes[i], indexes[j]);
    swap(points[indexes[i]], points[indexes[j]]);
    swap(indexes[i], indexes[j]);
  }
}

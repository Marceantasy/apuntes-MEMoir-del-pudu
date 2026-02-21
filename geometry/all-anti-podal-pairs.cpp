vector<pii> allAntiPodal(vector<Point> &points) {
  int n = points.size();

  if (n == 1) return {};
  if (n == 2) return {{0, 1}}; // TLE if not check this case, lol

  vector<bool> visited(n);

  vector<pii> result;

  for (int i = 0, j = 0; i < n; i++) {
    Point base = points[nx(i)] - points[i];

    while (i == j || nx(i) == j ||
           base.left(points[nx(j)] - points[j]) ==
               base.left(points[j] - points[pv(j)]))
      j = nx(j);

    if (visited[i]) continue;

    visited[i] = true;

    result.push_back({i, j});
    result.push_back({nx(i), j});

    if (base.left(points[nx(j)] - points[j]) == 0) {
      result.push_back({i, nx(j)});
      result.push_back({nx(i), nx(j)});
      visited[j] = true;
    }
  }

  return result;
}

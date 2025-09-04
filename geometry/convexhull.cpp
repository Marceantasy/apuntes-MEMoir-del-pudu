vector<Point> convexHull(vector<Point> points) {
  if (points.size() < 3)
    return points;

  sort(points.begin(), points.end());

  vector<Point> hull;

  // Lower hull
  for (Point &point : points) {
    // change <= to < for collineal
    while (hull.size() >= 2 &&
           point.left(hull[hull.size() - 2], hull.back()) < 0)
      hull.pop_back();

    hull.push_back(point);
  }

  hull.pop_back();

  int m = hull.size();

  // Upper hull
  for (int i = points.size() - 1; i >= 0; --i) {
    Point &point = points[i];

    // change <= to < for collineal
    while (hull.size() >= m + 2 &&
           point.left(hull[hull.size() - 2], hull.back()) < 0)
      hull.pop_back();

    hull.push_back(point);
  }

  hull.pop_back();

  return hull;
}

// MARCELO
void reorder_polygon(vector<P> &ps) {
  int pos = 0;
  repx(i, 1, (int)ps.size()) {
    if (ps[i].y < ps[pos].y || (ps[i].y == ps[pos].y && ps[i].x < ps[pos].x))
      pos = i;
  }
  rotate(ps.begin(), ps.begin() + pos, ps.end());
}
vector<P> minkowski(vector<P> ps, vector<P> qs) {
  // the first vertex must be the lowest
  reorder_polygon(ps);
  reorder_polygon(qs);
  ps.push_back(ps[0]);
  ps.push_back(ps[1]);
  qs.push_back(qs[0]);
  qs.push_back(qs[1]);
  vector<P> result;
  int i = 0, j = 0;
  while (i < ps.size() - 2 || j < qs.size() - 2) {
    result.push_back(ps[i] + qs[j]);
    auto z = (ps[i + 1] - ps[i]) % (qs[j + 1] - qs[j]);
    if (z >= 0 && i < ps.size() - 2)
      ++i;
    if (z <= 0 && j < qs.size() - 2)
      ++j;
  }
  return result;
}

// ENZO

bool reverseCompare(Point &a, Point &b) {
  if (a.y == b.y)
    return a.x < b.x;
  return a.y < b.y;
};

void reorder(vector<Point> &points) {
  int index = 0;

  for (int i = 1; i < (int)points.size(); i++)
    if (reverseCompare(points[i], points[index]))
      index = i;

  rotate(points.begin(), points.begin() + index, points.end());
}

// O(n + m)
// Returns the Minkowski sum of two polygons a and b
// Both polygons must be given in counter-clockwise order
vector<Point> minkowski(vector<Point> a, vector<Point> b) {

  reorder(a);
  a.push_back(a[0]);
  a.push_back(a[1]);

  reorder(b);
  b.push_back(b[0]);
  b.push_back(b[1]);

  vector<Point> result;

  int i = 0, j = 0;

  int n = (int)a.size(), m = (int)b.size();

  while (i < n - 2 || j < m - 2) {
    result.push_back(a[i] + b[j]);

    auto cross = (a[i + 1] - a[i]).cross(b[j + 1] - b[j]);

    if (i < n - 2 && cross >= 0)
      i++;

    if (j < m - 2 && cross <= 0)
      j++;
  }

  return result;
}

// Example: to compute the Minkowski difference of A and B, use
// minkowski(A, transform(B, [](Point point) { return Point(-point.x, -point.y);
// }));
vector<Point> transform(const vector<Point> &points,
                        function<Point(Point)> callback) {
  int n = (int)points.size();
  vector<Point> result(n);
  for (int i = 0; i < n; i++)
    result[i] = callback(points[i]);

  return result;
}
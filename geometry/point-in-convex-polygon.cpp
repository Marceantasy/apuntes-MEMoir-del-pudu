// Construction: O(n), Query: O(log n)
// Only works for convex polygons

struct PointInPolygon {
  vector<Point> points, sequence;
  Point translation;
  int n, m;

  PointInPolygon(vector<Point> points) : points(points) {
    n = (int)points.size();

    // order (x, y)
    rotate(points.begin(), min_element(points.begin(), points.end()),
           points.end());

    translation = points[0];

    m = n - 1;
    sequence.resize(m);

    for (int i = 0; i < m; i++)
      sequence[i] = points[i + 1] - points[0];
  }

  bool query(Point point) {
    point = point - translation;

    if (sequence.front().cross(point) == 0)
      return sequence.front().dot(point) >= 0 &&
             sequence.front().squaredLength() >=
                 point.squaredLength(); // Use >= to consider points on edge as
                                        // inside, < to consider them as outside

    if (sequence.back().cross(point) == 0)
      return sequence.back().dot(point) >= 0 &&
             sequence.back().squaredLength() >=
                 point.squaredLength(); // Use >= to consider points on edge as
                                        // inside, < to consider them as outside

    if (sequence.front().cross(point) < 0)
      return false;

    if (sequence.back().cross(point) > 0)
      return false;

    int left = 0, right = m - 1;

    while (right - left > 1) {
      int mid = (left + right) / 2;

      if (sequence[mid].cross(point) >= 0)
        left = mid;
      else
        right = mid;
    }

    // This dont check if point is on the edge of the polygon, modify
    // pointInTriangle if needed
    return pointInTriangle(sequence[left], sequence[(left + 1) % m],
                           Point(0, 0), point);
  }
};
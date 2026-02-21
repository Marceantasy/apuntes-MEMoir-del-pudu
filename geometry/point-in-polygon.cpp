// 0: outside, 1: inside, 2: boundary
template <class T>
int pointInPolygon(vector<Point<T>> &polygon, Point<T> point) {
  int count = 0;

  int n = polygon.size();

  for (int i = 0; i < n; i++) {
    Point<T> pointA = polygon[i], pointB = polygon[(i + 1) % n];

    T cross = (pointB - pointA).cross(point - pointA);

    if (cross == 0 && point.x >= min(pointA.x, pointB.x) &&
        point.x <= max(pointA.x, pointB.x) &&
        point.y >= min(pointA.y, pointB.y) &&
        point.y <= max(pointA.y, pointB.y))
      return 2;

    if ((point.y <= pointA.y) == (point.y <= pointB.y))
      continue;

    T left = point.x * (pointB.y - pointA.y);

    T right = pointA.x * (pointB.y - pointA.y) +
              (point.y - pointA.y) * (pointB.x - pointA.x);

    if ((pointB.y - pointA.y) < 0)
      left *= -1, right *= -1;

    count += left < right;
  }

  if (count % 2 == 0)
    return 0;

  return 1;
}

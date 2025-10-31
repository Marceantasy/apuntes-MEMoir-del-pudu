
template <class T>
optional<pair<Point<T>, Point<T>>>
circleLineIntersection(T radius, Point<T> first, Point<T> second) {
  auto [x1, y1] = first;
  auto [x2, y2] = second;

  T dx = x2 - x1, dy = y2 - y1;

  T a = dy;
  T b = -dx;
  T c = -(a * x1 + b * y1);

  if (c * c > radius * radius * (a * a + b * b)) {
    return nullopt;
  }

  if (c * c == radius * radius * (a * a + b * b)) {
    // TODO: Check if this is correct
    T x0 = -a * c / (a * a + b * b), y0 = -b * c / (a * a + b * b);
    return make_pair(Point<T>(x0, y0), Point<T>(x0, y0));
  }

  T d = radius * radius - c * c / (a * a + b * b);
  T mult = sqrt(d / (a * a + b * b));

  T x0 = -a * c / (a * a + b * b), y0 = -b * c / (a * a + b * b);
  T ax = x0 + b * mult, ay = y0 - a * mult;
  T bx = x0 - b * mult, by = y0 + a * mult;

  return make_pair(Point<T>(ax, ay), Point<T>(bx, by));
}

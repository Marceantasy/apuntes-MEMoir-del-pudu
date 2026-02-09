

template <typename T>
optional<pair<Point<T>, Point<T>>> circleCircleIntersection(Point<T> c1, T r1,
                                                            Point<T> c2, T r2) {
  T dx = c2.x - c1.x;
  T dy = c2.y - c1.y;

  // Same center
  if (abs(dx) < EPS && abs(dy) < EPS)
    return nullopt;

  T A = -2 * dx;
  T B = -2 * dy;
  T C = dx * dx + dy * dy + r1 * r1 - r2 * r2;

  Point<T> p1(0, 0), p2(0, 0);

  if (abs(B) > EPS) {
    p1 = Point<T>(0, -C / B);
    p2 = Point<T>(1, -(A + C) / B);
  } else {
    p1 = Point<T>(-C / A, 0);
    p2 = Point<T>(-C / A, 1);
  }

  auto result = circleLineIntersection(r1, p1, p2);

  if (!result)
    return nullopt;

  result->first.x += c1.x;
  result->first.y += c1.y;
  result->second.x += c1.x;
  result->second.y += c1.y;

  return result;
}

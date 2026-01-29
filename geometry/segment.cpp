inline int sign(ll x) {
  if (x == 0)
    return 0;

  return x > 0 ? 1 : -1;
}

inline bool intersect(ll a, ll b, ll c, ll d) {
  if (a > b)
    swap(a, b);

  if (c > d)
    swap(c, d);

  return max(a, c) <= min(b, d);
}

template <class T> struct Segment {
  Point<T> a, b;

  Segment() {}
  Segment(Point<T> a, Point<T> b) : a(a), b(b) {}

  friend istream &operator>>(istream &is, Segment &segment) {
    is >> segment.a >> segment.b;
    return is;
  }

  // Highly tested
  bool intersects(const Segment &other) const {
    Point<T> c = other.a, d = other.b;

    if (c.cross(a, d) == 0 && c.cross(b, d) == 0)
      return intersect(a.x, b.x, c.x, d.x) && intersect(a.y, b.y, c.y, d.y);

    return sign(a.cross(b, c)) != sign(a.cross(b, d)) &&
           sign(c.cross(d, a)) != sign(c.cross(d, b));
  }

  // Not tested
  pair<bool, pair<Point<T>, Point<T>>>
  getIntersection(const Segment &other) const {
    if (!intersects(other))
      return {false, {{0, 0}, {0, 0}}};

    Point<T> c = other.a, d = other.b;
    Point<T> ab = b - a, cd = d - c, ac = c - a;

    T det = ab.cross(cd);

    // If not using integers consider using EPS
    if (det == 0) {
      Point<T> leftA = min(a, b), rightA = max(a, b);
      Point<T> leftB = min(c, d), rightB = max(c, d);

      Point<T> start = max(leftA, leftB);
      Point<T> end = min(rightA, rightB);

      return {true, {start, end}};
    }

    // This maybe fail using integers, consider using long double
    T t = ac.cross(cd) / det;

    Point<T> intersectionPoint(a.x + (b.x - a.x) * t, a.y + (b.y - a.y) * t);

    return {true, {intersectionPoint, intersectionPoint}};
  }
};
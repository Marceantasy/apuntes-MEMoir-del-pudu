

template <class T> struct Line {
  Point<T> a, b;
  double angle;

  Line() {}
  Line(Point<T> a, Point<T> b) : a(a), b(b), angle((b - a).angle()) {}

  bool operator<(const Line &other) const { return angle < other.angle; }

  pair<int, pair<Point<T>, Point<T>>> intersect(const Line &other) const {
    Point<T> ab = b - a;
    Point<T> cd = other.b - other.a;
    Point<T> ac = other.a - a;
    T det = ab.cross(cd);

    if (abs(det) <= EPS) {
      // Same line
      if (ab.cross(other.a - a) == 0)
        return {2, {a, b}};

      // Paralels
      return {0, {Point<T>(0, 0), Point<T>(0, 0)}};
    }

    // Unique intersection
    // This maybe fail using integers, consider using long double
    T t = ac.cross(cd) / det;
    Point<T> point(a.x + ab.x * t, a.y + ab.y * t);

    return {1, {point, point}};
  }

  // For Half-plane-intersection
  Point<T> getPoint(const Line &other) const {
    Point<T> ab = b - a, cd = other.b - other.a, ac = other.a - a;
    T det = ab.cross(cd);
    return Point<T>(a.x + ab.x * ac.cross(cd) / det,
                    a.y + ab.y * ac.cross(cd) / det);
  }

  // Check if point is at right of the line
  bool out(const Point<T> &point) const { return point.left(a, b) < 0; }
};
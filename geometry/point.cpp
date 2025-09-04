template <class T> struct Point {
  T x, y;

  Point() {}
  Point(T x, T y) : x(x), y(y) {}

  friend istream &operator>>(istream &is, Point &point) {
    is >> point.x >> point.y;
    return is;
  }

  Point operator-(const Point &point) const {
    return Point(x - point.x, y - point.y);
  }

  T cross(const Point &point) const { return x * point.y - y * point.x; }

  T cross(const Point &a, const Point &b) const {
    return (a - *this).cross(b - *this);
  }
};

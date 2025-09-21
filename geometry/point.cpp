template <class T> struct Point {
  T x, y;

  Point() {}
  Point(T x, T y) : x(x), y(y) {}

  friend istream &operator>>(istream &is, Point &point) {
    is >> point.x >> point.y;
    return is;
  }

  bool operator==(const Point &point) const {
    return point.x == x && point.y == y;
  }

  bool operator!=(const Point &point) const { return !(point == *this); }

  bool operator<(const Point &point) const {
    if (x == point.x)
      return y < point.y;

    return x < point.x;
  }

  bool operator>(const Point &point) const {
    return !(*this > point) && (*this != point);
  }

  bool operator>=(const Point &point) {
    return *this > point || *this == point;
  }

  bool operator<=(const Point &point) {
    return *this < point || *this == point;
  }

  Point operator+(const Point &point) const {
    return Point(x + point.x, y + point.y);
  }

  Point operator-(const Point &point) const {
    return Point(x - point.x, y - point.y);
  }

  Point operator+(T value) const { return Point(x + value, y + value); }

  Point operator-(T value) const { return Point(x - value, y - value); }

  T cross(const Point &point) const { return x * point.y - y * point.x; }

  T cross(const Point &a, const Point &b) const {
    return (a - *this).cross(b - *this);
  }

  T squaredLength() const { return x * x + y * y; }

  T squaredDistance(const Point &point) {
    T deltaX = point.x - x, deltaY = point.y - y;

    return deltaX * deltaX + deltaY * deltaY;
  }

  T distance(const Point &point) { return sqrt(squaredDistance(point)); }
};

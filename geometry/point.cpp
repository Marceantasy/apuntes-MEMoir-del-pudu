

template <class T> struct Point {
  T x, y;

  const T EPS = 0;

  Point() {}
  Point(T x, T y) : x(x), y(y) {}

  friend istream &operator>>(istream &is, Point &point) {
    is >> point.x >> point.y;
    return is;
  }

  bool operator=(const Point &point) const { return Point(x, y); }

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

  Point operator*(T v) const { return Point(x * v, y * v); }

  Point operator/(T v) const { return Point(x / v, y / v); }

  T dot(const Point &other) const { return x * other.x + y * other.y; }

  T cross(const Point &point) const { return x * point.y - y * point.x; }

  T cross(const Point &a, const Point &b) const {
    return (a - *this).cross(b - *this);
  }

  int left(const Point &point) const {
    T crossProduct = this->cross(point);

    if (abs(crossProduct) < EPS)
      return 0;

    if (crossProduct > EPS)
      return 1;

    return -1;
  }

  int left(const Point &a, const Point &b) const {
    T crossProduct = this->cross(a, b);

    if (abs(crossProduct) < EPS)
      return 0;

    if (crossProduct > EPS)
      return 1;

    return -1;
  }

  T squaredLength() const { return x * x + y * y; }

  T squaredDistance(const Point &point) {
    T deltaX = point.x - x, deltaY = point.y - y;

    return deltaX * deltaX + deltaY * deltaY;
  }

  T distance(const Point &point) { return sqrt(squaredDistance(point)); }

  void rotate(T radians) {
    T newX = x * cos(radians) - y * sin(radians),
      newY = x * sin(radians) + y * cos(radians);

    x = newX, y = newY;
  };

  double angle() { return atan2(y, x); }

  bool isUpperHull() const { return y > 0 || (y == 0 && x > 0); }

  bool angle_lt(const Point &other) const {
    if (isUpperHull() != other.isUpperHull())
      return isUpperHull();

    return left(other) == 1; // cross(other)> 0
  }
};

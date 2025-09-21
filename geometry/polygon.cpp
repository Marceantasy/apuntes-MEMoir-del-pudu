template <class T> struct Polygon {
  vector<Point<T>> points, relative;
  int n;

  int sign(T value) {
    if (value == 0)
      return 0;

    return value > 0 ? 1 : -1;
  }

  Polygon(const int n) {
    this->n = n;
    points.resize(n);
  }
  Polygon(const vector<Point<T>> &points) : points(points), n(points.size()) {}

  friend istream &operator>>(istream &is, Polygon &polygon) {
    for (auto &point : polygon.points)
      is >> point;
    return is;
  }

  T doubleArea() {
    T sum = 0;

    for (int i = 0; i < n; i++)
      sum += points[i].cross(points[(i + 1) % n]);

    return abs(sum);
  }

  T area() { return doubleArea() / 2; }

  T boundaryLatticePoints() {
    T count = 0;

    for (int i = 0; i < n; i++) {
      Point<T> delta = points[i] - points[(i + 1) % n];
      count += gcd(abs(delta.x), abs(delta.y));
    }

    return count;
  }

  T insideLatticePoints() {
    return (doubleArea() - boundaryLatticePoints()) / 2 + 1;
  }

  T latticePoints() { return boundaryLatticePoints() + insideLatticePoints(); }
};
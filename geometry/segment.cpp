int sign(ll x) {
  if (x == 0)
    return 0;

  return x > 0 ? 1 : -1;
}

bool intersect(ll a, ll b, ll c, ll d) {
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

  bool intersects(const Segment &segment) const {
    Point<T> c = segment.a, d = segment.b;

    if (c.cross(a, d) == 0 && c.cross(b, d) == 0)
      return intersect(a.x, b.x, c.x, d.x) && intersect(a.y, b.y, c.y, d.y);

    return sign(a.cross(b, c)) != sign(a.cross(b, d)) &&
           sign(c.cross(d, a)) != sign(c.cross(d, b));
  }
};
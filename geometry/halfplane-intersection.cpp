// obtain the convex polygon that results from intersecting the given list
// of halfplanes, represented as lines that allow their left side
// assumes the halfplane intersection is bounded

template <class T>
vector<Point<T>> halfPlaneIntersection(vector<Line<T>> lines) {

  // add box if needed
  lines.push_back(Line(Point(-INF, -INF), Point(INF, -INF)));
  lines.push_back(Line(Point(INF, -INF), Point(INF, INF)));
  lines.push_back(Line(Point(INF, INF), Point(-INF, INF)));
  lines.push_back(Line(Point(-INF, INF), Point(-INF, -INF)));

  sort(lines.begin(), lines.end());

  // q: start, h: end
  int n = lines.size(), q = 1, h = 0;

  // just a silly deque
  vector<Line<T>> c(n + 2);

  for (int i = 0; i < n; i++) {
    while (q < h && lines[i].out(c[h].getPoint(c[h - 1])))
      h--;

    while (q < h && lines[i].out(c[q].getPoint(c[q + 1])))
      q++;

    c[++h] = lines[i];

    // check if parallel
    // If not using integers consider using EPS
    if (q < h && abs((c[h].b - c[h].a).cross(c[h - 1].b - c[h - 1].a)) == 0) {

      // if parallel are oposite, returns null answer
      if ((c[h].b - c[h].a).dot(c[h - 1].b - c[h - 1].a) <= 0)
        return {};

      h--;

      if (lines[i].out(c[h].a))
        c[h] = lines[i];
    }
  }

  while (q < h - 1 && c[q].out(c[h].getPoint(c[h - 1])))
    h--;

  while (q < h - 1 && c[h].out(c[q].getPoint(c[q + 1])))
    q++;

  // No intersection
  if (h - q <= 1)
    return {};

  vector<Point<T>> polygon;
  c[h + 1] = c[q];
  for (int i = q; i <= h; i++)
    polygon.push_back(c[i].getPoint(c[i + 1]));

  return polygon;
}
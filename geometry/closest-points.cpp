
// Marcelo
// sort by x
ll closest(vector<ii> &p) {
  int n = SZ(p);
  set<ii> s;
  ll best = 1e18;
  int j = 0;
  fore(i, 0, n) {
    ll d = ceil(sqrt(best));
    while (p[i].fst - p[j].fst >= best)
      s.erase({p[j].snd, p[j].fst}), j++;
    auto it1 = s.lower_bound({p[i].snd - d, p[i].fst});
    auto it2 = s.upper_bound({p[i].snd + d, p[i].fst});
    for (auto it = it1; it != it2; ++it) {
      ll dx = p[i].fst - it->snd;
      ll dy = p[i].snd - it->fst;
      best = min(best, dx * dx + dy * dy);
    }
    s.insert({p[i].snd, p[i].fst});
  }
  return best;
}

// Enzo
template <class T>
pair<ll, pair<Point<T>, Point<T>>> closest(vector<Point<T>> points) {
  int n = points.size();
  sort(points.begin(), points.end()); // sort by x

  // sort by y
  auto compare = [](const Point<T> &a, const Point<T> &b) {
    if (a.y != b.y)
      return a.y < b.y;
    return a.x < b.x;
  };

  set<Point<T>, decltype(compare)> uniques(compare);

  ll best = INF;
  pair<Point<T>, Point<T>> answer;

  int j = 0;
  for (int i = 0; i < n; i++) {
    while (j < i && points[i].x - points[j].x >= best)
      uniques.erase(points[j++]);

    ll distance = sqrt(best) + 1;

    // [y_i - d, y_i + d]
    auto start = uniques.lower_bound(Point<T>(-INF, points[i].y - distance));
    auto end = uniques.upper_bound(Point<T>(INF, points[i].y + distance));

    for (auto it = start; it != end; it++) {
      ll current = points[i].squaredDistance(*it);

      if (best <= current)
        continue;

      best = current;
      answer = {points[i], *it};
    }

    uniques.insert(points[i]);
  }

  return {best, answer};
}
// Check if point is in Triangle abc
// IMPORTANT: Points on the edge are considered inside
// IMPORTANT: Check for overflow (int128 may be needed)
bool pointInTriangle(Point a, Point b, Point c, Point point) {
  auto area = absolute(a.cross(b, c));
  auto candidateArea = absolute(point.cross(a, b)) +
                       absolute(point.cross(b, c)) +
                       absolute(point.cross(c, a));

  return area == candidateArea;
}

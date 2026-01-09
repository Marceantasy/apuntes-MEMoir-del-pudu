// Check if point is in Triangle abc
// IMPORTANT: Points on the edge are considered inside
// IMPORTANT: Check for overflow (int128 may be needed)
// int128 needs custom abs function
bool pointInTriangle(Point a, Point b, Point c, Point point) {
  auto area = abs(a.cross(b, c));
  auto candidateArea =
      abs(point.cross(a, b)) + abs(point.cross(b, c)) + abs(point.cross(c, a));

  return area == candidateArea;
}

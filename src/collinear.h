#pragma once

#include <cstddef>
#include <iosfwd>
#include <vector>

class Point {
public:
  int x{};
  int y{};
  Point() = default;
  Point(int &x, int &y) : x{x}, y{y} {}

  friend bool operator==(const Point &p1, const Point &p2);
  friend bool operator!=(const Point &p1, const Point &p2);
};

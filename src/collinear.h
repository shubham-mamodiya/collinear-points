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

class Slope {
public:
  int numerator{};
  int denominator{};
  std::size_t index{}; // for referencing index to some array.
  // just to save some cost when sorting. It will tell the
  // index of the point in actual points array.

  Slope() = default;

  Slope(int &numerator, int &denominator)
      : numerator{numerator}, denominator{denominator} {}

  friend bool operator==(const Slope &a, const Slope &b);
  friend bool operator<(const Slope &a, const Slope &b);
  friend bool operator>(const Slope &a, const Slope &b);
};

class LineSegment {
public:
  Point a{};
  Point b{};
};

std::istream &operator>>(std::istream &in, Point &p);
std::ostream &operator<<(std::ostream &out, const Point &p);

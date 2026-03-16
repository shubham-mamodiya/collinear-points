#include "collinear.h"

#include <cstddef>
#include <iostream>
#include <ostream>
#include <vector>

std::istream &operator>>(std::istream &in, Point &p) {
  return in >> p.x >> p.y;
}

std::ostream &operator<<(std::ostream &out, const Point &p) {
  return out << p.x << " " << p.y;
}

bool operator==(const Slope &a, const Slope &b) {
  return a.numerator * b.denominator == b.numerator * a.denominator;
}

bool operator<(const Slope &a, const Slope &b) {
  return (__int128)a.numerator * b.denominator <
         (__int128)b.numerator * a.denominator;
}

bool operator>(const Slope &a, const Slope &b) {
  return (__int128)a.numerator * b.denominator >
         (__int128)b.numerator * a.denominator;
}

bool operator==(const Point &p1, const Point &p2) {
  return p1.x == p2.x && p1.y == p2.y;
}

bool operator!=(const Point &p1, const Point &p2) {
  return p1.x != p2.x && p1.y != p2.y;
}

std::vector<LineSegment> find_segments(const std::vector<Point> points) {
  std::size_t size{points.size()};
  std::vector<LineSegment> segments{};
  std::vector<Slope> slopes;
  for (std::size_t i{}; i < size; ++i) {
    cal_slope(i, points, slopes);
    merge_sort(slopes);
    auto occ = occurences(slopes);
  }

  return segments;
}

void cal_slope(std::size_t with_this, const std::vector<Point> points,
               std::vector<Slope> &slopes) {
  std::size_t size{points.size()};

  if (slopes.size() != size) {
    slopes.resize(size);
  }

  for (std::size_t i{}; i < size; ++i) {
    slopes[i].numerator = points[i].y - points[with_this].y;
    slopes[i].denominator = points[i].x - points[with_this].x;
    slopes[i].index = i; // we will this index for referencing after we sort the
    // array.
  }
}

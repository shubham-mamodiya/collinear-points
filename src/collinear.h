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
  friend bool operator<(const Point &p1, const Point &p2);
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
  friend bool operator>(const Point &p1, const Point &p2);
};

class LineSegment {
public:
  Point a{};
  Point b{};
};

std::istream &operator>>(std::istream &in, Point &p);
std::ostream &operator<<(std::ostream &out, const Point &p);

void merge_sort(std::vector<Slope> &slopes);

void sort(int lo, int hi, std::vector<Slope> &arr, std::vector<Slope> &aux);

void merge(int lo, int mid, int hi, std::vector<Slope> &arr,
           std::vector<Slope> &aux);

std::vector<LineSegment> find_segments(const std::vector<Point> &points);

void cal_slope(std::size_t with_this, const std::vector<Point> &points,
               std::vector<Slope> &slopes);

std::vector<LineSegment> occurrences(const Point &origin_point,
                                     const std::vector<Slope> &slopes,
                                     const std::vector<Point> &points);

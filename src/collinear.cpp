#include "collinear.h"

#include <algorithm>
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
  __int128 diff_num = (__int128)a.numerator * b.denominator -
                      (__int128)b.numerator * a.denominator;
  __int128 denom_product = (__int128)a.denominator * b.denominator;
  // sign(diff_num / denom_product) < 0
  // i.e. diff_num and denom_product have opposite signs
  return (diff_num < 0) != (denom_product < 0);
}

bool operator>(const Slope &a, const Slope &b) {
  __int128 diff_num = (__int128)a.numerator * b.denominator -
                      (__int128)b.numerator * a.denominator;
  __int128 denom_product = (__int128)a.denominator * b.denominator;
  // same signs → positive result → a/b > c/d
  return (diff_num < 0) == (denom_product < 0) && diff_num != 0;
}

bool operator==(const Point &p1, const Point &p2) {
  return p1.x == p2.x && p1.y == p2.y;
}

bool operator!=(const Point &p1, const Point &p2) {
  return p1.x != p2.x || p1.y != p2.y;
}

bool operator<(const Point &p1, const Point &p2) {
  if (p1.y == p2.y) {
    return p1.x < p2.x;
  }

  return p1.y < p2.y;
}

bool operator>(const Point &p1, const Point &p2) {
  if (p1.y == p2.y) {
    return p1.x > p2.x;
  }

  return p1.y > p2.y;
}

std::vector<LineSegment> find_segments(const std::vector<Point> &points) {
  std::size_t size{points.size()};
  std::vector<LineSegment> segments{};
  // exclude the origin
  std::vector<Slope> slopes(points.size() - 1);

  for (std::size_t i{}; i < size; ++i) {
    cal_slope(i, points, slopes);
    merge_sort(slopes);
    auto temp{occurrences(points[i], slopes, points)};

    segments.insert(segments.end(), temp.begin(), temp.end());
  }
  return segments;
}

void cal_slope(std::size_t with_this, const std::vector<Point> &points,
               std::vector<Slope> &slopes) {
  std::size_t size{points.size()};

  if (slopes.size() != size - 1) {
    slopes.resize(size);
  }
  std::size_t j{};
  for (std::size_t i{}; i < size; ++i) {
    if (i == with_this) {
      continue; // for the origin point
    }
    slopes[j].numerator = points[i].y - points[with_this].y;
    slopes[j].denominator = points[i].x - points[with_this].x;
    slopes[j].index = i; // we will this index for referencing after we sort the
    // array.
    ++j;
  }
}

void merge_sort(std::vector<Slope> &slopes) {
  std::vector<Slope> aux{slopes};
  if (!slopes.empty()) {
    sort(0, slopes.size() - 1, slopes, aux);
  }
}

void sort(int lo, int hi, std::vector<Slope> &arr, std::vector<Slope> &aux) {
  // not necessary right now we are not gonna use it anywhere else
  // if (lo < 0 || hi < 0) {
  //   throw std::runtime_error(
  //       "You can not pass negative lo or hi to the sort function.");
  // }

  if (lo >= hi) {
    return;
  }

  int mid{lo + ((hi - lo) / 2)};
  sort(lo, mid, arr, aux);
  sort(mid + 1, hi, arr, aux);
  merge(lo, mid, hi, arr, aux);
}

void merge(int lo, int mid, int hi, std::vector<Slope> &arr,
           std::vector<Slope> &aux) {
  // Not necessary right now
  // if (lo < 0 || mid < 0 || hi < 0) {
  //   throw std::runtime_error(
  //       "You can not pass negative lo, mid or hi to the merge function.");
  // }
  //
  // if (mid < lo) {
  //   throw std::runtime_error(
  //       "mid parameter should not be less then lo parameter.");
  // }
  // if (hi < mid) {
  //   throw std::runtime_error(
  //       "hi parameter should not be less then lo or mid parameter.");
  // }

  int i{lo}, j{mid + 1};
  for (int k{i}; k <= hi; ++k) {
    if (i > mid) {
      aux[k] = arr[j++];
    } else if (j > hi) {
      aux[k] = arr[i++];
    } else if (arr[j] < arr[i]) {
      aux[k] = arr[j++];
    } else {
      aux[k] = arr[i++];
    }
  }

  for (int i{lo}; i <= hi; ++i) {
    arr[i] = aux[i];
  }
}

std::vector<LineSegment> occurrences(const Point &origin_point,
                                     const std::vector<Slope> &slopes,
                                     const std::vector<Point> &points) {
  std::size_t size{slopes.size()};
  std::vector<LineSegment> results{};
  if (size <= 1) {
    return results;
  }

  // this limit will actually find minimum_limit + 1 collinear points
  // because origin_point is collinear too
  const int minimum_limit{3};
  int newly_found{};

  auto smallest_point{origin_point};
  auto biggest_point{origin_point};

  for (std::size_t i{1}; i < size; ++i) {
    if (slopes[i] == slopes[i - 1]) {

      // we naturally find two collinear points, the is no single collinear
      // point
      newly_found += (newly_found == 0) ? 2 : 1;

      std::size_t x{slopes[i - 1].index};
      std::size_t y{slopes[i].index};

      smallest_point = std::min(points[x], std::min(points[y], origin_point));
      biggest_point = std::max(points[x], std::max(points[y], origin_point));

      continue;
    }

    if (newly_found >= minimum_limit) {
      if (smallest_point != biggest_point) {
        results.push_back({smallest_point, biggest_point});
      }
    }

    newly_found = 0;
    smallest_point = origin_point;
    biggest_point = origin_point;
  }
  if (newly_found >= minimum_limit) {
    if (smallest_point != biggest_point) {
      results.push_back({smallest_point, biggest_point});
    }
  }
  return results;
}

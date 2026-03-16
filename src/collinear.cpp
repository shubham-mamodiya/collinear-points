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

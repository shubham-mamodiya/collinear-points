#include <filesystem>
#include <fstream>
#include <iostream>
#include <vector>

#include "collinear.h"

std::vector<Point> read_points(const std::filesystem::path &path) {

  if (!std::filesystem::exists(path)) {
    throw std::runtime_error("File Not Found" + path.string());
  }

  std::ifstream file{path};

  if (!file) {
    throw std::runtime_error(path.string() + "Could Not be opened.");
  }

  int size{};
  file >> size;

  std::vector<Point> points{};
  points.reserve(size);

  int x{}, y{};
  while (file >> x >> y) {
    points.emplace_back(x, y);
  }

  return points;

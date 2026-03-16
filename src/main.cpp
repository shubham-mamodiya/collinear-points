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
}

int main(int argc, char *argv[]) {
  if (argc != 3) {
    std::cerr
        << "Usage [.Executable] [data file path] [result file location]\n";
    return 3;
  }

  std::filesystem::path input_file{argv[1]};
  auto points{read_points(input_file)};

  [[maybe_unused]] std::vector<LineSegment> seg = find_segments(points);

  return 0;
}

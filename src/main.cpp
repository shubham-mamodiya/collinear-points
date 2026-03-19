#include <cstddef>
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

void write_segments_csv(const std::filesystem::path &path,
                        const std::vector<LineSegment> &seg) {
  char permition{'n'};
  if (std::filesystem::exists(path)) {
    std::cout << path.string()
              << " already exists.\n\tDo you want to override it: ";
    std::cin >> permition;
    if (permition != 'y' && permition != 'Y') {
      std::cout << "We are not overriding it.\n";
      return;
    }
  }
  std::ofstream file{path};
  if (!file) {
    std::cerr << "Cat write to the file.\n";
    return;
  }

  const std::size_t size{seg.size()};

  for (std::size_t i{}; i < size; ++i) {
    auto segment = seg[i];
    auto a = segment.a;
    auto b = segment.b;
    file << a.x << " , " << a.y << " , " << b.x << " , " << b.y << "\n";
  }
}

// so I can just use pandas to read points
void convert_to_csv(const std::filesystem::path &path) {
  std::ifstream input{path};

  std::filesystem::path output_path{path};
  output_path.replace_extension(".csv");
  std::ofstream output{output_path};

  if (!output || !input) {
    std::cerr << "Cat write to the file.\n";
    return;
  }

  int temp{};
  input >> temp;

  int x{}, y{};
  while (input >> x >> y) {
    output << x << " , " << y << "\n";
  }
}

int main(int argc, char *argv[]) {
  if (argc != 3) {
    std::cerr
        << "Usage [.Executable] [data file path] [result file location]\n";
    return 3;
  }
  auto input_path{argv[1]};
  auto output_path{argv[2]};
  std::filesystem::path input_file{input_path};
  auto points{read_points(input_file)};
  convert_to_csv(input_path);
  [[maybe_unused]] auto seg = find_segments(points);
  write_segments_csv(output_path, seg);
  return 0;
}

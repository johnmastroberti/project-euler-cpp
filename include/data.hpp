#pragma once
#include <fstream>

#include "common.hpp"

template <typename T>
auto get_data(const char* filename, int N) {
  std::vector<T> data;

  std::ifstream datafile(filename);
  if (!datafile.good()) {
    spdlog::error("Could not open {} for reading");
    return data;
  }

  data.reserve(N);
  std::copy_n(std::istream_iterator<T>(datafile), N, std::back_inserter(data));
  return data;
}

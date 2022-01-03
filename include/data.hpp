#pragma once
#include <fstream>

#include "common.hpp"

template <typename T>
auto get_data(const char* filename, size_t N = 0) {
  std::vector<T> data;

  std::ifstream datafile(filename);
  if (!datafile.good()) {
    spdlog::error("Could not open {} for reading");
    return data;
  }

  if constexpr (std::is_same_v<T, char> || std::is_same_v<T, unsigned char>)
    datafile >> std::noskipws;

  if (N > 0) {
    data.reserve(N);
    std::copy_n(std::istream_iterator<T>(datafile), N,
                std::back_inserter(data));
  } else {
    std::copy(std::istream_iterator<T>(datafile), std::istream_iterator<T>(),
              std::back_inserter(data));
  }
  return data;
}

#include <cctype>
#include <cstddef>
#include <fstream>
#include <iostream>
#include <limits>
#include <new>
#include <stdexcept>

namespace serdyukov {
  void leftBottomSpiral(int *matrix, int rows, int columns);
  bool isNumber(const char *cstring);
  constexpr int fixed_size = 10000;
}

int main(int argc, char *argv[])
{
  if (argc < 4) {
    std::cerr << "Not enough arguments\n";
    return 1;
  }
  if (argc > 4) {
    std::cerr << "Too many arguments\n";
    return 1;
  }
  if ((argv[1][0] != '1' && argv[1][0] != '2') || argv[1][1] != '\0') {
    if (serdyukov::isNumber(argv[1])) {
      std::cerr << "First parameter is out of range\n";
    } else {
      std::cerr << "First parameter is not a number\n";
    }
    return 1;
  }
  const int mode = argv[1][0] - '0';

  std::ifstream input(argv[2]);
  if (!input) {
    std::cerr << "Cannot open file\n";
    return 2;
  }
  int rows = 0;
  int columns = 0;
  if (!(input >> rows >> columns) || rows < 0 || columns < 0 || ((rows == 0) != (columns == 0))) {
    std::cerr << "Incorrect size\n";
    return 2;
  }
  if (rows != 0 && std::numeric_limits< int >::max() / rows < columns) {
    std::cerr << "Too much elements\n";
    return 2;
  }
  const int elements = rows * columns;
  int *matrix = nullptr;

  try {
    int fixed[serdyukov::fixed_size];
    if (mode == 1 && elements > 0) {
      if (elements > serdyukov::fixed_size) {
        std::cerr << "Too much elements for static mode\n";
        return 2;
      }
      matrix = fixed;
    } else if (mode == 2 && elements > 0) {
      matrix = new int[elements];
    }
    for (int i = 0; i < elements; ++i) {
      if (!(input >> matrix[i])) {
        throw std::invalid_argument("Invalid matrix elements");
      }
    }
    char extra = 0;
    if (input >> extra) {
      std::cerr << "Extra data in input file\n";
      if (mode == 2) {
        delete[] matrix;
        matrix = nullptr;
      }
      return 2;
    }
    std::ofstream output(argv[3]);
    if (!output) {
      std::cerr << "Cannot open output file\n";
      if (mode == 2) {
        delete[] matrix;
        matrix = nullptr;
      }
      return 4;
    }
    output << rows << ' ' << columns << ' ';
    if (elements == 0) {
      return 0;
    }
    serdyukov::leftBottomSpiral(matrix, rows, columns);
    for (int i = 0; i < elements; ++i) {
      output << matrix[i] << ' ';
    }
    if (mode == 2) {
      delete[] matrix;
      matrix = nullptr;
    }
    return 0;
  } catch (const std::bad_alloc &) {
    std::cerr << "Memory allocation failed\n";
    return 3;
  } catch (const std::invalid_argument &e) {
    if (mode == 2) {
      delete[] matrix;
    }
    matrix = nullptr;
    std::cerr << e.what() << '\n';
    return 2;
  }
}

bool serdyukov::isNumber(const char *cstring)
{
  if (cstring[0] != '-' && !std::isdigit(static_cast< unsigned char >(cstring[0]))) {
    return false;
  }
  size_t i = 1;
  while (cstring[i] != '\0') {
    if (!std::isdigit(static_cast< unsigned char >(cstring[i]))) {
      return false;
    }
    i++;
  }
  if (cstring[0] == '-' && cstring[1] == '\0') {
    return false;
  }
  return true;
}

void serdyukov::leftBottomSpiral(int *matrix, int rows, int columns)
{
  int change = 1;
  int top = 0;
  int bottom = rows - 1;
  int left = 0;
  int right = columns - 1;

  while (top <= bottom && left <= right) {
    for (int c = left; c <= right; ++c) {
      matrix[bottom * columns + c] += change;
      change++;
    }
    --bottom;
    for (int r = bottom; r >= top; --r) {
      matrix[r * columns + right] += change;
      change++;
    }
    --right;
    for (int c = right; c >= left; --c) {
      matrix[top * columns + c] += change;
      change++;
    }
    ++top;
    for (int r = top; r <= bottom; ++r) {
      matrix[r * columns + left] += change;
      change++;
    }
    ++left;
  }
}

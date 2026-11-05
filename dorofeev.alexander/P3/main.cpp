#include <exception>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <stdexcept>

namespace dorofeev {
  void lftBotCnt(int *m, int rows, int cols)
  {
    int top = 0;
    int bottom = rows - 1;
    int left = 0;
    int right = cols - 1;
    int step = 1;
    while (top <= bottom && left <= right) {
      for (int j = left; j <= right; ++j) {
        m[bottom * cols + j] += step;
        ++step;
      }
      --bottom;

      for (int i = bottom; i >= top; --i) {
        m[i * cols + right] += step;
        ++step;
      }
      --right;

      if (top <= bottom) {
        for (int j = right; j >= left; --j) {
          m[top * cols + j] += step;
          ++step;
        }
        ++top;
      }

      if (left <= right) {
        for (int i = top; i <= bottom; ++i) {
          m[i * cols + left] += step;
          ++step;
        }
        ++left;
      }
    }
  }
}

int main(int argc, char **argv)
{
  if (argc != 4) {
    std::cerr << "Error: wrong number of arguments\n";
    return 1;
  }

  const int decimalBase = 10;
  char *end = nullptr;
  const long num = std::strtol(argv[1], &end, decimalBase);
  if (*end != '\0' || (num != 1 && num != 2)) {
    std::cerr << "Error: first argument must be 1 or 2\n";
    return 1;
  }

  std::ifstream in(argv[2]);
  if (!in) {
    std::cerr << "Error: cannot open input file\n";
    return 2;
  }

  int rows = 0;
  int cols = 0;
  if (!(in >> rows >> cols) || rows < 0 || cols < 0) {
    std::cerr << "Error: invalid matrix size\n";
    return 1;
  }

  const int total = rows * cols;

  const int maxFixedSize = 10000;
  int fixed[maxFixedSize];
  int *data = nullptr;
  try {
    if (num == 1 && total > maxFixedSize) {
      throw std::runtime_error("matrix too large");
    }

    if (num == 1) {
      if (total > 0) {
        data = fixed;
      }
    } else {
      if (total > 0) {
        data = new int[total];
      }
    }

    for (int i = 0; i < total; ++i) {
      if (!(in >> data[i])) {
        throw std::runtime_error("invalid matrix element");
      }
    }

    dorofeev::lftBotCnt(data, rows, cols);

    std::ofstream out(argv[3]);
    if (!out) {
      throw std::runtime_error("cannot open output file");
    }
    out << rows << " " << cols;
    for (int i = 0; i < total; ++i) {
      out << " " << data[i];
    }
    out << "\n";
  } catch (const std::bad_alloc &) {
    std::cerr << "Error: not enough memory\n";
    if (num == 2) {
      delete[] data;
    }
    return 2;
  } catch (const std::exception &e) {
    std::cerr << "Error: " << e.what() << "\n";
    if (num == 2) {
      delete[] data;
    }
    return 2;
  }

  if (num == 2) {
    delete[] data;
  }
  return 0;
}

#include <fstream>
#include <iostream>
#include <new>

namespace ermolaeva {
  static const int max_static = 10000;

  int parseMode(const char *arg);
  void readSizes(std::ifstream &in, int &rows, int &cols);
  void readElements(std::ifstream &in, int *buf, long long total);
  void transform(int *a, int rows, int cols);
  void writeMatrix(std::ofstream &out, const int *a, int rows, int cols);
}

int main(int argc, char *argv[])
{
  int *heap_arr = nullptr;
  try {
    if (argc != 4) {
      throw 1;
    }
    const int mode = ermolaeva::parseMode(argv[1]);

    std::ifstream in(argv[2]);
    if (!in) {
      throw 2;
    }
    int rows = 0, cols = 0;
    ermolaeva::readSizes(in, rows, cols);
    const long long total = 1LL * rows * cols;
    if (mode == 1) {
      if (total > ermolaeva::max_static) {
        throw 2;
      }
      int arr[ermolaeva::max_static];
      ermolaeva::readElements(in, arr, total);
      ermolaeva::transform(arr, rows, cols);
      std::ofstream out(argv[3]);
      if (!out) {
        throw 2;
      }
      ermolaeva::writeMatrix(out, arr, rows, cols);
    } else {
      heap_arr = new int[total > 0 ? total : 1];
      ermolaeva::readElements(in, heap_arr, total);
      ermolaeva::transform(heap_arr, rows, cols);
      std::ofstream out(argv[3]);
      if (!out) {
        throw 2;
      }
      ermolaeva::writeMatrix(out, heap_arr, rows, cols);
    }
  } catch (int code) {
    if (code == 1) {
      std::cerr << "invalid command line arg. Usage: ./lab num input output\n";
    } else {
      std::cerr << "Invalid input data or file error\n";
    }
    delete[] heap_arr;
    return code;
  } catch (const std::bad_alloc &) {
    std::cerr << "Not enough memory for  matrix\n";
    delete[] heap_arr;
    return 2;
  }
  delete[] heap_arr;
  return 0;
}

namespace ermolaeva {
  int parseMode(const char *arg)
  {
    if ((arg[0] == '1' || arg[0] == '2') && arg[1] == '\0') {
      return arg[0] - '0';
    }
    throw 1;
  }

  void readSizes(std::ifstream &in, int &rows, int &cols)
  {
    if (!(in >> rows >> cols) || rows < 0 || cols < 0) {
      throw 2;
    }
  }

  void readElements(std::ifstream &in, int *buf, long long total)
  {
    for (long long i = 0; i < total; i++) {
      if (!(in >> buf[i])) {
        throw 2;
      }
    }
    char extra = 0;
    if (in >> extra) {
      throw 2;
    }
  }

  void transform(int *a, int rows, int cols)
  {
    const long long total = 1LL * rows * cols;
    long long k = 1;
    int top = 0, bottom = rows - 1, left = 0, right = cols - 1;
    while (k <= total) {
      for (int r = top; r <= bottom; ++r) {
        a[r * rows + left] += k++;
      }
      ++left;
      if (k > total) {
        break;
      }
      for (int c = left; c <= right; ++c) {
        a[bottom * cols + c] += k++;
      }
      --bottom;
      if (k > total) {
        break;
      }
      for (int r = bottom; r >= top; --r) {
        a[r * cols + right] += k++;
      }
      --right;
      if (k > total) {
        break;
      }
      for (int c = right; c >= left; --c) {
        a[top * cols + c] += k++;
      }
      ++top;
    }
  }

  void writeMatrix(std::ofstream &out, const int *a, int rows, int cols)
  {
    out << rows << ' ' << cols;
    for (long long i = 0; i < 1LL * rows * cols; ++i) {
      out << ' ' << a[i];
    }
    out << '\n';
  }

}

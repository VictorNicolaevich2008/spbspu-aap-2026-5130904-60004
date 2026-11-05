#include <iostream>
#include <fstream>
#include <stdexcept>
#include <climits>
#include <exception>

namespace ibragimov {
  int numColLSR(const int *mat, int rows, int cols);
}

int main(int argc, char *argv[])
{
  int *d_mat = nullptr;
  const int mx_stat_size = 10000;
  try {
    if (argc != 4) {
      throw std::invalid_argument("Too many arguments");
    }

    int num = 0;

    if (argv[1][0] == '1' && argv[1][1] == '\0') {
      num = 1;
    } else if (argv[1][0] == '2' && argv[1][1] == '\0') {
      num = 2;
    } else {
      throw std::invalid_argument("First argument is out of range or is not a number");
    }

    std::ifstream input(argv[2]);

    if (!input) {
      throw std::runtime_error("Cannot open input file");
    }

    int rows = 0;
    int cols = 0;

    if (!(input >> rows >> cols)) {
      throw std::runtime_error("Incorrect matrix size input");
    }

    if (rows < 0 || cols < 0) {
      throw std::runtime_error("Incorrect matrix size input");
    }

    if ((rows == 0) != (cols == 0)) {
      throw std::runtime_error("Incorrect matrix size input");
    }

    if (cols != 0 && rows > INT_MAX / cols) {
      throw std::runtime_error("mat is too large");
    }

    const int count = rows * cols;

    if (num == 1 && count > mx_stat_size) {
      throw std::runtime_error("mat is too large");
    }

    int f_mat[mx_stat_size];
    int *mat = f_mat;

    if (num == 2 && count > 0) {
      d_mat = new int[count];
      mat = d_mat;
    }

    for (int i = 0; i < count; ++i) {
      if (!(input >> mat[i])) {
        throw std::runtime_error("Incorrect mat elements");
      }
    }

    const int result = ibragimov::numColLSR(mat, rows, cols);

    std::ofstream output(argv[3]);

    if (!output) {
      throw std::runtime_error("Cannot open output file");
    }

    output << result << std::endl;

    if (!output) {
      throw std::runtime_error("Cannot write output file");
    }

    delete[] d_mat;
    return 0;
  } catch (const std::invalid_argument &e) {
    std::cerr << e.what() << std::endl;
    delete[] d_mat;
    return 1;
  } catch (const std::exception &e) {
    std::cerr << e.what() << std::endl;
    delete[] d_mat;
    return 2;
  }
}

namespace ibragimov {
  int numColLSR(const int *mat, int rows, int cols)
  {
    int mx_len = 0;
    int res_col = 0;

    for (int j = 0; j < cols; ++j) {
      int now_len = 1;

      for (int i = 1; i < rows; ++i) {
        if (mat[i * cols + j] == mat[(i - 1) * cols + j]) {
          ++now_len;
        } else {
          now_len = 1;
        }

        if (now_len > mx_len) {
          mx_len = now_len;
          res_col = j + 1;
        }
      }

      if (mx_len == 0 && rows > 0) {
        mx_len = 1;
        res_col = j + 1;
      }
    }
    return res_col;
  }
}

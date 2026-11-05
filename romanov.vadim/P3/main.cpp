#include <fstream>
#include <iostream>
#include <stdexcept>
namespace romanov {
  const int max_elements = 10000;
  int matrixLocalMaxCount(int x, int y, int **arr);
  void creatingMatrix(int n, const char *input_file, const char *output_file);
}
int main(int arg_count, char *arg_values[])
{
  if (arg_count != 4) {
    std::cerr << "Wrong number of arguments\n";
    return 1;
  }
  if ((arg_values[1][0] != '1' && arg_values[1][0] != '2') || arg_values[1][1] != '\0') {
    std::cerr << "First parameter is not a number or number out of range\n";
    return 1;
  }
  int n = 0;
  if (arg_values[1][0] == '1') {
    n = 1;
  } else if (arg_values[1][0] == '2') {
    n = 2;
  }
  try {
    romanov::creatingMatrix(n, arg_values[2], arg_values[3]);
  } catch (std::logic_error &e) {
    std::cerr << e.what() << '\n';
    return 2;
  }
  return 0;
}
int romanov::matrixLocalMaxCount(int x, int y, int **arr)
{
  if (x < 3 || y < 3) {
    return 0;
  }
  int local_max_count = 0;
  for (int i = 1; i < x - 1; ++i) {
    for (int j = 1; j < y - 1; ++j) {
      const int cur = arr[i][j];
      const bool top_row = (cur > arr[i - 1][j - 1] && cur > arr[i - 1][j] && cur > arr[i - 1][j + 1]);
      const bool mid_row = (cur > arr[i][j - 1] && cur > arr[i][j + 1]);
      const bool bot_row = (cur > arr[i + 1][j - 1] && cur > arr[i + 1][j] && cur > arr[i + 1][j + 1]);
      const bool is_local_max = (top_row && mid_row && bot_row);
      if (is_local_max) {
        ++local_max_count;
      }
    }
  }
  return local_max_count;
}
void romanov::creatingMatrix(int n, const char *input_file, const char *output_file)
{
  std::ifstream input(input_file);
  int x = 0, y = 0;
  if (!(input >> x >> y) || x < 0 || y < 0) {
    throw std::logic_error("Not a matrix");
  }
  std::ofstream output(output_file);
  int result = 0;
  if (n == 1 && x * y > max_elements) {
    throw std::logic_error("Matrix too big");
  }
  if (n == 1) {
    int stack[max_elements];
    int *stack_matrix[max_elements];
    for (int i = 0; i < x; ++i) {
      stack_matrix[i] = &stack[i * y];
    }
    for (int i = 0; i < x; ++i) {
      for (int j = 0; j < y; ++j) {
        if (!(input >> stack_matrix[i][j])) {
          throw std::logic_error("Wrong matrix format");
        }
      }
    }
    result = matrixLocalMaxCount(x, y, stack_matrix);
  } else if (n == 2) {
    int **const matrix = new int *[x];
    for (int i = 0; i < x; ++i) {
      matrix[i] = new int[y];
    }
    for (int i = 0; i < x; ++i) {
      for (int j = 0; j < y; ++j) {
        if (!(input >> matrix[i][j])) {
          for (int k = 0; k < x; ++k) {
            delete[] matrix[k];
          }
          delete[] matrix;
          throw std::logic_error("Wrong matrix format");
        }
      }
    }
    result = matrixLocalMaxCount(x, y, matrix);
    for (int i = 0; i < x; ++i) {
      delete[] matrix[i];
    }
    delete[] matrix;
  }
  output << result;
}

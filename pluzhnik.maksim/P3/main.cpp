#include <cstdio>
#include <iostream>
#include <new>

namespace pluzhnik
{
  int countLocalMinima(const int *matrix, int rows, int cols);
}

int main(int argc, char *argv[])
{
  if (argc != 4)
  {
    std::cerr << "Error: Wrong number of arguments" << std::endl;
    return 1;
  }

  int mode = 0;
  if (std::sscanf(argv[1], "%d", &mode) != 1 || (mode != 1 && mode != 2))
  {
    std::cerr << "Error: mode" << std::endl;
    return 2;
  }

  if (std::freopen(argv[2], "r", stdin) == nullptr)
  {
    std::cerr << "Error: input file" << std::endl;
    return 2;
  }

  if (std::freopen(argv[3], "w", stdout) == nullptr)
  {
    std::cerr << "Error: output file" << std::endl;
    return 2;
  }

  int rows = 0;
  int cols = 0;
  if (!(std::cin >> rows >> cols) || rows < 0 || cols < 0)
  {
    std::cerr << "Error: size" << std::endl;
    return 2;
  }

  const int total_elements = rows * cols;
  int result = 0;

  if (mode == 1)
  {
    const int max_static_size = 10000;
    if (total_elements > max_static_size)
    {
      std::cerr << "Error: limit rows * cols" << std::endl;
      return 2;
    }
    int static_buffer[max_static_size];

    for (int i = 0; i < total_elements; ++i)
    {
      if (!(std::cin >> static_buffer[i]))
      {
        std::cerr << "Error: input data" << std::endl;
        return 2;
      }
    }

    result = pluzhnik::countLocalMinima(static_buffer, rows, cols);
  }
  else
  {
    int *const dynamic_buffer = new (std::nothrow) int[total_elements];
    if (dynamic_buffer == nullptr)
    {
      std::cerr << "Error: memory" << std::endl;
      return 2;
    }

    for (int i = 0; i < total_elements; ++i)
    {
      if (!(std::cin >> dynamic_buffer[i]))
      {
        std::cerr << "Error: data" << std::endl;
        delete[] dynamic_buffer;
        return 2;
      }
    }

    result = pluzhnik::countLocalMinima(dynamic_buffer, rows, cols);
    delete[] dynamic_buffer;
  }

  std::cout << result << std::endl;

  return 0;
}

namespace pluzhnik
{
  int countLocalMinima(const int *matrix, int rows, int cols)
  {
    int count = 0;
    for (int i = 1; i < rows - 1; ++i)
    {
      for (int j = 1; j < cols - 1; ++j)
      {
        const int number = matrix[i * cols + j];

        const int top = matrix[(i - 1) * cols + j];
        const int under = matrix[(i + 1) * cols + j];
        const int left = matrix[i * cols + (j - 1)];
        const int right = matrix[i * cols + (j + 1)];

        if (number < top && number < under && number < left && number < right)
        {
          count++;
        }
      }
    }

    return count;
  }
}


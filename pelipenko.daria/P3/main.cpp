#include <cstddef>
#include <fstream>
#include <iostream>
#include <new>
#include <stdexcept>

const int max_length = 10000;

namespace pelipenko
{
  void readMatrix(std::ifstream & in, int * arr, const std::size_t n, const std::size_t m)
  {
    for (std::size_t i = 0; i < n * m; ++i)
    {
      if (!(in >> arr[i]))
      {
        throw std::invalid_argument("Input error");
      }
    }

    int extra_element = 0;
    if (in >> extra_element)
    {
      throw std::invalid_argument("Input error");
    }
  }

  bool isUpperTriangular(const int * arr, const std::size_t n, const std::size_t m)
  {
    if (n != m)
    {
      return false;
    }

    for (std::size_t i = 0; i < n; ++i)
    {
      for (std::size_t j = 0; j < m; ++j)
      {
        if (i > j && arr[i * m + j] != 0)
        {
          return false;
        }
      }
    }

    return true;
  }

  void outputMatrix(const char * file, const bool result)
  {
    std::ofstream out(file);
    if (!out.is_open())
    {
      throw std::runtime_error("Could not open output file");
    }

    out << (result ? "true" : "false") << '\n';
  }
}

int main(int argc, char * argv[])
{
  if (argc != 4 || (*argv[1] != '1' && *argv[1] != '2') || argv[1][1] != '\0')
  {
    std::cerr << "Invalid argument\n";
    return 1;
  }

  int n = 0;
  int m = 0;

  std::ifstream in(argv[2]);
  if (!in || !(in >> n >> m) || n < 0 || m < 0)
  {
    std::cerr << "Input error\n";
    return 2;
  }

  bool result = false;

  if (*argv[1] == '1')
  {
    if (m != 0 && n > max_length / m)
    {
      std::cerr << "Input error\n";
      return 2;
    }

    int matrix[max_length] = {};

    try
    {
      pelipenko::readMatrix(in, matrix, n, m);
      result = pelipenko::isUpperTriangular(matrix, n, m);
      pelipenko::outputMatrix(argv[3], result);
    }
    catch (const std::exception & e)
    {
      std::cerr << e.what() << '\n';
      return 2;
    }
  }
  else if (*argv[1] == '2')
  {
    int * matrix = nullptr;

    try
    {
      matrix = new int[n * m];

      pelipenko::readMatrix(in, matrix, n, m);
      result = pelipenko::isUpperTriangular(matrix, n, m);
      pelipenko::outputMatrix(argv[3], result);

      delete[] matrix;
    }
    catch (const std::bad_alloc & e)
    {
      delete[] matrix;
      std::cerr << e.what() << '\n';
      return 2;
    }
    catch (const std::exception & e)
    {
      delete[] matrix;
      std::cerr << e.what() << '\n';
      return 2;
    }
  }

  in.close();
  return 0;
}

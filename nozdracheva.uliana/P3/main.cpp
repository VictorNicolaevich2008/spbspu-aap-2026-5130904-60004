#include <iostream>
#include <fstream>
#include <stdexcept>
#include <new>
#include <cstddef>

const int max_elements = 10000;
const int arguments_count = 4;
const int first_task = 1;
const int second_task = 2;
const int output_argument = 3;
const int invalid_arguments = 1;
const int invalid_data = 2;

namespace nozdracheva
{
  int countDiagonals(const int* a, int n, int m);
  void readMatrix(std::ifstream& in, int* a, int n, int m);
}

int main(int argc, char* argv[])
{
  if (argc != arguments_count)
  {
    std::cerr << "Invalid arguments\n";
    return invalid_arguments;
  }

  int num = 0;

  if (argv[1][0] == '1' && argv[1][1] == '\0')
  {
    num = first_task;
  }
  else if (argv[1][0] == '2' && argv[1][1] == '\0')
  {
    num = second_task;
  }
  else
  {
    std::cerr << "Invalid task number\n";
    return invalid_arguments;
  }

  std::ifstream in(argv[second_task]);

  int n = 0;
  int m = 0;

  if (!(in >> n >> m) || n < 0 || m < 0)
  {
    std::cerr << "Invalid matrix size\n";
    return invalid_data;
  }

  long long total = n;
  total *= m;

  if (num == first_task && total > max_elements)
  {
    std::cerr << "Matrix is too large\n";
    return invalid_data;
  }

  int a[max_elements] = {};
  int* b = nullptr;
  int* matrix = a;

  try
  {
    if (num == second_task)
    {
      b = new int[static_cast< std::size_t >(total)];
      matrix = b;
    }

    nozdracheva::readMatrix(in, matrix, n, m);

    std::ofstream out(argv[output_argument]);

    if (!out)
    {
      throw std::invalid_argument("Cannot open output file");
    }

    const int res = nozdracheva::countDiagonals(matrix, n, m);
    out << res << "\n";

    if (!out)
    {
      throw std::invalid_argument("Cannot write output");
    }

    delete[] b;
    return 0;
  }
  catch (const std::invalid_argument& e)
  {
    delete[] b;
    std::cerr << e.what() << "\n";
    return invalid_data;
  }
  catch (const std::bad_alloc& e)
  {
    delete[] b;
    std::cerr << e.what() << "\n";
    return invalid_data;
  }
}

namespace nozdracheva
{
  void readMatrix(std::ifstream& in, int* a, int n, int m)
  {
    for (int i = 0; i < n; ++i)
    {
      for (int j = 0; j < m; ++j)
      {
        in >> a[static_cast< std::size_t >(i) * m + j];

        if (!in)
        {
          throw std::invalid_argument("Invalid matrix element");
        }
      }
    }

    in >> std::ws;

    if (!in.eof())
    {
      throw std::invalid_argument("Invalid matrix data");
    }
  }

  int countDiagonals(const int* a, int n, int m)
  {
    const int size = (n < m) ? n : m;
    int c = 0;

    for (int k = 1; k < size; ++k)
    {
      bool upper = true;
      bool lower = true;

      for (int i = 0; i < size - k; ++i)
      {
        if (a[static_cast< std::size_t >(i) * m + i + k] == 0)
        {
          upper = false;
        }

        if (a[static_cast< std::size_t >(i + k) * m + i] == 0)
        {
          lower = false;
        }
      }

      if (upper)
      {
        ++c;
      }

      if (lower)
      {
        ++c;
      }
    }

    return c;
  }
}

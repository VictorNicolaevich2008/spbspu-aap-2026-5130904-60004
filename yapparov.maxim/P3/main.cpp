#include <cstddef>
#include <exception>
#include <fstream>
#include <iostream>
#include <new>
#include <stdexcept>

namespace yapparov
{
  const size_t maxElements = 10000;
  size_t numRow(const int *data, size_t str, size_t stb);
}

int main(int argc, char **argv)
{
  int *dynamic = nullptr;
  try
  {
    if (argc < 4)
    {
      throw std::invalid_argument("Not enough arguments");
    }
    if (argc > 4)
    {
      throw std::invalid_argument("Too many arguments");
    }
    int mode = 0;
    if (argv[1][0] == '1' && argv[1][1] == '\0')
    {
      mode = 1;
    }
    else if (argv[1][0] == '2' && argv[1][1] == '\0')
    {
      mode = 2;
    }
    else
    {
      bool digits = argv[1][0] != '\0';
      for (size_t i = 0; argv[1][i] != '\0'; ++i)
      {
        if (argv[1][i] < '0' || argv[1][i] > '9')
        {
          digits = false;
        }
      }
      if (digits)
      {
        throw std::invalid_argument("First parameter is out of range");
      }
      throw std::invalid_argument("First parameter is not a number");
    }
    std::ifstream input(argv[2]);
    if (!input)
    {
      throw std::runtime_error("Cannot open input file");
    }
    long long r = 0;
    long long c = 0;
    if (!(input >> r >> c) || r < 0 || c < 0)
    {
      throw std::runtime_error("Invalid matrix dimensions");
    }
    const size_t str = r;
    const size_t stb = c;
    if (stb != 0 && str * stb / stb != str)
    {
      throw std::runtime_error("Matrix is too large");
    }
    const size_t n = str * stb;
    size_t result = 0;
    if (mode == 1)
    {
      int data[yapparov::maxElements];
      for (size_t i = 0; i < n; ++i)
      {
        if (!(input >> data[i]))
        {
          throw std::runtime_error("Invalid matrix elements");
        }
      }
      result = yapparov::numRow(data, str, stb);
    }
    else
    {
      dynamic = new int[n];
      for (size_t i = 0; i < n; ++i)
      {
        if (!(input >> dynamic[i]))
        {
          throw std::runtime_error("Invalid matrix elements");
        }
      }
      result = yapparov::numRow(dynamic, str, stb);
      delete[] dynamic;
      dynamic = nullptr;
    }
    std::ofstream output(argv[3]);
    if (!output)
    {
      throw std::runtime_error("Cannot open output file");
    }
    output << result << '\n';
  }
  catch (const std::invalid_argument &e)
  {
    delete[] dynamic;
    std::cerr << e.what() << '\n';
    return 1;
  }
  catch (const std::bad_alloc &)
  {
    delete[] dynamic;
    std::cerr << "Not enough memory\n";
    return 2;
  }
  catch (const std::exception &e)
  {
    delete[] dynamic;
    std::cerr << e.what() << '\n';
    return 2;
  }
  return 0;
}

namespace yapparov
{
  size_t numRow(const int *data, size_t str, size_t stb)
  {
    size_t best_row = 0;
    size_t best_len = 0;
    for (size_t i = 0; i < str; ++i)
    {
      size_t cur = 0;
      for (size_t j = 0; j < stb; ++j)
      {
        if (j > 0 && data[i * stb + j] == data[i * stb + j - 1])
        {
          ++cur;
        }
        else
        {
          cur = 1;
        }

        if (cur > best_len)
        {
          best_len = cur;
          best_row = i + 1;
        }
      }
    }
    return best_row;
  }
}

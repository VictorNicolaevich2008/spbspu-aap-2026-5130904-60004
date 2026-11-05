#include <cstring>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <exception>

namespace chervov
{
  const int maxSizeFixedArray = 10000;

  void readMatrix(std::istream &in, int *array, int rows, int columns)
  {
    for (int i = 0; i < rows * columns; ++i)
    {
      if (!(in >> array[i]))
      {
        throw std::logic_error("Not correct matrix file");
      }
    }
  }

  int findColumnWithLongestSeries(const int *array, int rows, int columns)
  {
    int result = 0;
    int max_count = 0;
    for (int i = 0; i < columns; ++i)
    {
      int count = 0;
      for (int j = 0; j < rows - 1; ++j)
      {
        if (array[j * columns + i] == array[(j + 1) * columns + i])
        {
          ++count;
        }
        else
        {
          count = 0;
        }
        if (count >= max_count)
        {
          max_count = count;
          result = i + 1;
        }
      }
    }
    return result;
  }
}

int main(int argc, char *argv[])
{
  int *dynamic_array = nullptr;
  try
  {
    if (argc != 4)
    {
      throw std::invalid_argument("Not correct arguments count");
    }
    if (std::strcmp(argv[1], "1") != 0 && std::strcmp(argv[1], "2") != 0)
    {
      throw std::invalid_argument("Not correct first argument");
    }

    std::ifstream input(argv[2]);
    int rows = 0;
    int columns = 0;
    if (!(input >> rows >> columns) || rows < 0 || columns < 0)
    {
      throw std::logic_error("Not correct matrix file");
    }

    int result = 0;
    if (std::strcmp(argv[1], "1") == 0)
    {
      int fixed_array[chervov::maxSizeFixedArray] = {};
      chervov::readMatrix(input, fixed_array, rows, columns);
      result = chervov::findColumnWithLongestSeries(fixed_array, rows, columns);
    }
    else
    {
      dynamic_array = new int[rows * columns]{};
      chervov::readMatrix(input, dynamic_array, rows, columns);
      result = chervov::findColumnWithLongestSeries(dynamic_array, rows, columns);
      delete[] dynamic_array;
      dynamic_array = nullptr;
    }

    std::ofstream output(argv[3]);
    if (!output)
    {
      throw std::logic_error("Not correct out file");
    }
    output << result << "\n";
  }
  catch (const std::invalid_argument &e)
  {
    std::cerr << e.what() << "\n";
    delete[] dynamic_array;
    return 1;
  }
  catch (const std::exception &e)
  {
    std::cerr << e.what() << "\n";
    delete[] dynamic_array;
    return 2;
  }
}

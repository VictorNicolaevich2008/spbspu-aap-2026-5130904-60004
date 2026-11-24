#include <iostream>
#include <fstream>
#include <stdexcept>
#include <exception>
#include <cstddef>

namespace zaytseva
{
  void readSize(const char* file_name, int& rows, int& columns);
  void readElements(const char* file_name, int rows, int columns, int* data);
  int countRowsWithNoDuplicates(const int* data, int rows, int columns);
  void writeResult(const char* file_name, int value);
}

int main(int argc, char* argv[])
{
  const int expected_argc = 4;
  const int max_stack_size = 10000;
  const char first_var = '1';
  const char second_var = '2';
  if (argc != expected_argc)
  {
    std::cerr << "Wrong number of arguments" << '\n';
    return 1;
  }
  const char num = argv[1][0];
  if ((num != first_var && num != second_var) || argv[1][1] != '\0')
  {
    std::cerr << "First argument must be 1 or 2" << '\n';
    return 1;
  }
  int rows = 0;
  int columns = 0;
  int stack[max_stack_size] = {};
  int* heap = nullptr;
  int* data = nullptr;
  try
  {
    zaytseva::readSize(argv[2], rows, columns);
    long long total = rows;
    total *= columns;
    if (num == first_var)
    {
      if (total > max_stack_size)
      {
        throw std::length_error("Matrix is too big for stack array");
      }
      data = stack;
    }
    else
    {
      heap = new int[total];
      data = heap;
    }
    zaytseva::readElements(argv[2], rows, columns, data);
    const int result = zaytseva::countRowsWithNoDuplicates(data, rows, columns);
    zaytseva::writeResult(argv[3], result);
    delete[] heap;
    return 0;
  }
  catch (const std::exception& e)
  {
    delete[] heap;
    std::cerr << e.what() << '\n';
    return 2;
  }
}

void zaytseva::readSize(const char* file_name, int& rows, int& columns)
{
  std::ifstream file(file_name);
  if (!file)
  {
    throw std::runtime_error("Cannot open input file");
  }
  if (!(file >> rows >> columns))
  {
    throw std::runtime_error("Cannot read matrix size");
  }
  if (rows < 0 || columns < 0)
  {
    throw std::length_error("Incorrect value for the number of rows/columns");
  }
}

void zaytseva::readElements(const char* file_name, int rows, int columns, int* data)
{
  std::ifstream file(file_name);
  if (!file)
  {
    throw std::runtime_error("Cannot open input file");
  }
  int header_rows = 0;
  int header_columns = 0;
  if (!(file >> header_rows >> header_columns))
  {
    throw std::runtime_error("Cannot read matrix size");
  }
  for (int i = 0; i < rows; ++i)
  {
    for (int j = 0; j < columns; ++j)
    {
      if (!(file >> data[i * columns + j]))
      {
        throw std::runtime_error("Cannot read matrix element");
      }
    }
  }
  int extra = 0;
  if (file >> extra)
  {
    throw std::runtime_error("Extra data in input file");
  }
}

int zaytseva::countRowsWithNoDuplicates(const int* data, int rows, int columns)
{
  int count = 0;
  for (int i = 0; i < rows; ++i)
  {
    bool has_equal_neighbours = false;
    for (int j = 0; j + 1 < columns; ++j)
    {
      const int left = data[i * columns + j];
      const int right = data[i * columns + j + 1];
      if (left == right)
      {
        has_equal_neighbours = true;
        break;
      }
    }
    if (!has_equal_neighbours)
    {
      ++count;
    }
  }
  return count;
}

void zaytseva::writeResult(const char* file_name, int value)
{
  std::ofstream file(file_name);
  if (!file)
  {
    throw std::runtime_error("Cannot open output file");
  }
  file << value << '\n';
}

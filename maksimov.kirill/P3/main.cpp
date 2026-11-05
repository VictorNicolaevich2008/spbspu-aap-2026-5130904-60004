#include <iostream>
#include <exception>
#include <fstream>
#include <stdexcept>

namespace maksimov
{
  void readSize(const char *file_name, int &n, int &m);
  void readElements(const char *file_name, int n, int m, int *data);
  long long findMinDiagonalSum(int n, int m, const int *data);
}

int main(int argc, char *argv[])
{
  const int expectedArgc = 4;
  const int maxStackSize = 10000;

  if (argc != expectedArgc)
  {
    std::cerr << "Wrong number of arguments" << '\n';
    return 1;
  }

  if ((argv[1][0] != '1' && argv[1][0] != '2') || argv[1][1] != '\0')
  {
    std::cerr << "Number must be 1 or 2" << '\n';
    return 1;
  }

  const char num = argv[1][0];
  int n = 0;
  int m = 0;
  int stack[maxStackSize] = {};
  int *heap = nullptr;
  int *data = nullptr;

  try
  {
    maksimov::readSize(argv[2], n, m);

    long long total = n;
    total *= m;

    if (num == '1')
    {
      if (total > maxStackSize)
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

    maksimov::readElements(argv[2], n, m, data);
    const long long result = maksimov::findMinDiagonalSum(n, m, data);

    std::ofstream file(argv[3]);
    if (!file)
    {
      throw std::runtime_error("Error open output file");
    }
    file << result << '\n';

    delete[] heap;
    return 0;
  }
  catch (const std::exception &e)
  {
    delete[] heap;
    std::cerr << e.what() << '\n';
    return 2;
  }
}

void maksimov::readSize(const char *file_name, int &n, int &m)
{
  std::ifstream file(file_name);
  if (!file)
  {
    throw std::runtime_error("Error open file");
  }

  if (!(file >> n >> m))
  {
    throw std::runtime_error("Cannot read matrix size");
  }

  if (n < 0 || m < 0)
  {
    throw std::length_error("Matrix very small");
  }
}

void maksimov::readElements(const char *file_name, int n, int m, int *data)
{
  std::ifstream file(file_name);
  if (!file)
  {
    throw std::runtime_error("Error open file");
  }

  int header_n = 0;
  int header_m = 0;
  if (!(file >> header_n >> header_m))
  {
    throw std::runtime_error("Cannot read matrix size");
  }

  for (int i = 0; i < n; ++i)
  {
    for (int j = 0; j < m; ++j)
    {
      if (!(file >> data[i * m + j]))
      {
        throw std::runtime_error("Cannot read matrix element");
      }
    }
  }
}

long long maksimov::findMinDiagonalSum(int n, int m, const int *data)
{
  const int last_diagonal = n + m - 2;
  long long min_sum = 0;
  bool is_first = true;

  for (int diagonal = 0; diagonal <= last_diagonal && n > 0 && m > 0; ++diagonal)
  {
    long long sum = 0;
    for (int i = 0; i < n; ++i)
    {
      const int j = diagonal - i;
      if (j >= 0 && j < m)
      {
        sum += data[i * m + j];
      }
    }

    if (is_first || sum < min_sum)
    {
      min_sum = sum;
      is_first = false;
    }
  }

  return min_sum;
}

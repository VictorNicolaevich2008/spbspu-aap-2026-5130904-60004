#include <fstream>
#include <iostream>

namespace ryabchikov
{
  void processMatrix(int *data, int rows, int cols)
  {
    int top = 0;
    int bottom = rows - 1;
    int left = 0;
    int right = cols - 1;
    int step = 1;

    while (top <= bottom && left <= right)
    {
      for (int i = bottom; i >= top; --i)
      {
        data[i * cols + left] -= step;
        ++step;
      }
      ++left;

      if (left <= right)
      {
        for (int j = left; j <= right; ++j)
        {
          data[top * cols + j] -= step;
          ++step;
        }
        ++top;
      }

      if (top <= bottom)
      {
        for (int i = top; i <= bottom; ++i)
        {
          data[i * cols + right] -= step;
          ++step;
        }
        --right;
      }

      if (left <= right)
      {
        for (int j = right; j >= left; --j)
        {
          data[bottom * cols + j] -= step;
          ++step;
        }
        --bottom;
      }
    }
  }

  void writeMatrix(std::ostream &out, const int *data, int rows, int cols)
  {
    out << rows << ' ' << cols;
    for (int i = 0; i < rows * cols; ++i)
    {
      out << ' ' << data[i];
    }
    out << '\n';
  }
}

int main(int argc, char *argv[])
{
  int num = 0;

  try
  {
    if (argc != 4)
    {
      throw "expected 3 arguments: num input output";
    }

    if (argv[1][0] == '1' && argv[1][1] == '\0')
    {
      num = 1;
    }
    else if (argv[1][0] == '2' && argv[1][1] == '\0')
    {
      num = 2;
    }
    else
    {
      throw "first argument must be 1 or 2";
    }
  }
  catch (const char *error)
  {
    std::cerr << "Error: " << error << '\n';
    return 1;
  }

  const int max_size = 10000;
  int fixed_array[max_size] = {};
  int *dynamic_array = nullptr;

  try
  {
    std::ifstream input(argv[2]);
    int rows = 0;
    int cols = 0;

    if (!(input >> rows >> cols) || rows < 0 || cols < 0)
    {
      throw "input is not a matrix";
    }

    const long long count = 1LL * rows * cols;
    int *data = fixed_array;

    if (num == 1 && count > max_size)
    {
      throw "matrix is too big";
    }

    if (num == 2)
    {
      dynamic_array = new int[count];
      data = dynamic_array;
    }

    for (long long i = 0; i < count; ++i)
    {
      if (!(input >> data[i]))
      {
        throw "input is not a matrix";
      }
    }

    ryabchikov::processMatrix(data, rows, cols);
    std::ofstream output(argv[3]);
    ryabchikov::writeMatrix(output, data, rows, cols);
  }
  catch (const char *error)
  {
    delete[] dynamic_array;
    std::cerr << "Error: " << error << '\n';
    return 2;
  }

  delete[] dynamic_array;
  return 0;
}

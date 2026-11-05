#include <cstddef>
#include <exception>
#include <fstream>
#include <iostream>
#include <stdexcept>

namespace kayumov
{
  constexpr std::size_t MAX_STATIC_SIZE = 10000;

  std::size_t findLongestSeriesRow(const int* matrix, std::size_t rows, std::size_t cols)
  {
    if ((rows == 0) || (cols == 0))
    {
      return 0;
    }

    std::size_t best_row = 0;
    std::size_t max_global_streak = 0;

    for (std::size_t i = 0; i < rows; ++i)
    {
      std::size_t current_streak = 1;
      std::size_t row_max_streak = 1;

      for (std::size_t j = 1; j < cols; ++j)
      {
        if (matrix[(i * cols) + j] == matrix[(i * cols) + j - 1])
        {
          ++current_streak;
        }
        else
        {
          current_streak = 1;
        }

        if (current_streak > row_max_streak)
        {
          row_max_streak = current_streak;
        }
      }

      if (row_max_streak > max_global_streak)
      {
        max_global_streak = row_max_streak;
        best_row = i + 1;
      }
    }

    return best_row;
  }
}

int main(int argc, char** argv)
{
  constexpr int REQUIRED_ARGC = 4;

  if (argc != REQUIRED_ARGC)
  {
    std::cerr << "Error: Exactly 3 arguments are required.\n";
    return 1;
  }

  if (!((argv[1][0] == '1' || argv[1][0] == '2') && (argv[1][1] == '\0')))
  {
    std::cerr << "Error: First parameter must be exactly 1 or 2.\n";
    return 1;
  }

  const int mode = argv[1][0] - '0';
  int* dynamic_matrix = nullptr;

  try
  {
    std::ifstream in(argv[2]);
    if (!in.is_open())
    {
      throw std::runtime_error("Error: Cannot open input file.");
    }

    std::size_t rows = 0;
    std::size_t cols = 0;

    if (!(in >> rows >> cols))
    {
      throw std::runtime_error("Error: Cannot read matrix dimensions.");
    }

    int* matrix = nullptr;
    int stack_matrix[kayumov::MAX_STATIC_SIZE];

    if (mode == 1)
    {
      if ((rows * cols) > kayumov::MAX_STATIC_SIZE)
      {
        throw std::runtime_error("Error: Matrix size exceeds static array limit.");
      }
      matrix = stack_matrix;
    }
    else
    {
      dynamic_matrix = new int[rows * cols];
      matrix = dynamic_matrix;
    }

    for (std::size_t i = 0; i < (rows * cols); ++i)
    {
      if (!(in >> matrix[i]))
      {
        throw std::runtime_error("Error: Not enough elements in the file.");
      }
    }

    in >> std::ws;
    if (!in.eof())
    {
      throw std::runtime_error("Error: Too many elements in the file.");
    }

    const std::size_t answer = kayumov::findLongestSeriesRow(matrix, rows, cols);

    std::ofstream out(argv[3]);
    if (!out.is_open())
    {
      throw std::runtime_error("Error: Cannot open output file.");
    }
    out << answer << '\n';

    delete[] dynamic_matrix;
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << '\n';
    delete[] dynamic_matrix;
    return 2;
  }

  return 0;
}

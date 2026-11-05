#include <iostream>
#include <fstream>
#include <cctype>
#include <limits>
#include <cstring>
#include <cstdlib>

namespace zabrodotsy
{
  bool isNumber(const char* str)
  {
    if (str == nullptr || str[0] == '\0')
    {
      return false;
    }
    size_t start = 0;
    if (str[0] == '-' || str[0] == '+')
    {
      if (str[1] == '\0')
      {
        return false;
      }
      start = 1;
    }
    for (size_t i = start; str[i] != '\0'; ++i)
    {
      if (!std::isdigit(static_cast< unsigned char >(str[i])))
      {
        return false;
      }
    }
    return true;
  }
  int processMatrix(const int* matrix, int rows, int columns)
  {
    if (rows == 0 || columns == 0)
    {
      return 0;
    }
    int valid_columns = 0;
    for (int j = 0; j < columns; ++j)
    {
      bool duplicates = false;
      for (int i = 0; i < rows - 1; ++i)
      {
        if (matrix[i * columns + j] == matrix[(i + 1) * columns + j])
        {
          duplicates = true;
          break;
        }
      }
      if (!duplicates)
      {
        valid_columns++;
      }
    }
    return valid_columns;
  }
}
int main(int argc, char* argv[])
{
  if (argc != 4)
  {
    std::cerr << "Error: Invalid number" << std::endl;
    return 1;
  }
  const char* const num_param = argv[1];
  const char* const input_param = argv[2];
  const char* const output_param = argv[3];
  if (!zabrodotsy::isNumber(num_param))
  {
    std::cerr << "Error: Not a number" << std::endl;
    return 1;
  }
  const int mode = std::atoi(num_param);
  if (mode != 1 && mode != 2)
  {
    std::cerr << "Error: Parameter is out of range" << std::endl;
    return 1;
  }
  std::ifstream in_file(input_param);
  if (!in_file.is_open())
  {
    std::cerr << "Error: Can't open input file" << std::endl;
    return 2;
  }
  const int max_element_buf = 100;
  char buf[max_element_buf];
  if (!(in_file >> buf))
  {
    std::cerr << "Error: File is empty" << std::endl;
    return 2;
  }
  if (!zabrodotsy::isNumber(buf))
  {
    std::cerr << "Error: Not a integer number" << std::endl;
    return 2;
  }
  const long long temp_rows = std::strtoll(buf, nullptr, 10);
  if (temp_rows < 0 || temp_rows > std::numeric_limits< int >::max())
  {
    std::cerr << "Error: Invalid rows dimension" << std::endl;
    return 2;
  }
  const int rows = static_cast< int >(temp_rows);
  if (!(in_file >> buf))
  {
    std::cerr << "Error: Matrix dimensions are missing" << std::endl;
    return 2;
  }
  if (!zabrodotsy::isNumber(buf))
  {
    std::cerr << "Error: Not a integer number" << std::endl;
    return 2;
  }
  const long long temp_cols = std::strtoll(buf, nullptr, 10);
  if (temp_cols < 0 || temp_cols > std::numeric_limits< int >::max())
  {
    std::cerr << "Error: Invalid columns dimension" << std::endl;
    return 2;
  }
  const int cols = static_cast< int >(temp_cols);
  if (rows > 0 && cols > std::numeric_limits< int >::max() / rows)
  {
    std::cerr << "Error: Matrix size is too large" << std::endl;
    return 2;
  }
  const int total_elements = rows * cols;
  int* matrix_ptr = nullptr;
  const int max_element = 10000;
  int static_matrix[max_element];

  if (mode == 1)
  {
    if (total_elements > max_element)
    {
      std::cerr << "Error: Exceeding the 10000 elements limit matrix" << std::endl;
      return 2;
    }
    matrix_ptr = static_matrix;
  }
  else
  {
    matrix_ptr = new int[total_elements];
  }
  for (int i = 0; i < total_elements; ++i)
  {
    if (!(in_file >> buf))
    {
      std::cerr << "Error: Matrix size and elements error" << std::endl;
      if (mode == 2)
      {
        delete[] matrix_ptr;
      }
      return 2;
    }
    if (!zabrodotsy::isNumber(buf))
    {
      std::cerr << "Error: Not a integer number" << std::endl;
      if (mode == 2)
      {
        delete[] matrix_ptr;
      }
      return 2;
    }
    char* end_ptr = nullptr;
    const long long temp = std::strtoll(buf, &end_ptr, 10);
    if (temp < std::numeric_limits< int >::min() || temp > std::numeric_limits< int >::max())
    {
      std::cerr << "Error: Integer overflow" << std::endl;
      if (mode == 2)
      {
        delete[] matrix_ptr;
      }
      return 2;
    }
    matrix_ptr[i] = static_cast< int >(temp);
  }
  if (in_file >> buf)
  {
    std::cerr << "Error: Matrix size and elements error" << std::endl;
    if (mode == 2)
    {
      delete[] matrix_ptr;
    }
    return 2;
  }
  in_file.close();
  const int result = zabrodotsy::processMatrix(matrix_ptr, rows, cols);
  if (mode == 2)
  {
    delete[] matrix_ptr;
  }
  std::ofstream out_file(output_param);
  if (!out_file.is_open())
  {
    std::cerr << "Error: Can't open output file" << std::endl;
    return 1;
  }
  out_file << result << std::endl;
  out_file.close();
  return 0;
}


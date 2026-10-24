#include <iostream>
#include <climits>
#include <stdexcept>

namespace pluzhnik
{
  int getMaxLen()
  {
    int val = 0;
    int temp_val = 0;
    int len_pos = 0;
    int max_len_pos = 0;
    while (true)
    {
      if (!(std::cin >> val))
      {
        throw std::invalid_argument("Error: invalid input format");
      }
      if (val == 0)
      {
        if (len_pos > max_len_pos)
        {
          max_len_pos = len_pos;
        }
        break;
      }
      if (val >= temp_val)
      {
        if (len_pos < (INT_MAX - 1))
        {
          ++len_pos;
        }
        else
        {
          throw std::invalid_argument("Error: overflow len_pos");
        }
      }
      else if (len_pos > max_len_pos)
      {
        max_len_pos = len_pos;
        len_pos = 1;
      }
      else
      {
        len_pos = 1;
      }
      temp_val = val;
    }
    return max_len_pos;
  }
}

int main()
{
  try
  {
    const int max_len_pos = pluzhnik::getMaxLen();
    std::cout << max_len_pos << "\n";
    return 0;
  }
  catch (const std::invalid_argument &e)
  {
    std::cerr << e.what() << "\n";
    return 1;
  }
}

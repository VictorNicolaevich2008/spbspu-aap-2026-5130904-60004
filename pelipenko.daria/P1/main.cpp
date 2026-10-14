#include <exception>
#include <iostream>
#include <stdexcept>

namespace pelipenko
{
  int findMaxEqualRun()
  {
    long long prev = 0;
    long long curr = 0;
    int length = 0;
    int max_length = 0;

    if (!(std::cin >> prev))
    {
      throw std::invalid_argument("Input is not a sequence of integers");
    }

    while (true)
    {
      if (prev == 0)
      {
        break;
      }

      if (length == 0)
      {
        length = 1;
        max_length = 1;
      }

      if (!(std::cin >> curr))
      {
        throw std::invalid_argument("Input is not a sequence of integers");
      }

      if (curr == 0)
      {
        break;
      }

      if (curr == prev)
      {
        ++length;
      }
      else
      {
        length = 1;
        prev = curr;
      }

      if (length > max_length)
      {
        max_length = length;
      }
    }

    return max_length;
  }
}

int main()
{
  try
  {
    const int answer = pelipenko::findMaxEqualRun();
    std::cout << answer << "\n";
    return 0;
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << "\n";
    return 1;
  }
}

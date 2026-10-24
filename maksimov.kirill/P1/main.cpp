#include <iostream>
#include <stdexcept>

namespace maksimov
{
  int countSumRec()
  {
    const int min_length = 3;
    long long pre1 = 0;
    long long pre2 = 0;
    int sum = 0;
    int matches = 0;

    while (true)
    {
      int num = 0;

      if (!(std::cin >> num))
      {
        throw std::invalid_argument("Error: invalid input format");
      }

      if (num == 0)
      {
        break;
      }

      ++sum;

      if (sum >= min_length && num == pre1 + pre2)
      {
        ++matches;
      }

      pre2 = pre1;
      pre1 = num;
    }

    if (sum < min_length)
    {
      throw std::length_error("Error: sequence too short");
    }

    return matches;
  }
}

int main()
{
  try
  {
    const int result = maksimov::countSumRec();

    std::cout << result << "\n";

    return 0;
  }
  catch (const std::invalid_argument& e)
  {
    std::cerr << e.what() << "\n";

    return 1;
  }
  catch (const std::length_error& e)
  {
    std::cerr << e.what() << "\n";

    return 2;
  }
}

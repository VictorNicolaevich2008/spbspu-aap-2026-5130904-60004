#include <iostream>
#include <stdexcept>
#include <climits>

namespace nozdracheva
{
  int findSubMax();
}

int main()
{
  try
  {
    const int res = nozdracheva::findSubMax();
    std::cout << res << "\n";
    return 0;
  }
  catch (const std::invalid_argument& e)
  {
    std::cerr << e.what() << "\n";
    return 1;
  }
  catch (const std::overflow_error& e)
  {
    std::cerr << e.what() << "\n";
    return 2;
  }
}

namespace nozdracheva
{
  int findSubMax()
  {
    int n = 0;
    int max1 = INT_MIN;
    int max2 = INT_MIN;
    int c = 0;

    while (std::cin >> n)
    {
      if (n == 0)
      {
        break;
      }

      if (c == INT_MAX)
      {
        throw std::overflow_error("Sequence is too long");
      }

      ++c;

      if (n >= max1)
      {
        max2 = max1;
        max1 = n;
      }
      else if (n > max2)
      {
        max2 = n;
      }
    }

    if (!std::cin && !std::cin.eof())
    {
      throw std::invalid_argument("Not a number entered");
    }

    if (c < 2)
    {
      throw std::overflow_error("Sequence is too short");
    }

    return max2;
  }
}

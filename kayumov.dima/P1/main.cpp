#include <iostream>
#include <stdexcept>

namespace kayumov
{
  int maxChislo();
}

int main()
{
  try
  {
    const int result = kayumov::maxChislo();

    std::cout << result << "\n";

    return 0;
  }
  catch (const std::invalid_argument& e)
  {
    std::cerr << e.what() << "\n";

    return 1;
  }
  catch (const std::runtime_error& a)
  {
    std::cerr << a.what() << "\n";

    return 2;
  }
}

namespace kayumov
{
  int maxChislo()
  {
    int longer = 0;
    int cnt = 0;
    int max = 0;
    int k = 0;
    while (true)
    {
      if (!(std::cin >> k))
      {
        throw std::invalid_argument("Error: invald input count");
      }
      if (k == 0)
      {
        break;
      }

      ++longer;
      if (max < k)
      {
        max = k;
        cnt = 0;
      }
      else
      {
        cnt++;
      }
    }

    if (longer == 0)
    {
      throw std::runtime_error("Error: sequence too short");
    }

    return cnt;
  }
}

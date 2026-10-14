#include <exception>
#include <iostream>
#include <stdexcept>

namespace yapparov
{
  int func();
}

int main()
{
  try
  {
    const int result = yapparov::func();
    std::cout << result << "\n";
    return 0;
  }
  catch (const std::exception &e)
  {
    std::cerr << e.what() << '\n';
    return 1;
  }
}

namespace yapparov
{
  int func()
  {
    int x = 0;
    int min = 0;
    int count = 0;

    while (std::cin >> x)
    {
      if (x == 0)
      {
        return count;
      }
      if (count == 0 || x < min)
      {
        min = x;
        count = 1;
      }
      else if (x == min)
      {
        ++count;
      }
    }
    throw std::invalid_argument("invalid x");
  }
}

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
  catch (const std::invalid_argument & e)
  {
    std::cerr << e.what() << "\n";
    return 1;
  }
  catch (const std::runtime_error & a)
  {
    std::cerr << a.what() << "\n";
    return 2;
  }
}

namespace kayumov
{
  int maxChislo()
  {
    int number = 0;
    if (!(std::cin >> number))
    {
      throw std::invalid_argument("Invalid input");
    }
    int max_val = number;
    while (std::cin >> number)
    {
      if (number > max_val)
      {
        max_val = number;
      }
    }
    if (!std::cin.eof())
    {
      throw std::runtime_error("Read error");
    }
    return max_val;
  }
}

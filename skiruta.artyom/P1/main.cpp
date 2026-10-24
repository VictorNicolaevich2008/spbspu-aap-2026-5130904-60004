#include <iostream>
#include <stdexcept>

namespace skiruta
{
  int countDelimie()
  {
    int count = 0;
    int prev = 0;
    int n = 0;
    int nums = 0;
    while (true)
    {
      if (!(std::cin >> n))
      {
        throw std::invalid_argument("Error: input must be integer");
      }
      if (n == 0)
      {
        if (nums < 2)
        {
          throw std::runtime_error("Error: Not enough numbers");
        }
        return count;
      }
      if (prev && n % prev == 0)
      {
        count++;
      }
      prev = n;
      nums++;
    }
  }
}

int main()
{
  try
  {
    std::cout << skiruta::countDelimie() << std::endl;
    return 0;
  }
  catch (const std::invalid_argument& e)
  {
    std::cerr << e.what() << std::endl;
    return 1;
  }
  catch (const std::runtime_error& e)
  {
    std::cerr << e.what() << std::endl;
    return 2;
  }
}

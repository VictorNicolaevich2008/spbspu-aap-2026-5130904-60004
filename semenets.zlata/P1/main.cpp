#include <iostream>
#include <stdexcept>
#include <climits>

namespace semenets
{
  int countSignChanges();
}

int main()
{
  try
  {
    const int result = semenets::countSignChanges();
    std::cout << result << "\n";
    return 0;
  }
  catch (const std::invalid_argument& e)
  {
    std::cerr << e.what() << "\n";
    return 1;
  }
}

namespace semenets
{
  int countSignChanges()
  {
    int num = 0;
    int count = 0;
    int count_num = 0;
    int znak_past = 0;
    int znak_new = 0;
    while (true)
    {
      std::cin >> num;
      if (std::cin.fail())
      {
        throw std::invalid_argument("Not a number enter");
      }
      if (num == 0)
      {
        break;
      }
      ++count_num;
      if (num > 0)
      {
        znak_new = 1;
      }
      else
      {
        znak_new = -1;
      }
      if (count_num != 1 && znak_new != znak_past)
      {
        ++count;
      }
      znak_past = znak_new;
    }
    return count;
  }
}

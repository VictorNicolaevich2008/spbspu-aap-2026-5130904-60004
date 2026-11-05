#include <cstdlib>
#include <exception>
#include <iostream>
#include <stdexcept>
namespace fomin
{
  int func();
}
int main()
{
  try
  {
    const int max_len_over_zero = fomin::func();
    std::cout << max_len_over_zero << "\n";
  }
  catch (const std::exception &e)
  {
    std::cerr << e.what() << "\n";
    return 1;
  }
}
namespace fomin
{
  int func()
  {
    long int num = 0;
    int len = 0;
    int max_len = 0;
    while (std::cin >> num)
    {
      if (std::cin.peek() == '.' || std::cin.peek() == ',')
      {
        throw std::runtime_error("Not an integer");
      }
      if (num == 0)
      {
        if (max_len < len)
        {
          max_len = len;
        }
        return max_len;
      }
      if (num % 2 == 0)
      {
        len++;
      }
      else
      {
        if (max_len < len)
        {
          max_len = len;
        }
        len = 0;
      }
    }
    throw std::runtime_error("Writed not a int");
  }
}

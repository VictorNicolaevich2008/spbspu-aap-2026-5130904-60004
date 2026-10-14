#include <iostream>
#include <stdexcept>
#include <exception>

namespace ganev
{
  int maxLenght();
}
int main()
{
  try
  {
    std::cout << ganev::maxLenght();
    return 0;
  }
  catch (const std::exception& e)
  {
    std::cout << e.what();
    return 1;
  }
}

namespace ganev
{
  int maxLenght()
  {
    int n = 0, result = 0, lenght = 0;
    if (!(std::cin >> n))
    {
      throw std::invalid_argument("Input error");
    }
    int tmp = n;
    while (n != 0)
    {
      if (n <= tmp)
      {
        lenght++;
      }
      else
      {
        result = lenght > result ? lenght : result;
        lenght = 1;
      }
      tmp = n;
      if (!(std::cin >> n))
      {
        throw std::invalid_argument("Input error");
      }
    }
    result = lenght > result ? lenght : result;
    return result;
  }
}

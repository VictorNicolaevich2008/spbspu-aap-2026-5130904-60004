#include <iostream>
#include <stdexcept>

namespace zaytseva
{
  int countLessGreater();
}

int main()
{
  std::cout << "Please, enter the sequence of numbers:\n";
  try
  {
    const int result = zaytseva::countLessGreater();
    std::cout << "Count of suitable elements:" << result << "\n";
    return 0;
  }
  catch (const std::invalid_argument& e)
  {
    std::cerr << e.what() << "\n";
    return 1;
  }
}

namespace zaytseva
{
  int countLessGreater()
  {
    const int min_length = 3;
    int prev_num = 0;
    int curr_num = 0;
    int len = 0;
    int count = 0;
    while (true)
    {
      int next_num = 0;
      if (!(std::cin >> next_num))
      {
        throw std::invalid_argument("Invalid input format.\n");
      }
      if (next_num == 0)
      {
        break;
      }
      ++len;
      if ((len >= min_length) && (curr_num < prev_num) && (curr_num > next_num))
      {
        ++count;
      }
      prev_num = curr_num;
      curr_num = next_num;
    }
    return count;
  }
}

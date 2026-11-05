#include <iostream>
#include <stdexcept>

namespace ermolaeva
{
  int locMaxNum();
}
int main()
{
  try
  {
    const int result = ermolaeva::locMaxNum();
    std::cout << result << "\n";
  }
  catch (const std::invalid_argument &e)
  {
    std::cerr << e.what() << "\n";
    return 1;
  }
  catch (const std::logic_error &e)
  {
    std::cerr << e.what() << "\n";
    return 2;
  }
  return 0;
}

int ermolaeva::locMaxNum()
{
  int first = 0;
  int second = 0;
  int third = 0;
  int input_count = 0;
  int loc_max_count = 0;
  while (std::cin >> third && third != 0)
  {
    input_count++;
    if (input_count >= 3 && second > third && second > first)
    {
      loc_max_count++;
    }
    first = second;
    second = third;
  }
  if (std::cin.fail())
  {
    throw std::invalid_argument("Только целые числа!!!");
  }
  if (input_count == 0)
  {
    throw std::logic_error("где последовательсность?");
  }
  return loc_max_count;
}


#include <iostream>
#include <stdexcept>

namespace chervov
{
  void countSumOfPrevTwo()
  {
    const int MinSequenceLength = 3;
    int first_number = 0, second_number = 0, current_number = 0;
    int length_sequence = 0;

    int count = 0;

    while (std::cin >> current_number)
    {
      if (current_number == 0)
      {
        if (length_sequence < MinSequenceLength)
        {
          throw std::runtime_error("Lenght sequence short");
        }
        else
        {
          std::cout << count << "\n";
          return;
        }
      }

      length_sequence++;

      if (length_sequence > 2)
      {
        if (first_number + second_number == current_number)
        {
          count++;
        }
      }

      first_number = second_number;
      second_number = current_number;
    }

    throw std::invalid_argument("Invalid sequence number");
  }
}

int main()
{
  try
  {
    chervov::countSumOfPrevTwo();
    return 0;
  }
  catch (const std::invalid_argument &e)
  {
    std::cerr << e.what() << "\n";
    return 1;
  }
  catch (const std::runtime_error &e)
  {
    std::cerr << e.what() << "\n";
    return 2;
  }
}

#include <iostream>
#include <stdexcept>
#include <clocale>
namespace romanov
{
  int localMaxNumber();
}
int main()
{
  std::setlocale(LC_ALL, "Russian");
  std::cout << "Введите последовательность чисел, 0 - конец ввода\n";
  try
  {
    const int res = romanov::localMaxNumber();
    std::cout << res << "\n";
  }
  catch (std::invalid_argument &e)
  {
    std::cout << e.what();
    return 1;
  }
  catch (std::logic_error &e)
  {
    std::cout << e.what();
    return 2;
  }
  return 0;
}
int romanov::localMaxNumber()
{
  int third = 0, second = 0, first = 0;
  int input_count = 0, local_max_count = 0;
  while (std::cin >> third && third != 0)
  {
    input_count++;
    if (input_count >= 3 && second > third && second > first)
    {
      local_max_count++;
    }
    first = second;
    second = third;
  }
  if (std::cin.fail())
  {
    throw std::invalid_argument("Программа принимает только целые числа\n");
  }
  if (input_count == 0)
  {
    throw std::logic_error("Слишком мало значений\n");
  }
  return local_max_count;
}


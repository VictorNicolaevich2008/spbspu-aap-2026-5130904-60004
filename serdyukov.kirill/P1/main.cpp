#include <iostream>
#include <stdexcept>

namespace serdyukov {
  int getGreatLess();
}

int main()
{
  try {
    const int great_less = serdyukov::getGreatLess();
    std::cout << great_less << '\n';
    return 0;
  } catch (const std::invalid_argument& e) {
    std::cerr << e.what() << '\n';
    return 1;
  }
}

int serdyukov::getGreatLess()
{
  int next = 0;
  int current = 0;
  int previous = 0;
  int result = 0;

  if (!(std::cin >> next)) {
    throw std::invalid_argument("Incorrect input");
  }

  while (next != 0) {
    previous = current;
    current = next;

    if (!(std::cin >> next)) {
      throw std::invalid_argument("Incorrect input");
    }

    if (previous != 0 && next != 0 && current < previous && current > next) {
      result++;
    }
  }

  return result;
}


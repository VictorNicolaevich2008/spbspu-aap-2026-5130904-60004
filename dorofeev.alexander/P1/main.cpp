#include <exception>
#include <iostream>
#include <stdexcept>

namespace dorofeev {
  int maxMonoInt()
  {
    int x = 0;
    int prev = 0;
    int cur = 0;
    int best = 0;
    bool first = true;

    while (std::cin >> x) {
      if (x == 0) {
        return best;
      }
      if (!first && x >= prev) {
        cur++;
      } else {
        cur = 1;
      }
      if (cur > best) {
        best = cur;
      }
      prev = x;
      first = false;
    }
    throw std::invalid_argument("input is not a valid sequence");
  }
}

int main()
{
  try {
    const int result = dorofeev::maxMonoInt();
    std::cout << result << "\n";
  } catch (const std::exception & e) {
    std::cerr << "Error" << e.what() << "\n";
    return 1;
  }
  return 0;
}

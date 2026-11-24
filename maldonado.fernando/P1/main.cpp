#include <iostream>
#include <cstdlib>

namespace maldonado {
  void processSequence()
  {
    int current_val = 0;
    int min_val = 0;
    int min_count = 0;
    bool is_first = true;

    while (true) {
      std::cin >> current_val;

      if (std::cin.fail()) {
        std::exit(1);
      }

      if (current_val == 0) {
        break;
      }

      if (is_first) {
        min_val = current_val;
        min_count = 1;
        is_first = false;
      } else {
        if (current_val < min_val) {
          min_val = current_val;
          min_count = 1;
        } else if (current_val == min_val) {
          min_count++;
        }
      }
    }

    std::cout << min_count << "\n";
  }
}

int main()
{
  maldonado::processSequence();
  return 0;
}

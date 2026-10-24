#include <iostream>

namespace ryabchikov {
  bool isLocalMin(int a, int b, int c)
  {
    return b < a && b < c;
  }
}

int main()
{
  int a = 0;
  int b = 0;
  int x = 0;
  int count = 0;
  int local_mins = 0;
  try {
    while (std::cin >> x && x != 0) {
      if (count >= 2 && ryabchikov::isLocalMin(a, b, x)) {
        ++local_mins;
      }
      a = b;
      b = x;
      ++count;
    }
    if (std::cin.fail()) {
      throw "input is not a sequence";
    }
  } catch (const char *error) {
    std::cerr << "Error: " << error << "\n";
    return 1;
  }
  if (count == 0) {
    std::cerr << "Error: sequence is empty\n";
    return 2;
  }
  std::cout << local_mins << "\n";
  return 0;
}

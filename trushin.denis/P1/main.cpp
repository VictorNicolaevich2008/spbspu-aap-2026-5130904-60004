#include <exception>
#include <iostream>
#include <stdexcept>

namespace trushin {
  int inNum()
  {
    int num = 0;
    std::cin >> num;
    if (std::cin.fail()) {
      throw std::logic_error("bad input");
    }
    return num;
  }

  int isPif(int a, int b, int c)
  {
    if (a <= 0 || b <= 0 || c <= 0) {
      return 0;
    }
    const long long x = a;
    const long long y = b;
    const long long z = c;
    if (z * z == x * x + y * y) {
      return 1;
    }
    return 0;
  }
}

int main()
{
  int a = 0;
  int b = 0;
  int c = 0;
  int kol = 0;
  int sum = 0;
  try {
    c = trushin::inNum();
    while (c != 0) {
      if (kol == 2) {
        sum = sum + trushin::isPif(a, b, c);
      } else {
        kol = kol + 1;
      }
      a = b;
      b = c;
      c = trushin::inNum();
    }
  } catch (const std::exception &e) {
    std::cerr << e.what() << '\n';
    return 1;
  }
  std::cout << sum << '\n';
}

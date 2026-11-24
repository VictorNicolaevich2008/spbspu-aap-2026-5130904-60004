#include <iostream>
#include <cstring>
#include <cctype>
#include <climits>
#include <new>

namespace ibragimov {
  void uppLow(const char *arr, char *res);
}

int main()
{
  char *arr = nullptr;
  char *result = nullptr;

  try {
    int size = 1;
    int len = 0;

    arr = new char[size];
    char c = '\0';

    while (std::cin.get(c) && c != '\n') {
      if (len >= size - 1) {
        if (size > INT_MAX / 2) {
          throw std::invalid_argument("String is too large");
        }
        size *= 2;
        char *const new_arr = new char[size];
        for (int i = 0; i < len; ++i) {
          new_arr[i] = arr[i];
        }
        delete[] arr;
        arr = new_arr;
      }

      arr[len] = c;
      len++;
    }

    if (len == 0) {
      throw std::invalid_argument("Input is empty");
    }
    arr[len] = '\0';

    result = new char[len + 1];

    ibragimov::uppLow(arr, result);

    std::cout << result << '\n';

    delete[] result;
    delete[] arr;

    return 0;
  } catch (const std::bad_alloc &e) {
    std::cerr << "чтото с памятью не так: " << e.what() << std::endl;
    delete[] arr;
    delete[] result;

    return 1;
  } catch (const std::invalid_argument &e) {
    std::cerr << e.what() << std::endl;
    delete[] arr;
    delete[] result;

    return 1;
  }
}

namespace ibragimov {
  void uppLow(const char *arr, char *res)
  {
    for (int i = 0; arr[i] != '\0'; ++i) {
      if (arr[i] >= 'A' && arr[i] <= 'Z') {
        res[i] = std::tolower(arr[i]);
      } else {
        res[i] = arr[i];
      }
    }
    res[std::strlen(arr)] = '\0';
  }
}

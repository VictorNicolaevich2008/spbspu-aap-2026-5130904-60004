#include <iostream>
#include <new>
#include <cstddef>

namespace serdyukov {
  void compressString(const char* input, char* output);
  constexpr int total_values = 256;
}

int main()
{
  char* str = nullptr;
  size_t size = 1;
  char ch = '0';
  try {
    while (true) {
      if (!(std::cin.get(ch))) {
        std::cerr << "Can't handle input data\n";
        return 1;
      }
      if (ch == '\n') {
        if (str == nullptr) {
          std::cerr << "Empty line\n";
          return 1;
        }
        break;
      }

      char* const temp = new char[size + 1];

      for (size_t i = 0; i < size - 1; ++i) {
        temp[i] = str[i];
      }

      temp[size - 1] = ch;
      temp[size] = '\0';

      delete[] str;
      str = temp;
      ++size;
    }
    char* result = new char[size + 1];
    serdyukov::compressString(str, result);
    if (result[0] == '\0') {
      std::cout << "No repeated chars\n";
    } else {
      std::cout << result << '\n';
    }

    delete[] result;
    delete[] str;
    result = nullptr;
    str = nullptr;
    return 0;
  } catch (const std::bad_alloc&) {
    std::cerr << "Can't handle memory\n";
    return 1;
  }
}

void serdyukov::compressString(const char* input, char* output)
{
  int frequency[serdyukov::total_values] = {0};
  size_t i = 0;
  while (input[i] != '\0') {
    const unsigned char ch = static_cast< unsigned char >(input[i]);
    frequency[ch]++;
    ++i;
  }
  i = 0;
  int j = 0;
  while (input[i] != '\0') {
    const unsigned char ch = static_cast< unsigned char >(input[i]);
    if (frequency[ch] > 1) {
      frequency[ch] = 1;
      output[j] = input[i];
      j++;
    }
    i++;
  }
  output[j] = '\0';
}


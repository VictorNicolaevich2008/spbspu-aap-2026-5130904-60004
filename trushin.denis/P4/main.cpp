#include <cstddef>
#include <iostream>
#include <new>
namespace trushin {
  char *readStr(std::istream &in, size_t &length);
  int proverka(const char *str) noexcept;
}
int main()
{
  size_t length = 0;
  try {
    char *const line = trushin::readStr(std::cin, length);
    if (length == 0 && std::cin.eof()) {
      std::cerr << "no input" << '\n';
      delete[] line;
      return 1;
    }
    if (trushin::proverka(line) == 1) {
      std::cout << 1 << '\n';
      delete[] line;
      return 0;
    } else {
      std::cout << 0 << '\n';
      delete[] line;
      return 0;
    }
  } catch (const std::bad_alloc &) {
    std::cerr << "bad_alloc" << '\n';
    return 1;
  }
}
char *trushin::readStr(std::istream &in, size_t &length)
{
  length = 0;
  const size_t v1 = 10;
  size_t v = v1;
  char c = 0;
  char *str = new char[v]{};
  while (in.get(c) && c != '\n') {
    if (length + 1 == v) {
      try {
        char *const str1 = new char[v * 2]{};
        for (size_t i = 0; i < length; ++i) {
          str1[i] = str[i];
        }
        delete[] str;
        str = str1;
        v = v * 2;
      } catch (const std::bad_alloc &) {
        delete[] str;
        throw;
      }
    }
    str[length] = c;
    ++length;
  }
  str[length] = '\0';
  return str;
}
int trushin::proverka(const char *str) noexcept
{
  for (size_t i = 0; str[i] != '\0'; ++i) {
    if (str[i] == str[i + 1]) {
      return 1;
    }
  }
  return 0;
}

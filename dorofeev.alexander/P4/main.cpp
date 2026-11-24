#include <cstring>
#include <iostream>
#include <new>

namespace dorofeev {
  const size_t startCapacity = 100;

  char * readLine(std::istream & in)
  {
    size_t capacity = startCapacity;
    size_t size = 0;
    char * buf = new (std::nothrow) char[capacity];
    if (buf == nullptr) {
      return nullptr;
    }
    char c = 0;
    while (in.get(c) && c != '\n') {
      if (size + 1 >= capacity) {
        char * const bigger = new (std::nothrow) char[capacity * 2];
        if (bigger == nullptr) {
          delete[] buf;
          return nullptr;
        }
        for (size_t i = 0; i < size; ++i) {
          bigger[i] = buf[i];
        }
        delete[] buf;
        buf = bigger;
        capacity *= 2;
      }
      buf[size] = c;
      ++size;
    }
    buf[size] = '\0';
    return buf;
  }

  char * repSym(char * dest, const char * src)
  {
    size_t size = 0;
    dest[0] = '\0';
    for (size_t i = 0; src[i] != '\0'; ++i) {
      if (std::strchr(src + i + 1, src[i]) != nullptr && std::strchr(dest, src[i]) == nullptr) {
        dest[size] = src[i];
        ++size;
        dest[size] = '\0';
      }
    }
    return dest;
  }
}

int main()
{
  char * const s = dorofeev::readLine(std::cin);
  if (s == nullptr) {
    std::cerr << "Error: not enough memory\n";
    return 1;
  }

  const size_t len = std::strlen(s);
  if (len == 0 && std::cin.eof()) {
    std::cerr << "Error: empty input\n";
    delete[] s;
    return 1;
  }

  char * const result = new (std::nothrow) char[len + 1];
  if (result == nullptr) {
    std::cerr << "Error: not enough memory\n";
    delete[] s;
    return 1;
  }

  dorofeev::repSym(result, s);
  std::cout << result << "\n";

  delete[] result;
  delete[] s;
  return 0;
}

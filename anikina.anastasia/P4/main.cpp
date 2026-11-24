#include <cctype>
#include <iostream>
#include <new>

namespace anikina
{
  int length(const char * str) noexcept
  {
    int n = 0;
    while (str[n] != '\0')
    {
      ++n;
    }
    return n;
  }

  char * removeLatin(char * dest, const char * src) noexcept
  {
    int j = 0;
    for (int i = 0; src[i] != '\0'; ++i)
    {
      const unsigned char c = static_cast< unsigned char >(src[i]);
      if (!std::isalpha(c))
      {
        dest[j] = src[i];
        ++j;
      }
    }
    dest[j] = '\0';
    return dest;
  }

  char * readLine()
  {
    int capacity = 10;
    int size = 0;
    char * str = new (std::nothrow) char[capacity];
    if (str == nullptr)
    {
      return nullptr;
    }

    std::cin >> std::noskipws;
    char c = 0;
    while (std::cin >> c && c != '\n')
    {
      if (size + 1 == capacity)
      {
        const int new_capacity = capacity * 2;
        char * const bigger = new (std::nothrow) char[new_capacity];
        if (bigger == nullptr)
        {
          delete[] str;
          return nullptr;
        }
        for (int i = 0; i < size; ++i)
        {
          bigger[i] = str[i];
        }
        delete[] str;
        str = bigger;
        capacity = new_capacity;
      }
      str[size] = c;
      ++size;
    }
    if (!std::cin && size == 0)
    {
      delete[] str;
      return nullptr;
    }
    str[size] = '\0';
    return str;
  }
}

int main()
{
  char * const input = anikina::readLine();
  if (input == nullptr)
  {
    std::cerr << "Error: cannot read the input string\n";
    return 1;
  }

  char * const result = new (std::nothrow) char[anikina::length(input) + 1];
  if (result == nullptr)
  {
    delete[] input;
    std::cerr << "Error: not enough memory\n";
    return 1;
  }

  anikina::removeLatin(result, input);
  std::cout << result << '\n';

  delete[] result;
  delete[] input;
  return 0;
}

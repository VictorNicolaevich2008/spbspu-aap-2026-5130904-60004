#include <iostream>
#include <new>
#include <cstddef>
#include <cctype>

const int invalid_data = 1;
const std::size_t initial_size = 16;
const std::size_t growth_factor = 2;

namespace nozdracheva
{
  char* removeVowels(const char* str, char* res);
}

int main()
{
  std::size_t size = initial_size;
  std::size_t n = 0;

  char* str = new (std::nothrow) char[size];

  if (!str)
  {
    std::cerr << "Memory allocation error\n";
    return invalid_data;
  }

  char c = 0;

  while (std::cin.get(c) && c != '\n')
  {
    if (n == size - 1)
    {
      if (size > static_cast< std::size_t >(-1) / growth_factor)
      {
        delete[] str;
        std::cerr << "Memory allocation error\n";
        return invalid_data;
      }

      size *= growth_factor;
      char* const temp = new (std::nothrow) char[size];

      if (!temp)
      {
        delete[] str;
        std::cerr << "Memory allocation error\n";
        return invalid_data;
      }

      for (std::size_t i = 0; i < n; ++i)
      {
        temp[i] = str[i];
      }

      delete[] str;
      str = temp;
    }

    str[n] = c;
    ++n;
  }

  if (std::cin.bad())
  {
    delete[] str;
    std::cerr << "Input error\n";
    return invalid_data;
  }

  str[n] = '\0';
  if (n == 0)
  {
    delete[] str;
    std::cerr << "Empty input\n";
    return invalid_data;
  }

  char* const res = new (std::nothrow) char[n + 1];

  if (!res)
  {
    delete[] str;
    std::cerr << "Memory allocation error\n";
    return invalid_data;
  }

  nozdracheva::removeVowels(str, res);

  std::cout << res << "\n";

  delete[] str;
  delete[] res;

  return 0;
}

namespace nozdracheva
{
  char* removeVowels(const char* str, char* res)
  {
    std::size_t j = 0;

    for (std::size_t i = 0; str[i] != '\0'; ++i)
    {
      const char c = static_cast< char >(std::tolower(static_cast< unsigned char >(str[i])));

      if (c != 'a' && c != 'e' && c != 'i' && c != 'o' && c != 'u')
      {
        res[j] = str[i];
        ++j;
      }
    }

    res[j] = '\0';
    return res;
  }
}

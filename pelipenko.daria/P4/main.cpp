#include <cstddef>
#include <iostream>
#include <new>

namespace pelipenko
{
  char* getStr(std::istream& in);
  char* getCommon(const char* str1, const char* str2);
  std::size_t getLen(const char* str);
}

int main()
{
  char* str1 = nullptr;
  char* res = nullptr;
  const char* const str2 = "def_ghk";

  try
  {
    str1 = pelipenko::getStr(std::cin);

    if (pelipenko::getLen(str1) == 0)
    {
      std::cerr << "Error: Empty input\n";
      delete[] str1;
      return 1;
    }

    res = pelipenko::getCommon(str1, str2);
    std::cout << res << '\n';

    delete[] str1;
    delete[] res;
    return 0;
  }
  catch (const std::bad_alloc&)
  {
    std::cerr << "Memory error\n";
    delete[] str1;
    return 1;
  }
}

namespace pelipenko
{
  std::size_t getLen(const char* str)
  {
    std::size_t len = 0;
    while (str[len] != '\0')
    {
      ++len;
    }
    return len;
  }

  char* getStr(std::istream& in)
  {
    const std::size_t start_size = 16;
    std::size_t cap = start_size;
    std::size_t len = 0;
    char* buf = new char[cap];
    char ch = 0;

    while (in.get(ch) && ch != '\n')
    {
      if (len + 1 >= cap)
      {
        cap *= 2;
        char* const new_buf = new char[cap];

        for (std::size_t k = 0; k < len; ++k)
        {
          new_buf[k] = buf[k];
        }

        delete[] buf;
        buf = new_buf;
      }
      buf[len] = ch;
      ++len;
    }

    buf[len] = '\0';
    return buf;
  }

  char* getCommon(const char* str1, const char* str2)
  {
    const std::size_t len2 = getLen(str2);
    std::size_t pos = 0;

    char* const out = new char[len2 + 1];

    for (std::size_t i = 0; str2[i] != '\0'; ++i)
    {
      bool found = false;

      for (std::size_t j = 0; str1[j] != '\0'; ++j)
      {
        if (str2[i] == str1[j])
        {
          found = true;
          break;
        }
      }

      if (found)
      {
        bool already_added = false;
        for (std::size_t k = 0; k < pos; ++k)
        {
          if (out[k] == str2[i])
          {
            already_added = true;
            break;
          }
        }

        if (!already_added)
        {
          out[pos] = str2[i];
          ++pos;
        }
      }
    }

    out[pos] = '\0';
    return out;
  }
}

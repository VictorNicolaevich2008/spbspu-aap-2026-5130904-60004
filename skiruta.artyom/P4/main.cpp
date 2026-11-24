#include <iostream>
#include <cstring>
#include <cctype>
#include <new>

namespace skiruta
{
  char *readLine(size_t &size)
  {
    char *res = nullptr;
    char *buf = static_cast< char * >(malloc(1));
    if (!buf)
    {
      throw std::bad_alloc();
    }
    char c = 0;
    while (std::cin.get(c) && c != '\n' && buf)
    {
      *(buf + size) = c;
      size++;
      char *const tmp = static_cast< char * >(realloc(buf, size + 1));
      if (!tmp)
      {
        free(buf);
        throw std::bad_alloc();
      }
      buf = tmp;
    }
    buf[size] = '\0';
    res = static_cast< char * >(malloc(size + 1));
    if (!res)
    {
      free(buf);
      throw std::bad_alloc();
    }
    strcpy(res, buf);
    free(buf);
    return res;
  }

  size_t countDifLat(const char *t, const size_t s)
  {
    size_t count = 0;
    char *const seen = new char[s + 1]();
    for (size_t i = 0; i < s; i++)
    {
      *(seen + i) = ' ';
      if (!(strchr(seen, *(t + i))) && std::isalpha(static_cast< unsigned char >(*(t + i))))
      {
        seen[count++] = *(t + i);
      }
    }
    delete[] seen;
    return count;
  }
}

int main()
{
  try
  {
    char *t = nullptr;
    size_t s = 0;
    t = skiruta::readLine(s);
    if (s == 0)
    {
      std::cerr << "Empty line" << std::endl;
      free(t);
      return 1;
    }
    std::cout << skiruta::countDifLat(t, s) << std::endl;
    free(t);
  }
  catch (const std::bad_alloc &)
  {
    std::cerr << "Memory error" << std::endl;
    return 1;
  }
  return 0;
}

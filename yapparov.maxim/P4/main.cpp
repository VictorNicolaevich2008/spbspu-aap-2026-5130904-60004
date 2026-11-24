#include <cstddef>
#include <cstring>
#include <iostream>
#include <new>

namespace yapparov
{
  char *readLine(std::istream &in);
  char *twoRows(char *newstr, const char *str1, const char *str2);
}

int main()
{
  const char str2[] = "def_";
  char *str1 = nullptr;
  char *result = nullptr;
  try
  {
    str1 = yapparov::readLine(std::cin);
    if (str1 == nullptr)
    {
      std::cerr << "failed to read string" << "\n";
      return 1;
    }
    const size_t len1 = std::strlen(str1);
    const size_t len2 = std::strlen(str2);
    result = new char[len1 + len2 + 1];
    yapparov::twoRows(result, str1, str2);
    std::cout << result << "\n";
  }
  catch (const std::bad_alloc &)
  {
    std::cerr << "memory error" << "\n";
    delete[] str1;
    delete[] result;
    return 1;
  }
  delete[] str1;
  delete[] result;
  return 0;
}

namespace yapparov
{
  char *readLine(std::istream &in)
  {
    const size_t per_size = 16;
    size_t size = per_size;
    size_t len = 0;
    char *str = new char[size];
    char symb = 0;
    while (in.get(symb) && symb != '\n')
    {
      if (len + 1 >= size)
      {
        const size_t new_size = size * 2;
        char *temp = nullptr;
        try
        {
          temp = new char[new_size];
        }
        catch (const std::bad_alloc &)
        {
          delete[] str;
          throw;
        }
        for (size_t i = 0; i < len; ++i)
        {
          temp[i] = str[i];
        }
        delete[] str;
        str = temp;
        size = new_size;
      }
      str[len++] = symb;
    }
    if (len == 0 && in.eof())
    {
      delete[] str;
      return nullptr;
    }
    str[len] = '\0';
    return str;
  }

  char *twoRows(char *newstr, const char *str1, const char *str2)
  {
    int i = 0, j = 0, k = 0;
    while (str1[i] != '\0' && str2[j] != '\0')
    {
      newstr[k++] = str1[i++];
      newstr[k++] = str2[j++];
    }
    while (str1[i] != '\0')
    {
      newstr[k++] = str1[i++];
    }
    while (str2[j] != '\0')
    {
      newstr[k++] = str2[j++];
    }
    newstr[k] = '\0';
    return newstr;
  }
}

#include <iostream>
#include <cstring>
#include <new>

namespace semenets
{
  char* readLine(std::istream& in);
  char* uncSym(const char* str, const char* literal, char* result);
}

int main()
{
  char* str = nullptr;
  char* result = nullptr;
  const char* const literal = "abc_ef";
  try
  {
    str = semenets::readLine(std::cin);
    if (std::strlen(str) == 0)
    {
      std::cerr << "Error: Empty input\n";
      delete[] str;
      return 1;
    }
    result = new char[std::strlen(str) + std::strlen(literal) + 1];
  }
  catch (const std::bad_alloc&)
  {
    std::cerr << "Memory error\n";
    delete[] str;
    return 1;
  }
  semenets::uncSym(str, literal, result);
  std::cout << result << "\n";
  delete[] str;
  delete[] result;
  return 0;
}

namespace semenets
{
  char* readLine(std::istream& in)
  {
    const size_t i_size = 16;
    size_t izn_size = i_size;
    size_t size = 0;
    char* buf = new char[izn_size];
    char c = 0;
    while (in.get(c) && c != '\n')
    {
      if (size + 1 == izn_size)
      {
        izn_size *= 2;
        char* more_big = nullptr;
        try
        {
          more_big = new char[izn_size];
        }
        catch (const std::bad_alloc&)
        {
          delete[] buf;
          throw;
        }
        for (size_t i = 0; i < size; i++)
        {
          more_big[i] = buf[i];
        }
        delete[] buf;
        buf = more_big;
      }
      buf[size] = c;
      ++size;
    }
    buf[size] = '\0';
    return buf;
  }

  char* uncSym(const char* str, const char* literal, char* result)
  {
    size_t z = 0;
    const size_t len_str = std::strlen(str);
    const size_t len_lit = std::strlen(literal);
    for (size_t i = 0; literal[i] != '\0'; i++)
    {
      size_t count_sym = 0;
      for (size_t j = 0; str[j] != '\0'; j++)
      {
        if (literal[i] != str[j])
        {
          ++count_sym;
        }
      }
      if (count_sym == len_str)
      {
        result[z] = literal[i];
        z++;
      }
    }
    for (size_t i = 0; str[i] != '\0'; i++)
    {
      size_t count_sym = 0;
      for (size_t j = 0; literal[j] != '\0'; j++)
      {
        if (str[i] != literal[j])
        {
          ++count_sym;
        }
      }
      if (count_sym == len_lit)
      {
        result[z] = str[i];
        z++;
      }
    }
    result[z] = '\0';
    return result;
  }
}

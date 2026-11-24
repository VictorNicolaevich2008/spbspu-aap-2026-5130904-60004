#include <cstddef>
#include <cstring>
#include <iostream>
#include <new>

namespace maksimov
{
  char *readChar(std::istream &in);
  std::size_t excludeChar(const char *source, const char *excluded, char *result, std::size_t result_size);
}

int main()
{
  const char *const excluded = "abc";
  char *str = nullptr;
  char *result = nullptr;
  try
  {
    str = maksimov::readChar(std::cin);
    if (str[0] == '\0')
    {
      std::cerr << "No input\n";
      delete[] str;
      return 1;
    }
    const std::size_t size = std::strlen(str) + 1;
    result = new char[size];
    maksimov::excludeChar(str, excluded, result, size);
    std::cout << result << "\n";
  }
  catch (const std::bad_alloc &)
  {
    std::cerr << "Memory error\n";
    delete[] str;
    delete[] result;
    return 1;
  }
  delete[] str;
  delete[] result;
  return 0;
}

char *maksimov::readChar(std::istream &in)
{
  const std::size_t initialSize = 16;
  std::size_t allocated = initialSize;
  std::size_t count = 0;
  char *line = new char[allocated];
  char c = '\0';
  while (in.get(c) && c != '\n')
  {
    if (count + 1 == allocated)
    {
      char *bigger = nullptr;
      try
      {
        bigger = new char[allocated * 2];
      }
      catch (const std::bad_alloc &)
      {
        delete[] line;
        throw;
      }
      for (std::size_t i = 0; i < count; ++i)
      {
        bigger[i] = line[i];
      }
      delete[] line;
      line = bigger;
      allocated *= 2;
    }
    line[count] = c;
    ++count;
  }
  line[count] = '\0';
  return line;
}

std::size_t maksimov::excludeChar(const char *source, const char *excluded, char *result, std::size_t result_size)
{
  std::size_t total = 0;
  std::size_t written = 0;
  for (std::size_t i = 0; source[i] != '\0'; ++i)
  {
    const char *const found = std::strchr(excluded, source[i]);
    if (found == nullptr)
    {
      ++total;
      if (written + 1 < result_size)
      {
        result[written] = source[i];
        ++written;
      }
    }
  }
  result[written] = '\0';
  return total;
}

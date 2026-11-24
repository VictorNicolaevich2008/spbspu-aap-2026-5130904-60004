#include <iostream>
#include <new>
#include <cctype>

namespace chervov
{
  char* lowerLatin(const char* src, char* dst);
  char* readLine(std::size_t& out_length);
}

int main()
{
  char* input = nullptr;
  char* result = nullptr;
  try
  {
    std::size_t length = 0;
    input = chervov::readLine(length);
    if (input[0] == '\0')
    {
      std::cerr << "No input string" << "\n";
      delete[] input;
      return 1;
    }
    result = new char[length + 1];
    chervov::lowerLatin(input, result);
    std::cout << result << '\n';
  }
  catch (const std::bad_alloc&)
  {
    std::cerr << "Not enough memory" << "\n";
    delete[] result;
    delete[] input;
    return 1;
  }
  delete[] result;
  delete[] input;
  return 0;
}

char* chervov::readLine(std::size_t& length)
{
  const std::size_t initialCapacity = 8;
  std::size_t capacity = initialCapacity;
  length = 0;
  char* buf = new char[capacity];
  int ch = 0;
  while ((ch = std::cin.get()) != EOF && ch != '\n')
  {
    if (length + 1 >= capacity)
    {
      const std::size_t new_capacity = capacity * 2;
      char* const tmp = new char[new_capacity];
      for (std::size_t i = 0; i < length; ++i)
      {
        tmp[i] = buf[i];
      }
      delete[] buf;
      buf = tmp;
      capacity = new_capacity;
    }
    buf[length++] = static_cast< char >(ch);
  }
  buf[length] = '\0';
  return buf;
}

char* chervov::lowerLatin(const char* src, char* dst)
{
  char* out = dst;
  for (const char* p = src; *p != '\0'; ++p, ++out)
  {
    const char c = *p;
    if (std::isupper(static_cast< unsigned char >(c)))
    {
      *out = static_cast< char >(std::tolower(static_cast< unsigned char >(c)));
    }
    else
    {
      *out = c;
    }
  }
  *out = '\0';
  return dst;
}

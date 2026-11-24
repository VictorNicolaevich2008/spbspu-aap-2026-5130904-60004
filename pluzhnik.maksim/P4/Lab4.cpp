#include <iostream>
#include <cctype>
#include <new>

namespace pluzhnik
{
  char* removeDigits(char* dest, const char* src) noexcept;
  char* readLine(std::istream& in, std::size_t* out_size);
}

int main()
{
  std::size_t length = 0;
  const char* const input_str = pluzhnik::readLine(std::cin, &length);
  if (input_str == nullptr)
  {
    std::cerr << "Error: memory" << std::endl;
    return 1;
  }

  char* const result_str = new (std::nothrow) char[length + 1];
  if (result_str == nullptr)
  {
    std::cerr << "Error: memory" << std::endl;
    delete[] input_str;
    return 1;
  }

  pluzhnik::removeDigits(result_str, input_str);

  std::cout << result_str << std::endl;

  delete[] input_str;
  delete[] result_str;

  return 0;
}

namespace pluzhnik
{

  char* removeDigits(char* dest, const char* src) noexcept
  {
    char* target = dest;
    while (*src != '\0')
    {
      if (!std::isdigit(static_cast< unsigned char >(*src)))
      {
        *target = *src;
        ++target;
      }
      ++src;
    }
    *target = '\0';
    return dest;
  }

  char* readLine(std::istream& in, std::size_t* out_size)
  {
    const std::size_t INITIAL_CAPACITY = 16;
    std::size_t capacity = INITIAL_CAPACITY;
    std::size_t size = 0;

    char* buffer = new (std::nothrow) char[capacity];
    if (buffer == nullptr)
    {
      return nullptr;
    }

    char ch = '\0';
    std::noskipws(in);

    while (in >> ch && ch != '\n')
    {
      if (size + 1 >= capacity)
      {
        const std::size_t new_capacity = capacity * 2;
        char* const new_buffer = new (std::nothrow) char[new_capacity];
        if (new_buffer == nullptr)
        {
          delete[] buffer;
          return nullptr;
        }

        for (std::size_t i = 0; i < size; ++i)
        {
          new_buffer[i] = buffer[i];
        }

        delete[] buffer;
        buffer = new_buffer;
        capacity = new_capacity;
      }

      buffer[size] = ch;
      ++size;
    }

    buffer[size] = '\0';

    if (ch != '\n' && size == 0)
    {
      delete[] buffer;
      return nullptr;
    }

    char* const exact_buffer = new (std::nothrow) char[size + 1];
    if (exact_buffer != nullptr)
    {
      for (std::size_t i = 0; i <= size; ++i)
      {
        exact_buffer[i] = buffer[i];
      }
      delete[] buffer;
      buffer = exact_buffer;
    }

    if (out_size != nullptr)
    {
      *out_size = size;
    }

    return buffer;
  }
}

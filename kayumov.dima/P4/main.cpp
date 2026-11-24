#include <iostream>
#include <cctype>
#include <cstring>
#include <exception>

namespace ksyumov
{
  char * mergeInterleaved(char * const dest, const char * src1, const char * src2, const size_t dest_size) noexcept
  {
    if (dest == nullptr || src1 == nullptr || src2 == nullptr || dest_size == 0)
    {
      return nullptr;
    }

    size_t i = 0;
    size_t j = 0;
    size_t k = 0;

    while ((src1[i] != '\0' || src2[j] != '\0') && k < dest_size - 1)
    {
      if (src1[i] != '\0')
      {
        dest[k++] = src1[i++];
      }

      if (src2[j] != '\0' && k < dest_size - 1)
      {
        dest[k++] = src2[j++];
      }
    }

    dest[k] = '\0';
    return dest;
  }
}

int main()
{
  const char * const literal_str = "def_";

  char * input_buffer = nullptr;
  char * result_buffer = nullptr;

  try
  {
    const size_t initial_capacity = 16;
    size_t capacity = initial_capacity;
    size_t length = 0;

    input_buffer = new char[capacity];

    char ch = '\0';

    while (std::cin.get(ch))
    {
      if (ch == '\n')
      {
        break;
      }

      if (length + 1 >= capacity)
      {
        capacity *= 2;

        char * const new_buffer = new char[capacity];

        std::strncpy(new_buffer, input_buffer, length);
        delete[] input_buffer;
        input_buffer = new_buffer;
      }

      input_buffer[length++] = ch;
    }

    input_buffer[length] = '\0';

    if (length == 0)
    {
      std::cerr << "Error: Input is empty." << std::endl;
      delete[] input_buffer;
      return 1;
    }

    const size_t result_capacity = length + std::strlen(literal_str) + 1;

    result_buffer = new char[result_capacity];

    char * const status = ksyumov::mergeInterleaved(result_buffer, input_buffer, literal_str, result_capacity);

    if (status != nullptr)
    {
      std::cout << result_buffer << std::endl;
    }
    else
    {
      std::cerr << "Error: Transformation failed due to invalid arguments." << std::endl;
      delete[] input_buffer;
      delete[] result_buffer;
      return 1;
    }

    delete[] input_buffer;
    delete[] result_buffer;
  }
  catch (const std::bad_alloc & e)
  {
    std::cerr << "Error: Memory allocation failed (" << e.what() << ")." << std::endl;
    delete[] input_buffer;
    delete[] result_buffer;
    return 1;
  }

  return 0;
}

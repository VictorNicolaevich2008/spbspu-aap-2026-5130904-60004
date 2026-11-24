#include <cstring>
#include <iostream>

namespace fomin
{
  char *strChange(char *modified_buffer, const char *buffer, size_t size, char target_char, char new_char) noexcept;
}

int main()
{
  const size_t initial_capacity = 16;
  char *buffer = nullptr;
  try
  {
    buffer = new char[initial_capacity];
  }
  catch (const std::bad_alloc &)
  {
    std::cerr << "Out of memory\n";
    return 1;
  }

  size_t capacity = initial_capacity;
  size_t size = 0;
  int ch = std::cin.get();

  if (ch != '\n' && ch != EOF)
  {
    buffer[size] = static_cast< char >(ch);
    while (ch != '\n' && ch != EOF)
    {
      ch = std::cin.get();
      size++;
      if (size + 1 >= capacity)
      {
        try
        {
          const size_t new_capacity = capacity * 2;
          char *const new_buffer = new char[new_capacity];
          memcpy(new_buffer, buffer, size);
          delete[] buffer;
          buffer = new_buffer;
          capacity = new_capacity;
        }
        catch (const std::bad_alloc &)
        {
          delete[] buffer;
          std::cerr << "Out of memory\n";
          return 1;
        }
      }

      if (ch != '\n' && ch != EOF)
      {
        buffer[size] = static_cast< char >(ch);
      }
      else
      {
        buffer[size] = '\0';
      }
    }
  }
  else
  {
    buffer[0] = '\0';
  }

  if (size == 0)
  {
    delete[] buffer;
    std::cerr << "empty input\n";
    return 1;
  }

  try
  {
    char *const modified_buffer = new char[size + 1];
    std::cout << "Choice a taget char\n";
    char target_char = '\0';
    std::cin >> target_char;
    std::cout << "Choice a new char\n";
    char new_char = '\0';
    std::cin >> new_char;

    std::cout << fomin::strChange(modified_buffer, buffer, size + 1, target_char, new_char) << '\n';
    delete[] buffer;
    delete[] modified_buffer;
    return 0;
  }
  catch (const std::bad_alloc &)
  {
    std::cerr << "Out of memory\n";
    delete[] buffer;
    return 1;
  }
}

namespace fomin
{
  char *strChange(char *modified_buffer, const char *buffer, size_t size, char target_char, char new_char) noexcept
  {
    for (size_t i = 0; i < size; i++)
    {
      if (buffer[i] == target_char)
      {
        modified_buffer[i] = new_char;
      }
      else
      {
        modified_buffer[i] = buffer[i];
      }
    }
    return modified_buffer;
  }
}

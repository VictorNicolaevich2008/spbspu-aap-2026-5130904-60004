#include <cctype>
#include <cstring>
#include <iostream>
namespace romanov
{
  void readDynamicString(char*& buffer, int& length);
  void removeLatin(char* buffer, const char* my_str);
}
int main()
{
  char* my_str = nullptr;
  int length = 0;
  std::cout << "Write a line" << '\n';
  romanov::readDynamicString(my_str, length);
  try
  {
    char* const new_str = new char[length + 1];
    romanov::removeLatin(new_str, my_str);
    std::cout << "The new line is " << new_str << '\n';
    delete[] new_str;
  }
  catch (...)
  {
    delete[] my_str;
    std::cerr << "Memory allocation fail\n";
    return 1;
  }
  delete[] my_str;
  return 0;
}
void romanov::readDynamicString(char*& buffer, int& length)
{
  int capacity = 10;
  length = 0;
  try
  {
    buffer = new char[capacity];
    char ch = 0;
    while (std::cin.get(ch) && ch != '\n')
    {
      if (length + 1 >= capacity)
      {
        capacity *= 2;
        char* const new_buffer = new char[capacity];
        std::copy(buffer, buffer + length, new_buffer);
        delete[] buffer;
        buffer = new_buffer;
      }
      buffer[length] = ch;
      length++;
    }
    if (length == 0)
    {
      delete[] buffer;
      buffer = nullptr;
      std::cerr << "Empty input\n";
      std::exit(1);
    }
    buffer[length] = '\0';
  }
  catch (...)
  {
    std::cerr << "Memory allocation fail\n";
    std::exit(1);
  }
}
void romanov::removeLatin(char* buffer, const char* my_str)
{
  int write_index = 0;
  int read_index = 0;
  while (my_str[read_index] != '\0')
  {
    const char ch = my_str[read_index];
    if (!std::isalpha(ch))
    {
      buffer[write_index] = my_str[read_index];
      write_index++;
    }
    read_index++;
  }
  buffer[write_index] = '\0';
}

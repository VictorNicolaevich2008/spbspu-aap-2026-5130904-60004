#include <iostream>
#include <new>

namespace zaytseva
{
  char* replaceSymbol(const char* source, char symb1, char symb2, char* result);
}

int main()
{
  const int initial_max_size = 16;
  int max_size = initial_max_size;
  int length = 0;
  char* str = nullptr;
  char* result = nullptr;
  try
  {
    str = new char[max_size + 1];
    std::cout << "Enter a string:\n";
    while (true)
    {
      const int ch = std::cin.get();
      if (ch == EOF || ch == '\n')
      {
        break;
      }
      if (length >= max_size)
      {
        char* const new_str = new char[max_size * 2 + 1];
        for (int i = 0; i < length; i++)
        {
          new_str[i] = str[i];
        }
        delete[] str;
        str = new_str;
        max_size = max_size * 2;
      }
      str[length] = ch;
      ++length;
    }
    str[length] = '\0';
    if (length == 0)
    {
      std::cerr << "Empty input\n";
      delete[] str;
      return 1;
    }
    char symb1 = '\0';
    char symb2 = '\0';
    std::cout << "Enter the symbols. First, the one to be replaced.\n";
    std::cin >> symb1 >> symb2;
    result = new char[length + 1];
    std::cout << zaytseva::replaceSymbol(str, symb1, symb2, result) << "\n";
    delete[] result;
    delete[] str;
    return 0;
  }
  catch (const std::bad_alloc&)
  {
    delete[] result;
    delete[] str;
    std::cerr << "Memory error!\n";
    return 1;
  }
}

namespace zaytseva
{
  char* replaceSymbol(const char* source, char symb1, char symb2, char* result)
  {
    int written = 0;
    for (int i = 0; source[i] != '\0'; i++)
    {
      if (source[i] == symb1)
      {
        result[written] = symb2;
      }
      else
      {
        result[written] = source[i];
      }
      ++written;
    }
    result[written] = '\0';
    return result;
  }
}

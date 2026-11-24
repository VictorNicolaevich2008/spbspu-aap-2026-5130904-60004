#include <iostream>
#include <stdexcept>

namespace pechnikov
{
  void delspace(const char *, char *, int);
}

int main()
{
  const int initial_max_size = 16;
  int max_size = initial_max_size;
  int length = 0;
  char *str = nullptr;
  char *nice_str = nullptr;

  try
  {
    str = new char[max_size + 1];
    while (true)
    {
      const int ch = std::cin.get();
      if (ch == EOF || ch == '\n')
      {
        break;
      }
      if (length >= max_size)
      {
        char *const new_str = new char[max_size * 2 + 1];
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
      throw std::invalid_argument("Empty string");
    }
    nice_str = new char[length + 1];

    pechnikov::delspace(str, nice_str, length);
    std::cout << nice_str << "\n";

    delete[] nice_str;
    nice_str = nullptr;
    delete[] str;
    str = nullptr;

    return 0;
  }
  catch (const std::bad_alloc &)
  {
    delete[] nice_str;
    nice_str = nullptr;
    delete[] str;
    str = nullptr;
    std::cerr << "error memory";
    return 1;
  }
  catch (const std::invalid_argument &err)
  {
    std::cerr << err.what() << '\n';
    delete[] str;
    str = nullptr;
    return 2;
  }
}

void pechnikov::delspace(const char *str, char *nice_str, int length)
{
  int space_pod = 1;
  int length_nice = 0;
  for (int i = 0; i < length; i++)
  {
    if (str[i] == ' ')
    {
      space_pod += 1;
    }
    else
    {
      space_pod = 0;
    }
    if (space_pod <= 1)
    {
      nice_str[length_nice] = str[i];
      length_nice += 1;
    }
  }
  if (length_nice > 0 && nice_str[length_nice - 1] == ' ')
  {
    --length_nice;
  }

  nice_str[length_nice] = '\0';
}

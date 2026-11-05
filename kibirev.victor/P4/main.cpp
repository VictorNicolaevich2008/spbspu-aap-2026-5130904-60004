#include <iostream>
#include <new>
namespace kibirev
{
  std::istream &readstr(std::istream &input, char *&string, size_t &len);
  int hasSam(const char *str1, const char *str2, size_t len1, size_t len2);
}
int main()
{
  char *str1;
  char *str2;
  try
  {
    str1 = new char[1]{'\0'};
    size_t len1 = 0;
    str2 = new char[1]{'\0'};
    size_t len2 = 0;
    kibirev::readstr(std::cin, str1, len1);
    kibirev::readstr(std::cin, str2, len2);

    const int res = kibirev::hasSam(str1, str2, len1, len2);

    std::cout << res << '\n';
    delete[] str2;
    delete[] str1;
    return 0;
  }
  catch (const std::bad_alloc &e)
  {
    std::cerr << e.what() << '\n';
    delete[] str2;
    delete[] str1;
    return 1;
  }
}

std::istream &kibirev::readstr(std::istream &input, char *&string, size_t &len)
{
  size_t i = 0;
  char c;
  while (input.get(c) && c != '\n')
  {
    i++;
    char *dop = new char[i + 1];
    for (size_t j = 0; j < i - 1; j++)
    {
      dop[j] = string[j];
    }
    dop[i - 1] = c;
    dop[i] = '\0';
    delete[] string;
    string = dop;
  }
  len = i;
  return input;
}
int kibirev::hasSam(const char *str1, const char *str2, size_t len1, size_t len2)
{
  for (size_t i = 0; i < len1; i++)
  {
    for (size_t j = 0; j < len2; j++)
    {
      if (str1[i] == str2[j])
      {
        return 1;
      }
    }
  }
  return 0;
}

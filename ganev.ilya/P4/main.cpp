#include <iostream>
#include <cstring>
#include <stdexcept>

namespace ganev
{
  char* readString(std::istream& in);
  char* appendChar(const char* string, char let, int new_size);
  void unicSymbols(const char* str1, const char* str2, char* res);
  bool isContain(const char* str, char let);
}
int main()
{
  char* string = nullptr;
  try
  {
    string = ganev::readString(std::cin);
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << '\n';
    return 1;
  }

  if (string == nullptr || string[0] == '\0')
  {
    std::cerr << "Empty input";
    delete[] string;
    return 1;
  }

  const char* const string2 = "abc ef";
  char* const result = new char[std::strlen(string) + std::strlen(string2) + 1];
  ganev::unicSymbols(string, string2, result);
  std::cout << result;
  delete[] string;
  delete[] result;
}

char* ganev::readString(std::istream& in)
{
  char* line = new char[1];
  char c = '\0';
  int index = 0;
  while (in.get(c))
  {
    line = ganev::appendChar(line, c, index + 1);
    index++;
  }
  line = ganev::appendChar(line, '\0', index + 1);
  return line;
}

char* ganev::appendChar(const char* string, char let, int new_size)
{
  char* appended = nullptr;
  try
  {
    appended = new char[new_size];
  }
  catch (const std::bad_alloc& e)
  {
    delete[] string;
    throw std::runtime_error("Memory error");
  }
  for (int i = 0; i < new_size - 1; i++)
  {
    appended[i] = string[i];
  }
  appended[new_size - 1] = let;
  delete[] string;
  return appended;
}

void ganev::unicSymbols(const char* str1, const char* str2, char* res)
{
  int index = 0;
  for (const char* let = str1; *let; let++)
  {
    if (!ganev::isContain(str2, *let))
    {
      res[index] = *let;
      index++;
    }
  }
  for (const char* let = str2; *let; let++)
  {
    if (!ganev::isContain(str1, *let))
    {
      res[index] = *let;
      index++;
    }
  }
  res[index] = '\0';
}

bool ganev::isContain(const char* str, char let)
{
  for (const char* i = str; *i; i++)
  {
    if (*i == let || let == '\n')
    {
      return true;
    }
  }
  return false;
}

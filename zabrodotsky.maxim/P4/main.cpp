#include <iostream>
#include <cstddef>
namespace zabrodotsky {
  int duplicates(const char* str)
  {
    if (str == nullptr || str[0] == '\0') {
      return 0;
    }
    for (std::size_t i = 0; str[i] != '\0' && str[i + 1] != '\0'; ++i) {
      if (str[i] == str[i + 1]) {
        return 1;
      }
    }
    return 0;
  }
}
int main()
{
  const std::size_t Size = 1000;
  char input_buffer[Size];
  if (!std::cin.getline(input_buffer, Size)) {
    std::cerr << "Failed to read input\n";
    return 1;
  }
  const int result = zabrodotsky::duplicates(input_buffer);
  std::cout << result << "\n";
  return 0;
}

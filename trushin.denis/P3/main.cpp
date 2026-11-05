#include <cstddef>
#include <fstream>
#include <iostream>
#include <new>
namespace trushin {
  bool number(const char *str, int &num);
  size_t countGoodStolb(const int *a, size_t y, size_t x);
}
int main(int argc, char **argv)
{
  if (argc != 4) {
    std::cerr << "Bad arguments\n";
    return 1;
  }
  int num = 0;
  if (trushin::number(argv[1], num) != true || (num != 1 && num != 2)) {
    std::cerr << "Bad first parametr\n";
    return 1;
  }
  std::ifstream input(argv[2]);
  if (input.fail()) {
    std::cerr << "Cannot open file\n";
    return 2;
  }
  int a = 0;
  int b = 0;
  input >> a >> b;
  if (input.fail()) {
    std::cerr << "Bad Zifra\n";
    return 2;
  }
  if (b < 0 || a < 0) {
    std::cerr << "invalid matrix\n";
    return 2;
  }
  const size_t y = a;
  const size_t x = b;
  const size_t maxSize = 10000;
  const size_t count = x * y;
  int fix[maxSize] = {};
  int *dynamic = nullptr;
  int *matrix = nullptr;
  if (num == 1) {
    matrix = fix;
  }
  if (num == 2) {
    try {
      dynamic = new int[count];
      matrix = dynamic;
    } catch (const std::bad_alloc &) {
      std::cerr << "bad alloc\n";
      return 2;
    }
  }
  for (size_t i = 0; i < count; ++i) {
    input >> matrix[i];
    if (input.fail()) {
      std::cerr << "Error\n";
      delete[] dynamic;
      return 2;
    }
  }
  const size_t sum = trushin::countGoodStolb(matrix, y, x);
  std::ofstream output(argv[3]);
  output << sum << '\n';
  delete[] dynamic;
  return 0;
}
bool trushin::number(const char *str, int &num)
{
  int result = 0;
  if (str[0] == '\0') {
    return false;
  }
  for (size_t i = 0; str[i] != '\0'; ++i) {
    if (str[i] < '0' || str[i] > '9') {
      return false;
    }
  }
  for (size_t i = 0; str[i] != '\0'; ++i) {
    result = result * 10 + (str[i] - '0');
    if (result > 2) {
      return false;
    }
  }
  num = result;
  return true;
}
size_t trushin::countGoodStolb(const int *a, size_t y, size_t x)
{
  size_t count = 0;
  for (size_t j = 0; j < x; ++j) {
    bool good = true;
    for (size_t i = 1; i < y; ++i) {
      if (a[i * x + j] == a[(i - 1) * x + j]) {
        good = false;
        break;
      }
    }
    if (good) {
      ++count;
    }
  }
  return count;
}

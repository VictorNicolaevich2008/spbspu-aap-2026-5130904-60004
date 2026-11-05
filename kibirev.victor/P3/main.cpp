#include <iostream>
#include <cstddef>
#include <fstream>
#include <cstdint>
#include <new>
namespace kibirev {
  int maxSumMdg(const int *arr, size_t n, size_t m);
}
const size_t Max_Size = 10000;
int main(int argc, char **argv)
{
  if (argc < 4) {
    std::cerr << "Not enough arguments.\n";
    return 1;
  }
  if (argc > 4) {
    std::cerr << "Too many arguments.\n";
    return 1;
  }
  if (argv[1][0] == '\0') {
    std::cerr << "First parameter is not a number.\n";
    return 1;
  }
  for (size_t i = 0; argv[1][i] != '\0'; i++) {
    if (argv[1][i] < '0' || argv[1][i] > '9') {
      std::cerr << "First parameter is not a number.\n";
      return 1;
    }
  }
  if (!((argv[1][0] == '1' && argv[1][1] == '\0') || (argv[1][0] == '2' && argv[1][1] == '\0'))) {
    std::cerr << "First parameter is out of range.\n";
    return 1;
  }
  const int type_arr = argv[1][0] - '0';
  std::ifstream input(argv[2]);
  if (!input) {
    std::cerr << "Входной файл не открылся.\n";
    return 2;
  }
  int *arr = nullptr;
  int *arrd = nullptr;
  int fix_arr[Max_Size];
  size_t n = 0, m = 0;
  if (!(input >> n)) {
    std::cerr << "Не удалось прочитать n.\n";
    return 2;
  }
  if (!(input >> m)) {
    std::cerr << "Не удалось прочитать m.\n";
    return 2;
  }
  if (m != 0) {
    if (n > SIZE_MAX / m) {
      std::cerr << "Слишком большая матрица.\n";
      return 2;
    }
  }
  if (type_arr == 1) {
    if (m != 0) {
      if (n > Max_Size / m) {
        std::cerr << "Слишком большая матрица.\n";
        return 2;
      }
    }
    arr = fix_arr;
  } else if (type_arr == 2) {
    try {
      arrd = new int[n * m];
      arr = arrd;
    } catch (const std::bad_alloc &) {
      std::cerr << "Недостаточно памяти для выделения массива.\n";
      return 2;
    }
  }
  for (size_t i = 0; i < n * m; i++) {
    if (!(input >> arr[i])) {
      delete[] arrd;
      std::cerr << "Ошибка ввода.\n";
      return 2;
    }
  }
  const int res = kibirev::maxSumMdg(arr, n, m);
  std::ofstream output(argv[3]);
  if (!output) {
    delete[] arrd;
    std::cerr << "Не удалось открыть итоговый файл.\n";
    return 2;
  }
  output << res << '\n';
  delete[] arrd;
  return 0;
}

namespace kibirev {
  int maxSumMdg(const int *arr, size_t n, size_t m)
  {
    if (n < 2 || m < 2) {
      return 0;
    }
    const size_t size = (n < m ? n : m);
    int max = arr[0];
    for (size_t d = 0; d < 2 * size - 1; d++) {
      if (d == size - 1) {
        continue;
      }
      int sum = 0;
      for (size_t i = 0; i < size; i++) {
        if (i <= d) {
          if (d - i < size) {
            sum += arr[i * m + (d - i)];
          }
        }
      }
      max = (sum > max ? sum : max);
    }
    return max;
  }
}

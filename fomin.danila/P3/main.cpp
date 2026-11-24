#include <charconv>
#include <fstream>
#include <iostream>
#include <new>
#include <stdexcept>
int main(int argc, char *argv[])
{
  if (argc < 4) {
    std::cerr << "Not enought arguments" << "\n";
    return 1;
  }
  if (argc > 4) {
    std::cerr << "Too many arguments";
    return 1;
  }
  const char *const arg1 = argv[1];
  const char *arg1_end = arg1;
  while (*arg1_end != '\0') {
    ++arg1_end;
  }
  int numeric = 0;
  auto res = std::from_chars(arg1, arg1_end, numeric);
  if (res.ec != std::errc{} || res.ptr != arg1_end) {
    std::cerr << "First parameter is not integer\n";
    return 1;
  }
  if (numeric != 1 && numeric != 2) {
    std::cerr << "First parametr out of range\n";
    return 1;
  }
  std::ifstream in(argv[2]);
  if (!in.is_open()) {
    std::cerr << "Can't open this file, mb it's empty?";
    return 2;
  }
  std::ofstream out(argv[3]);
  if (!out.is_open()) {
    std::cerr << "Error create out file";
    return 2;
  }
  int num = 0;
  int size_x = 0;
  int size_y = 0;
  int k = 0;
  int g = 0;
  const int size = 10000;
  int static_massive[size];
  int *matrix = nullptr;
  try {
    if (!(in >> size_y >> size_x) || size_x < 0 || size_y < 0) {
      throw std::invalid_argument("Size of matrix not integer which more than zero");
    }
    if (size_x == 0 || size_y == 0) {
      std::cout << "0";
      return 0;
    }
    if (numeric == 2) {
      matrix = new int[size_x * size_y];
    } else {
      matrix = static_massive;
    }
    while (in >> num) {
      if (k >= size_x * size_y) {
        throw std::invalid_argument("Too many arguments");
      }
      matrix[k] = num;
      ++k;
    }
    if (!in.eof()) {
      throw std::invalid_argument("Writed not int in matrix or size matrix");
    }
    if (k != size_x * size_y) {
      throw std::invalid_argument("Not enought arguments");
    }
  } catch (const std::invalid_argument &e) {
    if (numeric == 2) {
      delete[] matrix;
      matrix = nullptr;
    }
    std::cerr << "Error: " << e.what() << "\n";
    return 1;
  } catch (const std::bad_alloc &e) {
    std::cerr << "Bad_alloc error" << "\n";
    return 2;
  }
  in.close();
  for (int i = 0; i < size_x - 1; ++i) {
    if (matrix[i] == matrix[i + 1]) {
      ++g;
      i = size_x;
    }
  }
  for (int i = 1; i < size_y; ++i) {
    for (int h = 1; h <= size_x - 1; ++h) {
      if (matrix[h + size_x * i - 1] == matrix[h + size_x * i]) {
        ++g;
        h = size_x;
      }
    }
  }
  out << size_y - g << "\n";
  if (numeric == 2) {
    delete[] matrix;
    matrix = nullptr;
  }
}

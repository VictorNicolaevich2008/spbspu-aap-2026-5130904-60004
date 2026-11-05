#include <iostream>
#include <fstream>
#include <new>

const int max_elements = 10000;

namespace semenets
{
  void spiralDecrease(int* a, int n, int m);
}

int main(int argc, char* argv[])
{
  if (argc != 4)
  {
    std::cerr << "Error: programm need 3 parameters\n";
    return 1;
  }
  int num = 0;
  if (argv[1][0] == '1' && argv[1][1] == '\0')
  {
    num = 1;
  }
  else if (argv[1][0] == '2' && argv[1][1] == '\0')
  {
    num = 2;
  }
  else
  {
    std::cerr << "Error: first parameter not a number 1 or 2\n";
    return 1;
  }

  std::ifstream input(argv[2]);
  int n = 0;
  int m = 0;
  if (!(input) || !(input >> n) || !(input >> m))
  {
    std::cerr << "Wrong input fail\n";
    return 2;
  }
  if (n < 0 || m < 0)
  {
    std::cerr << "Rows and cols do not be < 0\n";
    return 2;
  }
  long long total = n;
  total = total * m;
  int fixed_array[max_elements];
  int* a = nullptr;
  int* arr = nullptr;
  if (num == 1)
  {
    if (total > max_elements)
    {
      std::cerr << "Too many elements\n";
      return 2;
    }
    a = fixed_array;
  }
  if (num == 2)
  {
    try
    {
      arr = new int[total];
      a = arr;
    }
    catch (const std::bad_alloc&)
    {
      std::cerr << "Not enough memory\n";
      return 2;
    }
  }
  for (long long i = 0; i < total; i++)
  {
    if (!(input >> a[i]))
    {
      std::cerr << "Wrong element matrix\n";
      if (num == 2)
      {
        delete[] arr;
      }
      return 2;
    }
  }
  semenets::spiralDecrease(a, n, m);
  std::ofstream output(argv[3]);
  if (!output)
  {
    std::cerr << "Error: output fail do not open\n";
    if (num == 2)
    {
      delete[] arr;
    }
    return 2;
  }
  output << n << " " << m;
  for (long long i = 0; i < total; i++)
  {
    output << " " << a[i];
  }
  output << std::endl;
  if (num == 2)
  {
    delete[] arr;
  }
  return 0;
}

namespace semenets
{
  void spiralDecrease(int* a, int n, int m)
  {
    int i = 0;
    int i1 = n - 1;
    int j = 0;
    int j1 = m - 1;
    int z = 1;
    while (i <= i1 && j <= j1)
    {
      for (int k = j; k <= j1; k++)
      {
        a[i * m + k] -= z;
        ++z;
      }
      ++i;
      for (int p = i; p <= i1; p++)
      {
        a[p * m + j1] -= z;
        ++z;
      }
      --j1;
      if (i <= i1)
      {
        for (int l = j1; l >= j; l--)
        {
          a[i1 * m + l] -= z;
          ++z;
        }
        --i1;
      }
      if (j <= j1)
      {
        for (int q = i1; q >= i; q--)
        {
          a[q * m + j] -= z;
          ++z;
        }
        ++j;
      }
    }
  }
}

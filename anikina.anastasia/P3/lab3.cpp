#include <fstream>
#include <iostream>

namespace anikina
{
  const int max_size = 10000;
  int countlocalmax(const int* a, int rows, int cols);
}

int main(int argc, char* argv[])
{
  int* heap = nullptr;
  try
  {
    if (argc != 4)
    {
      throw 1;
    }
    const char num = argv[1][0];
    if ((num != '1' && num != '2') || argv[1][1] != '\0')
    {
      throw 1;
    }

    std::ifstream in(argv[2]);
    if (!in.is_open())
    {
      throw 3;
    }
    int rows = 0;
    int cols = 0;
    int st[anikina::max_size];
    if (!(in >> rows >> cols) || rows < 0 || cols < 0)
    {
      throw 2;
    }
    const long long total = rows * cols;
    if (num == '1' && total > anikina::max_size)
    {
      throw 2;
    }

    if (num == '2')
    {
      try
      {
        heap = new int[total];
      }
      catch (...)
      {
        throw 2;
      }
    }
    int* a = st;
    if (heap != nullptr)
    {
      a = heap;
    }

    bool read_ok = true;
    for (long long i = 0; i < total && read_ok; ++i)
    {
      if (!(in >> a[i]))
      {
        read_ok = false;
      }
    }
    char trailing = 0;
    if (!read_ok || (in >> trailing))
    {
      throw 2;
    }

    const int cnt = anikina::countlocalmax(a, rows, cols);
    delete[] heap;
    heap = nullptr;
    std::ofstream out(argv[3]);
    if (!out.is_open())
    {
      throw 4;
    }
    out << cnt << "\n";
  }
  catch (int code)
  {
    delete[] heap;
    if (code == 1)
    {
      std::cerr << "Error: wrong arguments\n";
    }
    else if (code == 3)
    {
      std::cerr << "Error: cannot open input file\n";
    }
    else if (code == 4)
    {
      std::cerr << "Error: cannot open output file\n";
    }
    else if (code == 2)
    {
      std::cerr << "Error: the file does not contain a correct matrix\n";
    }
    return code;
  }
}

namespace anikina
{
  int countlocalmax(const int* a, int rows, int cols)
  {
    int cnt = 0;
    for (int i = 1; i + 1 < rows; ++i)
    {
      for (int j = 1; j + 1 < cols; ++j)
      {
        bool islocalmax = true;
        for (int di = -1; di <= 1; ++di)
        {
          for (int dj = -1; dj <= 1; ++dj)
          {
            if ((di || dj) && a[(i + di) * cols + j + dj] >= a[i * cols + j])
            {
              islocalmax = false;
            }
          }
        }
        if (islocalmax)
        {
          ++cnt;
        }
      }
    }
    return cnt;
  }
}

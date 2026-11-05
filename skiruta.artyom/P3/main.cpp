#include <fstream>
#include <iostream>
#include <new>
#include <stdexcept>
#include <cstring>

namespace skiruta
{
  void safeAllocMatrix(int **&m, int &w, int &h)
  {
    m = new int *[h]();
    for (int i = 0; i < h; i++)
    {
      m[i] = new int[w];
    }
  }

  void freeMatrix(int **&m, int &h)
  {
    if (m)
    {
      for (int i = 0; i < h; i++)
      {
        if (m[i])
        {
          delete[] m[i];
        }
      }
      delete[] m;
      m = nullptr;
    }
  }

  template< typename T >
  void readMatrix(std::ifstream &f, T &m, int &w, int &h)
  {
    for (int i = 0; i < h; i++)
    {
      for (int j = 0; j < w; j++)
      {
        f >> m[i][j];
        if (f.fail())
        {
          throw std::bad_alloc();
        }
      }
    }
  }

  template< typename T >
  void incrMatrix(T &m, int &w, int &h)
  {
    int top = 0, bottom = h - 1, left = 0, right = w - 1;
    int inc = 1;
    while (top <= bottom && left <= right)
    {
      for (int i = top; i <= bottom; i++)
      {
        m[i][left] += inc++;
      }
      left++;
      for (int j = left; j <= right; j++)
      {
        m[bottom][j] += inc++;
      }
      bottom--;
      if (left <= right)
      {
        for (int i = bottom; i >= top; i--)
        {
          m[i][right] += inc++;
        }
      }
      right--;
      if (top <= bottom)
      {
        for (int j = right; j >= left; j--)
        {
          m[top][j] += inc++;
        }
      }
      top++;
    }
  }

  template< typename T >
  void transMatrixToFile(std::ofstream &f, T m, int &w, int &h)
  {
    f << w << " " << h;
    for (int i = 0; i < h; i++)
    {
      for (int j = 0; j < w; j++)
      {
        f << " " << m[i][j];
      }
    }
    f << "\n";
  }
}

int main(int argc, char *argv[])
{
  int **matrix = nullptr;
  int width = 0, height = 0;
  try
  {
    if (argc != 4)
    {
      throw std::runtime_error("Wrong amount of arguments, must be 3");
    }
    std::ifstream file(argv[2]);
    std::ofstream out(argv[3]);
    if (!file.is_open() || !out.is_open())
    {
      throw std::bad_alloc();
    }
    const char *const mode = argv[1];
    if (strcmp(mode, "2") && strcmp(mode, "1"))
    {
      throw std::runtime_error("Wrong first argument (1 or 2 expected)");
    }
    file >> height >> width;
    if (file.fail() || height < 0 || width < 0)
    {
      throw std::bad_alloc();
    }
    if (!strcmp(mode, "1"))
    {
      const int hMax = 100, wMax = 100;
      int fm[hMax][wMax];
      skiruta::readMatrix(file, fm, width, height);
      skiruta::incrMatrix(fm, width, height);
      skiruta::transMatrixToFile(out, fm, width, height);
    }
    else
    {
      skiruta::safeAllocMatrix(matrix, width, height);
      skiruta::readMatrix(file, matrix, width, height);
      skiruta::incrMatrix(matrix, width, height);
      skiruta::transMatrixToFile(out, matrix, width, height);
    }
  }
  catch (const std::runtime_error &e)
  {
    std::cerr << e.what() << "\n";
    skiruta::freeMatrix(matrix, height);
    return 1;
  }
  catch (const std::bad_alloc &)
  {
    std::cerr << "Error with memory, matrix or opening file\n";
    skiruta::freeMatrix(matrix, height);
    return 2;
  }
  skiruta::freeMatrix(matrix, height);
  return 0;
}

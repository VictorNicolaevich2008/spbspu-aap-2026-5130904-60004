#include <fstream>
#include <iostream>

const int MAX_LENGTH = 10000;

namespace ganev
{
  void lftTopCkl(int* m, size_t rows, size_t cols);
  void lftTopCkl(int** m, size_t rows, size_t cols);
  void outputMatrix(int* m, size_t rows, size_t cols, char* file);
  void outputMatrix(int** m, size_t rows, size_t cols, char* file);
}
int main(int argc, char* argv[])
{
  if (argc != 4 || (*argv[1] != '1' && *argv[1] != '2') || argv[1][1])
  {
    std::cout << "Invalid argument\n";
    return 1;
  }
  int n = 0, m = 0;

  std::fstream in(argv[2]);
  if (!in || !(in >> n >> m))
  {
    std::cout << "Input error";
    return 2;
  }

  if (n < 0 || m < 0)
  {
    std::cout << "Input error";
    return 2;
  }

  if (*argv[1] == '1')
  {
    int matrix[MAX_LENGTH] = {};
    if (n * m > MAX_LENGTH)
    {
      std::cout << "Input error";
      return 2;
    }
    for (int i = 0; i < n * m; i++)
    {
      if (!(in >> matrix[i]))
      {
        std::cout << "Input error";
        return 2;
      }
    }
    ganev::lftTopCkl(matrix, n, m);
    ganev::outputMatrix(matrix, n, m, argv[3]);
  }
  else if (*argv[1] == '2')
  {
    try
    {
      int** const matrix = new int*[n];
      for (int i = 0; i < n; i++)
      {
        matrix[i] = new int[m];
      }
      for (int i = 0; i < n; i++)
      {
        for (int j = 0; j < m; j++)
        {
          if (!(in >> matrix[i][j]))
          {
            std::cout << "Input error";
            for (int i = 0; i < n; i++)
            {
              delete[] matrix[i];
            }
            delete[] matrix;
            return 2;
          }
        }
      }
      ganev::lftTopCkl(matrix, n, m);
      ganev::outputMatrix(matrix, n, m, argv[3]);
      for (int i = 0; i < n; i++)
      {
        delete[] matrix[i];
      }
      delete[] matrix;
    }
    catch (const std::bad_alloc& e)
    {
      std::cerr << e.what() << '\n';
    }
  }

  in.close();
  return 0;
}

namespace ganev
{
  void lftTopCkl(int* m, size_t rows, size_t cols)
  {
    int count = 1;
    int t = 0, b = rows - 1, l = 0, r = cols - 1;
    while (t <= b && l <= r)
    {
      for (int i = l; i <= r; i++)
      {
        m[t * cols + i] -= count;
        count++;
      }
      t++;
      for (int j = t; j <= b; j++)
      {
        m[j * cols + r] -= count;
        count++;
      }
      r--;
      if (t > b)
      {
        break;
      }
      for (int i = r; i >= l; i--)
      {
        m[b * cols + i] -= count;
        count++;
      }
      if (l > r)
      {
        break;
      }
      b--;
      for (int j = b; j >= t; j--)
      {
        m[j * cols + l] -= count;
        count++;
      }
      l++;
    }
  }

  void lftTopCkl(int** m, size_t rows, size_t cols)
  {
    int count = 1;
    int t = 0, b = rows - 1, l = 0, r = cols - 1;
    while (t <= b && l <= r)
    {
      for (int i = l; i <= r; i++)
      {
        m[t][i] -= count;
        count++;
      }
      t++;
      for (int j = t; j <= b; j++)
      {
        m[j][r] -= count;
        count++;
      }
      r--;
      if (t > b)
      {
        break;
      }
      for (int i = r; i >= l; i--)
      {
        m[b][i] -= count;
        count++;
      }
      if (l > r)
      {
        break;
      }
      b--;
      for (int j = b; j >= t; j--)
      {
        m[j][l] -= count;
        count++;
      }
      l++;
    }
  }
  void outputMatrix(int* m, size_t rows, size_t cols, char* file)
  {
    std::ofstream out(file);
    out << rows << " " << cols << "\n";
    for (size_t i = 0; i < rows; i++)
    {
      for (size_t j = 0; j < cols; j++)
      {
        out << m[i * rows + j] << " ";
      }
      out << "\n";
    }
    out.close();
  }

  void outputMatrix(int** m, size_t rows, size_t cols, char* file)
  {
    std::ofstream out(file);
    out << rows << " " << cols << "\n";
    for (size_t i = 0; i < rows; i++)
    {
      for (size_t j = 0; j < cols; j++)
      {
        out << m[i][j] << " ";
      }
      out << "\n";
    }
    out.close();
  }
}

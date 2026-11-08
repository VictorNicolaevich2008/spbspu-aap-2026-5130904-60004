#include <iostream>
namespace zabrodotsky
{
  int solve();
}
int main()
{
  const int res = zabrodotsky::solve();
  if (res < 0)
  {
    return -res;
  }
  std::cout << res << "\n";
  return 0;
}
namespace zabrodotsky
{
  int solve()
  {
    long long prev = 0;
    long long curr = 0;
    int count = 0;
    if (!(std::cin >> prev) || prev == 0)
    {
      return prev == 0 ? -2 : -1;
    }
    while (std::cin >> curr && curr != 0)
    {
      if ((prev < 0 && curr > 0) || (prev > 0 && curr < 0))
      {
        count++;
      }
      prev = curr;
    }
    if (!std::cin.eof() && std::cin.fail())
    {
      return -1;
    }
    return count;
  }
}

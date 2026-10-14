#include <iostream>
#include <stdexcept>
namespace kibirev
{
  int pifTrip();
}

int main()
{
  try
  {
    const int ans = kibirev::pifTrip();
    std::cout << ans << "\n";
  }
  catch (const std::invalid_argument& e)
  {
    std::cerr << e.what() << "\n";
    return 1;
  }
}
namespace kibirev
{
  int pifTrip()
  {
    int num = 0;
    int piftr = 0;
    int cntr = 0;
    bool bad = false;
    long long sum = 0;
    if (!(std::cin >> num))
    {
      throw std::invalid_argument("Not a number of int\n");
    }
    if (num == 0)
    {
      std::cerr << "Не полная последовательность\n";
      return 2;
    }
    while (num != 0)
    {
      if (cntr < 2)
      {
        if (num > 0)
        {
          const long long n = num;
          sum += n * n;
        }
        else
        {
          bad = true;
        }
        cntr++;
      }
      else
      {
        if (!bad && num > 0 && sum == num * num)
        {
          piftr++;
        }
        cntr = 0;
        sum = 0;
        bad = false;
      }
      if (!(std::cin >> num))
      {
        throw std::invalid_argument("Not a number of int\n");
      }
    }
    if (cntr != 0)
    {
      std::cerr << "Не полная последовательность.\n";
      return 2;
    }
    return piftr;
  }
}

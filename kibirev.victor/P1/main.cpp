#include <iostream>
#include <stdexcept>
#include <cstddef>
 
namespace kibirev
{
  struct Piftr
  {
    Piftr() {};
    void operator()(int value);
    int operator()() const;
    size_t getCounter() const;
  private:
    long long sum = 0;
    int piftr = 0;
    long long num = 0;
    size_t counter = 0;
    bool flag = true;
  };
}
 
int main()
{
  using kibirev::Piftr;
  try
  {
    Piftr cnt;
    int value = 0;
    if (!(std::cin >> value))
    {
      throw std::invalid_argument("Not a number\n");
    }
    while (value != 0)
    {
      cnt(value);
      if (!(std::cin >> value))
      {
        throw std::invalid_argument("Not a number\n");
      }
    }
    if (cnt.getCounter() == 0)
    {
      std::cout << cnt();
    }
    else
    {
      throw std::logic_error("Not enough elements\n");
    }
  }
  catch (const std::invalid_argument& e)
  {
    std::cerr << e.what() << '\n';
    return 1;
  }
  catch (const std::logic_error& e)
  {
    std::cerr << e.what() << '\n';
    return 2;
  }
}
 
void kibirev::Piftr::operator()(int value)
{
  if (counter < 2)
  {
    if (value > 0)
    {
      num = value;
      sum += num * num;
    }
    else
    {
      flag = false;
    }
    counter++;
  }
  else
  {
    if (flag && value > 0)
    {
      num = value;
      if (sum == num * num)
      {
        piftr++;
      }
    }
    counter = 0;
    sum = 0;
    flag = true;
  }
}
 
int kibirev::Piftr::operator()() const
{
  return piftr;
}
 
size_t kibirev::Piftr::getCounter() const
{
  return counter;
}

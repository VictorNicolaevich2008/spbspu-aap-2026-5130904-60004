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
    long long sum_ = 0;
    int piftr_ = 0;
    long long num_ = 0;
    size_t counter_ = 0;
    bool flag_ = true;
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
  if (counter_ < 2)
  {
    if (value > 0)
    {
      num_ = value;
      sum_ += num_ * num_;
    }
    else
    {
      flag_ = false;
    }
    counter_++;
  }
  else
  {
    if (flag_ && value > 0)
    {
      num_ = value;
      if (sum_ == num_ * num_)
      {
        piftr_++;
      }
    }
    counter_ = 0;
    sum_ = 0;
    flag_ = true;
  }
}

int kibirev::Piftr::operator()() const
{
  return piftr_;
}

size_t kibirev::Piftr::getCounter() const
{
  return counter_;
}

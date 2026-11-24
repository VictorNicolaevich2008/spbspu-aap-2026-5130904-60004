#include <iostream>
#include <cstddef>
#include <limits>
#include <stdexcept>

namespace sierra
{
  struct AftMax
  {
    void operator()(int value);
    size_t operator()() const;
  private:
    int max_ = 0;
    size_t after_ = 0;
    bool empty_ = true;
    bool overflow_ = false;
  };
}

void sierra::AftMax::operator()(int value)
{
  if (empty_ || value > max_)
  {
    max_ = value;
    after_ = 0;
    empty_ = false;
    overflow_ = false;
  }
  else if (after_ == std::numeric_limits< size_t >::max())
  {
    overflow_ = true;
  }
  else
  {
    ++after_;
  }
}

size_t sierra::AftMax::operator()() const
{
  if (empty_)
  {
    throw std::logic_error("AFT-MAX: sequence is empty");
  }
  if (overflow_)
  {
    throw std::overflow_error("AFT-MAX: sequence is too long");
  }
  return after_;
}

int main()
{
  int value = 0;
  sierra::AftMax counter;
  while ((std::cin >> value) && value != 0)
  {
    counter(value);
  }
  if (!std::cin)
  {
    std::cerr << "Error: input is not a sequence\n";
    return 1;
  }
  try
  {
    std::cout << counter() << '\n';
  }
  catch (const std::exception & e)
  {
    std::cerr << e.what() << '\n';
    return 2;
  }
  return 0;
}

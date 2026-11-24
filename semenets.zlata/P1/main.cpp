#include <iostream>
#include <stdexcept>

namespace semenets
{
  struct CountSignChanges
  {
    CountSignChanges();
    void operator()(int value);
    size_t operator()() const;

  private:
    size_t count_;
    size_t count_num_;
    int znak_past_;
    int znak_new_;
  };
}

semenets::CountSignChanges::CountSignChanges():
  count_(0),
  count_num_(0),
  znak_past_(0),
  znak_new_(0)
{}

void semenets::CountSignChanges::operator()(int value)
{
  ++count_num_;
  if (value > 0)
  {
    znak_new_ = 1;
  }
  else
  {
    znak_new_ = -1;
  }
  if (count_num_ != 1 && znak_new_ != znak_past_)
  {
    ++count_;
  }
  znak_past_ = znak_new_;
}

size_t semenets::CountSignChanges::operator()() const
{
  return count_;
}

int main()
{
  try
  {
    semenets::CountSignChanges counter;
    while (true)
    {
      int value = 0;
      if (!(std::cin >> value))
      {
        throw std::invalid_argument("Not a number enter");
      }
      if (value == 0)
      {
        break;
      }
      counter(value);
    }
    std::cout << counter() << "\n";
    return 0;
  }
  catch (const std::invalid_argument& e)
  {
    std::cerr << e.what() << "\n";
    return 1;
  }
}

#include "Ring.hpp"
#include <iostream>
namespace kibirev
{
  static const double PI = 3.1415926;
  Ring::Ring(double r1, double r2, point_t c):
    Shape(c)
  {
    rad_in_ = (r1 < r2 ? r1 : r2);
    rad_out_ = (r1 > r2 ? r1 : r2);
    if (rad_in_ <= 0)
    {
      throw std::invalid_argument("Not a Ring\n");
    }
  }
  double Ring::getArea()
  {
    return PI * (rad_out_ * rad_out_ - rad_in_ * rad_in_);
  }
  rectangle_t Ring::getFrameRect()
  {
    rectangle_t ring_rect(center, 2 * rad_out_, 2 * rad_out_);
    return ring_rect;
  }
  void Ring::move(double x, double y)
  {
    center.x += x;
    center.y += y;
  }
  void Ring::move(point_t c_new)
  {
    center = c_new;
  }
  void Ring::scale(double k)
  {
    if (k <= 0)
    {
      throw std::invalid_argument("K is Null or lower than null");
    }
    rad_in_ *= k;
    rad_out_ *= k;
  }
}

#include "Rubber.hpp"
#include <iostream>
#include <cmath>
namespace kibirev
{
  static const double PI = 3.1415926;
  Rubber::Rubber(double r1, double r2, point_t c, point_t cout):
    Shape(c),
    rad_in_(r1 < r2 ? r1 : r2),
    rad_out_(r1 > r2 ? r1 : r2),
    c_out_(cout)
  {
    const double dx = c_out_.x - center.x;
    const double dy = c_out_.y - center.y;
    if (rad_out_ < rad_in_ + std::sqrt(dx * dx + dy * dy))
    {
      throw std::invalid_argument("Not a Rubber");
    }
  }
  double Rubber::getArea()
  {
    return PI * (rad_out_ * rad_out_ - rad_in_ * rad_in_);
  }
  rectangle_t Rubber::getFrameRect()
  {
    rectangle_t rubb_rect(c_out_, 2 * rad_out_, 2 * rad_out_);
    return rubb_rect;
  }
  void Rubber::move(double x, double y)
  {
    center.x += x;
    center.y += y;
    c_out_.x += x;
    c_out_.y += y;
  }
  void Rubber::move(point_t cn)
  {
    move(cn.x - center.x, cn.y - center.y);
  }
  void Rubber::scale(double k)
  {
    if (k <= 0)
    {
      throw std::invalid_argument("K is Null or lower than null");
    }
    c_out_.x = center.x + (c_out_.x - center.x) * k;
    c_out_.y = center.y + (c_out_.y - center.y) * k;
    rad_in_ *= k;
    rad_out_ *= k;
  }
}

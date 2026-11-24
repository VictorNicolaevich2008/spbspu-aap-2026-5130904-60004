#include "Rubber.hpp"
#include <iostream>
static const double PI = 3.1415926;
Rubber::Rubber(double r1, double r2, point_t c, point_t cout):
  Shape(c),
  rad_in_(r1 < r2 ? r1 : r2),
  rad_out_(r1 > r2 ? r1 : r2),
  c_out_(cout)
{
  if (rad_out_ < rad_in_
          + std::sqrt((c_out_.x_ - center_.x_) * (c_out_.x_ - center_.x_)
              + (c_out_.y_ - center_.y_) * (c_out_.y_ - center_.y_)))
  {
    throw std::invalid_argument("Not a Rubber\n");
  }
}
double Rubber::getArea()
{
  return PI * (rad_out_ * rad_out_ - rad_in_ * rad_in_);
}
void Rubber::getFrameRect()
{
  rectangle_t frRec;
  frRec.pos_ = center_;
  frRec.width_ = frRec.height_ = 2 * rad_out_;
  std::cout << "FrameRect: " << frRec.pos_.x_ << "," << frRec.pos_.y_ << " " << frRec.width_ << " " << frRec.height_
            << '\n';
}
void Rubber::move(double x, double y)
{
  center_.x_ += x;
  center_.y_ += y;
}
void Rubber::move(point_t cn)
{
  center_ = cn;
}
void Rubber::scale(double k)
{
  if (k <= 0)
  {
    throw std::invalid_argument("K is Null or lower than null");
  }
  rad_in_ *= k;
  rad_out_ *= k;
}

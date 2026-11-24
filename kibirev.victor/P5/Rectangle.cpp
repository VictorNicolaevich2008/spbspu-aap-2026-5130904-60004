#include <iostream>
#include "Rectangle.hpp"
Rectangle::Rectangle(double w, double h, point_t c):
  Shape(c),
  width_(w),
  height_(h)
{}
double Rectangle::getArea()
{
  return width_ * height_;
}
void Rectangle::getFrameRect()
{
  std::cout << "FrameRect: " << center_.x_ << "," << center_.y_ << " " << width_ << " " << height_ << '\n';
}
void Rectangle::move(double x, double y)
{
  center_.x_ += x;
  center_.y_ += y;
}
void Rectangle::move(point_t cent_2)
{
  center_ = cent_2;
}
void Rectangle::scale(double k)
{
  if (k <= 0)
  {
    throw std::invalid_argument("K is Null or lower than null");
  }
  width_ *= k;
  height_ *= k;
}

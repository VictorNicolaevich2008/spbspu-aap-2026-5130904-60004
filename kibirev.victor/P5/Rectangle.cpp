#include <iostream>
#include "Rectangle.hpp"
namespace kibirev
{
  Rectangle::Rectangle(double w, double h, point_t c):
    Shape(c),
    width_(w),
    height_(h)
  {}
  double Rectangle::getArea()
  {
    return width_ * height_;
  }
  rectangle_t Rectangle::getFrameRect()
  {
    rectangle_t frame_rect(center, width_, height_);
    return frame_rect;
  }
  void Rectangle::move(double x, double y)
  {
    center.x += x;
    center.y += y;
  }
  void Rectangle::move(point_t cent_2)
  {
    center = cent_2;
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
}

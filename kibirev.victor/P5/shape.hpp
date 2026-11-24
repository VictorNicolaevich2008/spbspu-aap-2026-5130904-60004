#pragma once
#include "base_type.hpp"
class Shape
{
public:
  Shape(point_t cen):
    center_(cen) {};
  virtual double getArea() = 0;
  virtual void getFrameRect() = 0;
  virtual void move(double, double) = 0;
  virtual void move(point_t) = 0;
  virtual void scale(double) = 0;
  virtual ~Shape() = default;
  friend void isotrop_point(Shape** shapes, point_t p, double k, int len);

  point_t center_;
};

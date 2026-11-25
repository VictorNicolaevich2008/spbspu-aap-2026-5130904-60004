#ifndef SHAPE_HPP
#define SHAPE_HPP
#include "base_type.hpp"
namespace kibirev
{
  class Shape;
  void isotropPoint(Shape** shapes, point_t p, double k, size_t len);
  class Shape
  {
  public:
    Shape(point_t cen):
      center(cen) {};
    virtual double getArea() = 0;
    virtual rectangle_t getFrameRect() = 0;
    virtual void move(double, double) = 0;
    virtual void move(point_t) = 0;
    virtual void scale(double) = 0;
    virtual ~Shape() = default;
    friend void isotropPoint(Shape** shapes, point_t p, double k, size_t len);

    point_t center = {0, 0};
  };
}
#endif

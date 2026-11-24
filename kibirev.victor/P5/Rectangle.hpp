#pragma once
#include "shape.hpp"
class Rectangle: public Shape
{
private:
  double width_, height_;
public:
  Rectangle(double, double, point_t);
  double getArea() override;
  void getFrameRect() override;
  void move(double x, double y) override;
  void move(point_t cent_2) override;
  void scale(double k) override;
};

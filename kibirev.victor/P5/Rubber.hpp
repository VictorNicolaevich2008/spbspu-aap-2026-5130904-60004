#pragma once
#include "shape.hpp"

class Rubber: public Shape
{
private:
  double rad_in_, rad_out_;
  point_t c_out_;
public:
  Rubber(double r1, double r2, point_t c, point_t cout);
  double getArea() override;
  void getFrameRect() override;
  void move(double x, double y) override;
  void move(point_t cn) override;
  void scale(double k) override;
};

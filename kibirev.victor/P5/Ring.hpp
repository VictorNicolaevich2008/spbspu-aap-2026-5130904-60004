#ifndef RING_HPP
#define RING_HPP
#include "shape.hpp"
namespace kibirev
{
  class Ring: public Shape
  {
  private:
    double rad_in_, rad_out_;
  public:
    Ring(double r1, double r2, point_t c);
    double getArea() override;
    rectangle_t getFrameRect() override;
    void move(double x, double y) override;
    void move(point_t c_new) override;
    void scale(double k) override;
  };
}
#endif

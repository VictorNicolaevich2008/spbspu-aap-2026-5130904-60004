#pragma once
#include "shape.hpp"

class Ring : public Shape
{
private:
    double rad_in_, rad_out_;
public:
    Ring(double r1, double r2, point_t c);
    double getArea() override;
    void getFrameRect() override;
    void move(double x, double y) override;
    void move(point_t c_new) override;
    void scale(double k) override;
};

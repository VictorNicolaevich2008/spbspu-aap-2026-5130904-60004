#include "Ring.hpp"
#include <iostream>
static const double PI =3.1415926; 
Ring::Ring(double r1, double r2, point_t c): Shape(c)
{
    rad_in_ = (r1 < r2?r1:r2);
    rad_out_ = (r1 > r2?r1:r2);
}
double Ring::getArea()
{
    return PI * (rad_out_ * rad_out_ - rad_in_ * rad_in_);
}
void Ring::getFrameRect()
{
    rectangle_t frRec;
    frRec.pos_ = center_;
    frRec.width_ = frRec.height_ = 2 * rad_out_;
    std::cout << "FrameRect: " << frRec.pos_.x_ << "," << frRec.pos_.y_ << " " << frRec.width_ << " " << frRec.height_ << '\n';
}
void Ring::move(double x, double y)
{
    center_.x_ += x;
    center_.y_ += y;
}
void Ring::move(point_t c_new)
{
    center_ = c_new;
}
void Ring::scale(double k)
{
    if (k <= 0)
    {
        throw std::invalid_argument("K is Null or lower than null");
    }
    rad_in_ *= k;
    rad_out_ *= k;
}

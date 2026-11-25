#ifndef BASE_TYPE_HPP
#define BASE_TYPE_HPP
#include <iostream>
namespace kibirev
{
  struct point_t
  {
    double x, y;
    friend std::istream& operator>>(std::istream& input, point_t& p)
    {
      input >> p.x >> p.y;
      return input;
    }
    friend std::ostream& operator<<(std::ostream& out, point_t& el)
    {
      out << el.x << " " << el.y << "\n";
      return out;
    }
  };
  struct rectangle_t
  {
    rectangle_t(point_t po, double widt, double heigh):
      width(widt),
      height(heigh),
      pos(po)
    {}
    double width, height;
    point_t pos;
    friend std::ostream& operator<<(std::ostream& out, rectangle_t& el)
    {
      out << el.pos << " " << el.width << " " << el.height << "\n";
      return out;
    }
  };
}
#endif

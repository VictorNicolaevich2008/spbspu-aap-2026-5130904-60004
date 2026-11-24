#pragma once
#include <iostream>
struct point_t{
  double x_,y_;
  friend std::istream& operator>>(std::istream& input, point_t& p){
    input >> p.x_ >> p.y_;
    return input;
  }
};
struct rectangle_t{
  double width_, height_;
  point_t pos_;
};

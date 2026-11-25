#include "shape.hpp"
#include <iostream>
#include <cmath>
#include "Rectangle.hpp"
#include "Ring.hpp"
#include "Rubber.hpp"
#include <algorithm>
namespace kibirev
{
  rectangle_t getTotalFrame(Shape** shapes, size_t len);
  void isotropPoint(Shape** shapes, point_t p, double k, size_t len);
  void sumArea(Shape** shapes, size_t len);
  void getInfo(Shape** shapes, size_t len);
}
using namespace kibirev;
int main()
{
  const double rw = 4.0;
  const double rh = 2.0;
  const point_t rc = {3.0, 2.0};
  const double rin = 3.0;
  const double rout = 1.0;
  const point_t ric = {-4.0, 2.0};
  const double ur1 = 1.0;
  const double ur2 = 4.0;
  const point_t uc1 = {2.0, -3.0};
  const point_t uc2 = {5.0, -3.0};
  const size_t n = 3;
  Shape * shapes[n] = {nullptr, nullptr, nullptr};
  try
  {
    shapes[0] = new Rectangle(rw, rh, rc);
    shapes[1] = new Ring(rin, rout, ric);
    shapes[2] = new Rubber(ur1, ur2, uc1, uc2);
    getInfo(shapes, n);
    point_t pp = {0.0, 0.0};
    std::cout << "Enter point for Isotrop_scale by point.\n";
    if (!(std::cin >> pp))
    {
      throw std::invalid_argument("Not numbers\n");
    }
    double k = 0.0;
    std::cout << "Enter k for scale.\n";
    if (!(std::cin >> k))
    {
      throw std::invalid_argument("Not a number.\n");
    }
    isotropPoint(shapes, pp, k, n);
    getInfo(shapes, n);
    for (size_t i = 0; i < n; i++)
    {
      delete shapes[i];
    }
    return 0;
  }
  catch (const std::invalid_argument& e)
  {
    std::cerr << e.what() << '\n';
    for (size_t i = 0; i < n; i++)
    {
      delete shapes[i];
    }
    return 1;
  }
}

void kibirev::isotropPoint(Shape** shapes, point_t p, double k, size_t len)
{
  const double x = p.x;
  const double y = p.y;
  for (size_t i = 0; i < len; i++)
  {
    const double x0 = shapes[i]->center.x;
    const double y0 = shapes[i]->center.y;
    shapes[i]->move({(x0 + (x0 - x) * (k - 1)), (y0 + (y0 - y) * (k - 1))});
    shapes[i]->scale(k);
  }
}
void kibirev::sumArea(Shape** shapes, size_t len)
{
  double area = 0.0;
  for (size_t i = 0; i < len; i++)
  {
    area += shapes[i]->getArea();
  }
  std::cout << area << '\n';
}
rectangle_t kibirev::getTotalFrame(Shape** shapes, size_t len)
{
  rectangle_t r = shapes[0]->getFrameRect();
  double min_x = r.pos.x - r.width / 2;
  double max_x = r.pos.x + r.width / 2;
  double min_y = r.pos.y - r.height / 2;
  double max_y = r.pos.y + r.height / 2;

  for (size_t i = 1; i < len; i++)
  {
    r = shapes[i]->getFrameRect();
    min_x = std::min(min_x, r.pos.x - r.width / 2);
    max_x = std::max(max_x, r.pos.x + r.width / 2);
    min_y = std::min(min_y, r.pos.y - r.height / 2);
    max_y = std::max(max_y, r.pos.y + r.height / 2);
 }
  return {{(min_x + max_x) / 2, (min_y + max_y) / 2}, max_x - min_x, max_y - min_y};
}
void kibirev::getInfo(Shape** shapes, size_t len)
{
  for (size_t i = 0; i < len; i++)
  {
    std::cout << shapes[i]->getArea() << '\n';
  }
  sumArea(shapes, 3);
  for (size_t i = 0; i < len; i++)
  {
    const rectangle_t frame = shapes[i]->getFrameRect();
    std::cout << "(" << frame.pos.x << ", " << frame.pos.y << ") " << frame.width << " " << frame.height << '\n';
  }
  const rectangle_t total_frame = getTotalFrame(shapes, 3);
  std::cout << "(" << total_frame.pos.x << ", " << total_frame.pos.y << ") " << total_frame.width << " "
            << total_frame.height << '\n';
}

#include "shape.hpp"
#include <iostream>
#include <cmath>
#include "Rectangle.hpp"
#include "Ring.hpp"
#include "Rubber.hpp"
namespace kibirev
{
    void isotrop_point(Shape** shapes, point_t p, double k, int len);
}
int main()
{   
    Shape * shapes[3];
    try{
        double k;
        std::cout << "Enter k for scale.\n";
        if (!(std::cin >> k)){
            throw std::invalid_argument("Not a number.\n");
        }
        point_t pp;
        std::cout << "Enter point for Isotrop_scale by point.\n";
        if (!(std::cin >> pp)){
            throw std::invalid_argument("Not numbers\n");
        }
        shapes[0] = new Rectangle(1.5, 2, {3,2});
        shapes[1] = new Ring(3, 1, {2,3});
        shapes[2] = new Rubber(2, 5, {2,2}, {3,3});
        for (size_t i = 0; i < 3; i++)
        {
            shapes[i]->getFrameRect();
        }
        isotrop_point(shapes, pp, k, 3);
        for (size_t i = 0; i < 3; i++)
        {
            shapes[i]->getFrameRect();
        }
        for (size_t i = 0; i < 3; i++)
        {
            delete shapes[i];
        }
        return 0;
        
    } catch(const std::invalid_argument& e)
    {
        std::cerr << e.what() << '\n';
        for (size_t i = 0; i < 3; i++)
        {
            delete shapes[i];
        }
        return 1;
    }
}

void kibirev::isotrop_point(Shape** shapes, point_t p, double k, int len)
{
    double x = p.x_;
    double y = p.y_;
    for (size_t i = 0; i < len; i ++){
        double x0 = shapes[i]->center_.x_;
        double y0 = shapes[i]->center_.y_;
        shapes[i]->move({(x0 + (x0 - x) * (k - 1)), (y0 + (y0 - y) * (k - 1))});
        shapes[i]->scale(k);
    }
}

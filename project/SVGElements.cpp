#include "SVGElements.hpp"

namespace svg
{
    // These must be defined!
    SVGElement::SVGElement() {}
    SVGElement::~SVGElement() {}

    // Ellipse (initial code provided)
    Ellipse::Ellipse(const Color &fill,
                     const Point &center,
                     const Point &radius)
        : fill(fill), center(center), radius(radius)
    {
    }
    void Ellipse::draw(PNGImage &img) const
    {
        img.draw_ellipse(center, radius, fill);
    }
    // @todo provide the implementation of SVGElement derived classes
    // HERE -->
    Circle::Circle(const Color &fill,
                     const Point &center,
                     const int &radius)
        : fill(fill), center(center), radius(radius)
    {
    }
    void Circle::draw(PNGImage &img) const
    {
        Point radiusPoint;
        radiusPoint.x = radius;
        radiusPoint.y = radius;

        img.draw_ellipse(center, radiusPoint, fill);
    }

    Line::Line(const Color &stroke,
                     const Point &start,
                     const Point &end)
        : stroke(stroke), start(start), end(end)
    {
    }
    void Line::draw(PNGImage &img) const
    {
        img.draw_line(start, end, stroke);
    }


}

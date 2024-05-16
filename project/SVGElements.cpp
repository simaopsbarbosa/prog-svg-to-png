#include "SVGElements.hpp"

namespace svg
{
    // These must be defined!
    SVGElement::SVGElement() {}
    SVGElement::~SVGElement() {}

    // Ellipse
    Ellipse::Ellipse(const Color &fill,
                     const Point &center,
                     const Point &radius,
                     const Point transform_origin)
        : fill(fill), center(center), radius(radius), transform_origin(transform_origin)
    {
    }
    void Ellipse::draw(PNGImage &img) const
    {
        img.draw_ellipse(center, radius, fill);
    }
    void Ellipse::translate(int x, int y) {
        center = center.translate({x,y});
    }
    void Ellipse::rotate(int v) {
        center = center.rotate(transform_origin, v);
    }
    void Ellipse::scale(int v) {
        radius = radius.scale({0,0}, v);
        center = center.scale(transform_origin, v);
    }

    // Line
    Line::Line(const Color &stroke,
                     const Point &start,
                     const Point &end,
                     const Point transform_origin)
        : stroke(stroke), start(start), end(end), transform_origin(transform_origin)
    {
    }
    void Line::draw(PNGImage &img) const
    {
        img.draw_line(start, end, stroke);
    }
    void Line::translate(int x, int y) {
        start = start.translate({x,y});
        end = end.translate({x,y});
    }
    void Line::rotate(int v) {
        start = start.rotate(transform_origin, v);
        end = end.rotate(transform_origin, v);
    }
    void Line::scale(int v) {
        start = start.scale(transform_origin, v);
        end = end.scale(transform_origin, v);
    }

    // Polygon
    Polygon::Polygon(const std::vector<Point> &points, 
                     const Color &fill,
                     const Point transform_origin)
        : points(points), fill(fill), transform_origin(transform_origin)
    {
    }
    void Polygon::draw(PNGImage &img) const
    {
        img.draw_polygon(points, fill);
    }
    void Polygon::translate(int x, int y) {
        for (Point& p : this->points) {
            p = p.translate({x,y});
        }
    }
    void Polygon::rotate(int v) {
        for (Point& p : this->points) {
            p = p.rotate(transform_origin, v);
        }
    }
    void Polygon::scale(int v) {
        for (Point& p : this->points) {
            p = p.scale(transform_origin, v);
        }
    }

}

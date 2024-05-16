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
    SVGElement *Ellipse::clone(const Point transform_origin) const
    {
        return new Ellipse(this->fill, this->center, this->radius, transform_origin);
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
    SVGElement *Line::clone(const Point transform_origin) const
    {
        return new Line(this->stroke, this->start, this->end, transform_origin);
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
    SVGElement *Polygon::clone(const Point transform_origin) const
    {
        return new Polygon(this->points, this->fill, transform_origin);
    }

    // Group
    Group::Group(const std::vector<SVGElement*> &elements, 
                const Point transform_origin)
        : elements(elements), transform_origin(transform_origin)
    {
    }
    void Group::draw(PNGImage &img) const
    {
        for (SVGElement* elem : elements) {
            elem->draw(img);
            delete elem;
        }
    }
    void Group::translate(int x, int y) {
        for (SVGElement* elem : elements) {
            elem->translate(x,y);
        }
    }
    void Group::rotate(int v) {
        for (SVGElement* elem : elements) {
            elem->rotate(v);
        }
    }
    void Group::scale(int v) {
        for (SVGElement* elem : elements) {
            elem->scale(v);
        }
    }
    SVGElement *Group::clone(const Point transform_origin) const
    {
        return new Group(this->elements, transform_origin);
    }

    // Use
    Use::Use(const std::map<std::string,SVGElement*> &elements_with_id,  
             const std::string &href,
             const Point transform_origin)
        : elements_with_id(elements_with_id), href(href), transform_origin(transform_origin)
    {
    }
    void Use::draw(PNGImage &img) const
    {

    }
    void Use::translate(int x, int y) {
        elements_with_id.at(href)->translate(x,y);
    }
    void Use::rotate(int v) {
        elements_with_id.at(href)->rotate(v);
    }
    void Use::scale(int v) {
        elements_with_id.at(href)->scale(v);
    }
    SVGElement *Use::clone(const Point transform_origin) const
    {
        return new Use(this->elements_with_id, this->href, transform_origin);
    }
}

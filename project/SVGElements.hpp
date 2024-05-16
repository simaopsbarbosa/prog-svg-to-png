//! @file shape.hpp
#ifndef __svg_SVGElements_hpp__
#define __svg_SVGElements_hpp__

#include "Color.hpp"
#include "Point.hpp"
#include "PNGImage.hpp"
#include "iostream" // DELETE ME LATEr

namespace svg
{
    class SVGElement
    {

    public:
        SVGElement();
        virtual ~SVGElement();
        virtual void draw(PNGImage &img) const = 0;
        virtual void translate(int x, int y) = 0;
        virtual void rotate(int v) = 0;
        virtual void scale(int v) = 0;
    };

    // Declaration of namespace functions
    // readSVG -> implement it in readSVG.cpp
    // convert -> already given (DO NOT CHANGE) in convert.cpp

    void readSVG(const std::string &svg_file,
                 Point &dimensions,
                 std::vector<SVGElement *> &svg_elements);
    void convert(const std::string &svg_file,
                 const std::string &png_file);

    class Ellipse : public SVGElement
    {
    public:
        Ellipse(const Color &fill, 
                const Point &center, 
                const Point &radius, 
                const Point transform_origin);
        void draw(PNGImage &img) const override;
        void translate(int x, int y) override;
        void rotate(int v) override;
        void scale(int v) override;

    private:
        Color fill;
        Point center;
        Point radius;
        Point transform_origin;
    };

    class Line : public SVGElement
    {
    public:
        Line(const Color &stroke,  
            const Point &start, 
            const Point &end, 
            const Point transform_origin);
        void draw(PNGImage &img) const override;
        void translate(int x, int y) override;
        void rotate(int v) override;
        void scale(int v) override;

    private:
        Color stroke;
        Point start;
        Point end;
        Point transform_origin;
    };

    class Polygon : public SVGElement
    {
    public:
        Polygon(const std::vector<Point> &points, 
                const Color &fill, 
                const Point transform_origin);
        void draw(PNGImage &img) const override;
        void translate(int x, int y) override;
        void rotate(int v) override;
        void scale(int v) override;

    private:
        std::vector<Point> points;
        Color fill;
        Point transform_origin;
    };
}
#endif

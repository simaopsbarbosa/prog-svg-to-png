//! @file shape.hpp
#ifndef __svg_SVGElements_hpp__
#define __svg_SVGElements_hpp__

#include "Color.hpp"
#include "Point.hpp"
#include "PNGImage.hpp"
#include <map>
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
        virtual SVGElement* clone(const Point transform_origin) const = 0;
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
        SVGElement* clone(const Point transform_origin) const override;

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
        SVGElement* clone(const Point transform_origin) const override;

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
        SVGElement* clone(const Point transform_origin) const override;

    private:
        std::vector<Point> points;
        Color fill;
        Point transform_origin;
    };

    class Group : public SVGElement
    {
    public:
        Group(const std::vector<SVGElement*> &elements,  
                const Point transform_origin);
        void draw(PNGImage &img) const override;
        void translate(int x, int y) override;
        void rotate(int v) override;
        void scale(int v) override;
        SVGElement* clone(const Point transform_origin) const override;

    private:
        std::vector<SVGElement*> elements;
        Point transform_origin;
    };

    class Use : public SVGElement
    {
    public:
        Use(const std::map<std::string,SVGElement*> &elements_with_id,  
            const std::string &href,
            const Point transform_origin);
        void draw(PNGImage &img) const override;
        void translate(int x, int y) override;
        void rotate(int v) override;
        void scale(int v) override;
        SVGElement* clone(const Point transform_origin) const override;

    private:
        std::map<std::string,SVGElement*> elements_with_id;
        std::string href;
        Point transform_origin;
    };
}
#endif
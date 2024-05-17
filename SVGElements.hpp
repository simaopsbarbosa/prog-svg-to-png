//! @file shape.hpp
#ifndef __svg_SVGElements_hpp__
#define __svg_SVGElements_hpp__

#include "Color.hpp"
#include "Point.hpp"
#include "PNGImage.hpp"
#include <map>

namespace svg
{
    //! Base class for SVG elements.
    class SVGElement
    {
    public:
        //! Default constructor for SVGElement.
        SVGElement();

        //! Virtual destructor for SVGElement.
        virtual ~SVGElement();

        //! Draws the SVG element on a PNGImage.
        //! @param img The PNGImage object to draw on.
        virtual void draw(PNGImage &img) const = 0;

        //! Translates the SVG element by the given x and y values.
        //! @param x The x-coordinate translation.
        //! @param y The y-coordinate translation.
        virtual void translate(int x, int y) = 0;

        //! Rotates the SVG element by the given angle.
        //! @param v The angle to rotate the element.
        virtual void rotate(int v) = 0;

        //! Scales the SVG element by the given factor.
        //! @param v The scaling factor.
        virtual void scale(int v) = 0;

        //! Clones the SVG element with a new transform origin.
        //! @param transform_origin The new transform origin.
        //! @return A pointer to the cloned SVGElement.
        virtual SVGElement *clone(const Point transform_origin) const = 0;
    };

    //! Reads an SVG file and extracts its elements.
    //! @param svg_file The path to the SVG file.
    //! @param dimensions The dimensions of the SVG canvas.
    //! @param svg_elements A vector to store the extracted SVG elements.
    void readSVG(const std::string &svg_file,
                 Point &dimensions,
                 std::vector<SVGElement *> &svg_elements);

    //! Converts an SVG file to a PNG file.
    //! @param svg_file The path to the SVG file.
    //! @param png_file The path to the output PNG file.
    void convert(const std::string &svg_file,
                 const std::string &png_file);

    //! Class representing an ellipse SVG element.
    class Ellipse : public SVGElement
    {
    public:
        //! Constructs an Ellipse object.
        //! @param fill The fill color of the ellipse.
        //! @param center The center point of the ellipse.
        //! @param radius The radius of the ellipse.
        //! @param transform_origin The transform origin for the ellipse.
        Ellipse(const Color &fill,
                const Point &center,
                const Point &radius,
                const Point transform_origin);

        //! Draws the ellipse on a PNGImage.
        //! @param img The PNGImage object to draw on.
        void draw(PNGImage &img) const override;

        //! Translates the ellipse by the given x and y values.
        //! @param x The x-coordinate translation.
        //! @param y The y-coordinate translation.
        void translate(int x, int y) override;

        //! Rotates the ellipse by the given angle.
        //! @param v The angle to rotate the ellipse.
        void rotate(int v) override;

        //! Scales the ellipse by the given factor.
        //! @param v The scaling factor.
        void scale(int v) override;

        //! Clones the ellipse with a new transform origin.
        //! @param transform_origin The new transform origin.
        //! @return A pointer to the cloned Ellipse.
        SVGElement *clone(const Point transform_origin) const override;

    private:
        Color fill;             //!< The fill color of the ellipse.
        Point center;           //!< The center point of the ellipse.
        Point radius;           //!< The radius of the ellipse.
        Point transform_origin; //!< The transform origin for the ellipse.
    };

    //! Class representing a line SVG element.
    class Line : public SVGElement
    {
    public:
        //! Constructs a Line object.
        //! @param stroke The stroke color of the line.
        //! @param start The starting point of the line.
        //! @param end The ending point of the line.
        //! @param transform_origin The transform origin for the line.
        Line(const Color &stroke,
             const Point &start,
             const Point &end,
             const Point transform_origin);

        //! Draws the line on a PNGImage.
        //! @param img The PNGImage object to draw on.
        void draw(PNGImage &img) const override;

        //! Translates the line by the given x and y values.
        //! @param x The x-coordinate translation.
        //! @param y The y-coordinate translation.
        void translate(int x, int y) override;

        //! Rotates the line by the given angle.
        //! @param v The angle to rotate the line.
        void rotate(int v) override;

        //! Scales the line by the given factor.
        //! @param v The scaling factor.
        void scale(int v) override;

        //! Clones the line with a new transform origin.
        //! @param transform_origin The new transform origin.
        //! @return A pointer to the cloned Line.
        SVGElement *clone(const Point transform_origin) const override;

    private:
        Color stroke;           //!< The stroke color of the line.
        Point start;            //!< The starting point of the line.
        Point end;              //!< The ending point of the line.
        Point transform_origin; //!< The transform origin for the line.
    };

    //! Class representing a polygon SVG element.
    class Polygon : public SVGElement
    {
    public:
        //! Constructs a Polygon object.
        //! @param points The points defining the polygon.
        //! @param fill The fill color of the polygon.
        //! @param transform_origin The transform origin for the polygon.
        Polygon(const std::vector<Point> &points,
                const Color &fill,
                const Point transform_origin);

        //! Draws the polygon on a PNGImage.
        //! @param img The PNGImage object to draw on.
        void draw(PNGImage &img) const override;

        //! Translates the polygon by the given x and y values.
        //! @param x The x-coordinate translation.
        //! @param y The y-coordinate translation.
        void translate(int x, int y) override;

        //! Rotates the polygon by the given angle.
        //! @param v The angle to rotate the polygon.
        void rotate(int v) override;

        //! Scales the polygon by the given factor.
        //! @param v The scaling factor.
        void scale(int v) override;

        //! Clones the polygon with a new transform origin.
        //! @param transform_origin The new transform origin.
        //! @return A pointer to the cloned Polygon.
        SVGElement *clone(const Point transform_origin) const override;

    private:
        std::vector<Point> points; //!< The points defining the polygon.
        Color fill;                //!< The fill color of the polygon.
        Point transform_origin;    //!< The transform origin for the polygon.
    };

    //! Class representing a group of SVG elements.
    class Group : public SVGElement
    {
    public:
        //! Constructs a Group object.
        //! @param elements The vector of SVGElement pointers.
        //! @param transform_origin The transform origin for the group.
        Group(const std::vector<SVGElement *> &elements,
              const Point transform_origin);

        //! Draws the group of elements on a PNGImage.
        //! @param img The PNGImage object to draw on.
        void draw(PNGImage &img) const override;

        //! Translates the group by the given x and y values.
        //! @param x The x-coordinate translation.
        //! @param y The y-coordinate translation.
        void translate(int x, int y) override;

        //! Rotates the group by the given angle.
        //! @param v The angle to rotate the group.
        void rotate(int v) override;

        //! Scales the group by the given factor.
        //! @param v The scaling factor.
        void scale(int v) override;

        //! Clones the group with a new transform origin.
        //! @param transform_origin The new transform origin.
        //! @return A pointer to the cloned Group.
        SVGElement *clone(const Point transform_origin) const override;

    private:
        std::vector<SVGElement *> elements; //!< The vector of SVGElement pointers.
        Point transform_origin;             //!< The transform origin for the group.
    };

    //! Class representing a 'use' element that references another SVG element.
    class Use : public SVGElement
    {
    public:
        //! Constructs a Use object.
        //! @param copied The SVGElement being referenced.
        //! @param transform_origin The transform origin for the use element.
        Use(SVGElement *copied,
            const Point transform_origin);

        //! Draws the referenced element on a PNGImage.
        //! @param img The PNGImage object to draw on.
        void draw(PNGImage &img) const override;

        //! Translates the referenced element by the given x and y values.
        //! @param x The x-coordinate translation.
        //! @param y The y-coordinate translation.
        void translate(int x, int y) override;

        //! Rotates the referenced element by the given angle.
        //! @param v The angle to rotate the element.
        void rotate(int v) override;

        //! Scales the referenced element by the given factor.
        //! @param v The scaling factor.
        void scale(int v) override;

        //! Clones the use element with a new transform origin.
        //! @param transform_origin The new transform origin.
        //! @return A pointer to the cloned Use element.
        SVGElement *clone(const Point transform_origin) const override;

    private:
        SVGElement *copied;     //!< The SVGElement being referenced.
        Point transform_origin; //!< The transform origin for the use element.
    };
}
#endif
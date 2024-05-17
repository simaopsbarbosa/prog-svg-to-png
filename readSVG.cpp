#include <iostream>
#include <sstream>
#include "SVGElements.hpp"
#include "external/tinyxml2/tinyxml2.h"
#include <string.h>

using namespace std;
using namespace tinyxml2;

namespace svg
{
    //! Gets transform-origin point.
    //! @param child The XMLElement to search for transform-origin
    //! @return Point transform-origin from XMLELement
    Point getTransformOrigin(XMLElement *child)
    {
        std::string transform_origin_str;
        if (child->Attribute("transform-origin") != NULL)
        {
            // get transform_origin string (ex: "150 150" or "150, 150")
            transform_origin_str = child->Attribute("transform-origin");

            // replace commas with spaces
            for (char &c : transform_origin_str)
            {
                if (c == ',')
                {
                    c = ' ';
                }
            }
        }
        else
        {
            // if there is no "transform-origin" attritube function should return {0,0}
            transform_origin_str = "0 0";
        }
        int torigin_x, torigin_y;
        stringstream originSStream(transform_origin_str);
        originSStream >> torigin_x >> torigin_y; // get first and second values
        Point res = {torigin_x, torigin_y};
        return res;
    }

    //! Applies transformations to SVGElement.
    //! @param child The XMLElement with transformations.
    //! @param elem The SVGElement to transform.
    void applyTransform(XMLElement *child, SVGElement *elem)
    {
        std::string operation;
        if (child->Attribute("transform") != NULL)
        {
            // get transform attribute
            std::string transform = child->Attribute("transform");
            // replace characters '(', ')' and ',' with spaces
            for (char &c : transform)
            {
                if (c == '(' || c == ')' || c == ',')
                {
                    c = ' ';
                }
            }

            std::stringstream sstream(transform);
            sstream >> operation;
            if (operation == "rotate")
            {
                int v;
                sstream >> v;
                elem->rotate(v);
            }
            else if (operation == "scale")
            {
                int v;
                sstream >> v;
                elem->scale(v);
            }
            else if (operation == "translate")
            {
                int x, y;
                sstream >> x;
                sstream >> y;
                elem->translate(x, y);
            }
        }
    }

    //! Seaches an XMLElement for an SVGElement and pushes it to vector svg_elements.
    //! @param child XMLElement to search.
    //! @param svg_elements Vector of SVGElements to push to.
    //! @param elements_with_id Map with all elements that have an id.
    void getElement(XMLElement *child, std::vector<SVGElement *> &svg_elements, std::map<std::string, SVGElement *> &elements_with_id)
    {
        // ELLIPSE
        if (std::string(child->Name()) == "ellipse")
        {

            // exemplo:
            // cx="100"
            // cy="100"
            // rx="95"
            // ry="20"
            // fill="red"

            Point center;
            center.x = child->IntAttribute("cx");
            center.y = child->IntAttribute("cy");

            Point radius;
            radius.x = child->IntAttribute("rx");
            radius.y = child->IntAttribute("ry");

            Color color = parse_color(child->Attribute("fill"));

            // get transform_origin point
            Point transform_origin = getTransformOrigin(child);
            // dynamically allocate new ellipse object
            Ellipse *elem = new Ellipse(color, center, radius, transform_origin);
            // check and apply transforms
            applyTransform(child, elem);
            // check if child has an id and add to elements_with_id map
            if (child->Attribute("id") != NULL)
            {
                elements_with_id[child->Attribute("id")] = elem;
            }
            // push ellipse into svg_elements vector
            svg_elements.push_back(elem);
        }

        // CIRCLE
        if (std::string(child->Name()) == "circle")
        {

            // exemplo:
            // cx="100"
            // cy="100"
            // r="95"
            // fill="red"

            Point center;
            center.x = child->IntAttribute("cx");
            center.y = child->IntAttribute("cy");

            Point radius;
            radius.x = child->IntAttribute("r");
            radius.y = radius.x;

            Color color = parse_color(child->Attribute("fill"));

            // get transform_origin point
            Point transform_origin = getTransformOrigin(child);
            // dynamically allocate new ellipse object
            Ellipse *elem = new Ellipse(color, center, radius, transform_origin);
            // check and apply transforms
            applyTransform(child, elem);
            // check if child has an id and add to elements_with_id map
            if (child->Attribute("id") != NULL)
            {
                elements_with_id[child->Attribute("id")] = elem;
            }
            // push ellipse into svg_elements vector
            svg_elements.push_back(elem);
        }

        // LINE
        if (std::string(child->Name()) == "line")
        {

            // exemplo:
            // x1="1"
            // y1="198"
            // x2="1"
            // y2="1"
            // stroke="red"

            Point start;
            start.x = child->IntAttribute("x1");
            start.y = child->IntAttribute("y1");

            Point end;
            end.x = child->IntAttribute("x2");
            end.y = child->IntAttribute("y2");

            Color color = parse_color(child->Attribute("stroke"));

            // get transform_origin point
            Point transform_origin = getTransformOrigin(child);
            // dynamically allocate new line object
            Line *elem = new Line(color, start, end, transform_origin);
            // check and apply transforms
            applyTransform(child, elem);
            // check if child has an id and add to elements_with_id map
            if (child->Attribute("id") != NULL)
            {
                elements_with_id[child->Attribute("id")] = elem;
            }
            // push line into svg_elements vector
            svg_elements.push_back(elem);
        }

        // POLYLINE
        if (std::string(child->Name()) == "polyline")
        {

            // exemplo:
            // points="0,0 0,399 399,399, 399,199"
            // fill="red"

            std::string points_str = child->Attribute("points");

            // substituir virgulas com espaços
            for (char &c : points_str)
            {
                if (c == ',')
                {
                    c = ' ';
                }
            }
            // separar valores e push_back para numbers
            std::stringstream ss(points_str);
            int num;
            std::vector<int> numbers;
            while (ss >> num)
            {
                numbers.push_back(num);
            }

            Color color = parse_color(child->Attribute("stroke"));

            for (long unsigned int i = 0; i < numbers.size() - 3; i += 2)
            {
                Point start = {numbers[i], numbers[i + 1]};
                Point end = {numbers[i + 2], numbers[i + 3]};

                // get transform_origin point
                Point transform_origin = getTransformOrigin(child);
                // dynamically allocate new line obejct
                Line *elem = new Line(color, start, end, transform_origin);
                // check and apply transforms
                applyTransform(child, elem);
                // check if child has an id and add to elements_with_id map
                if (child->Attribute("id") != NULL)
                {
                    elements_with_id[child->Attribute("id")] = elem;
                }
                // push line into svg_elements vector
                svg_elements.push_back(elem);
            }
        }

        // POLYGON
        if (std::string(child->Name()) == "polygon")
        {

            // exemplo:
            // points="0,0 0,399 399,399, 399,199"
            // fill="red"

            std::string points_str = child->Attribute("points");

            // substituir virgulas com espaços
            for (char &c : points_str)
            {
                if (c == ',')
                {
                    c = ' ';
                }
            }

            // separar valores e push_back para numbers
            std::stringstream ss(points_str);
            int num;
            std::vector<int> numbers;
            while (ss >> num)
            {
                numbers.push_back(num);
            }

            vector<Point> points;
            for (unsigned int i = 0; i < numbers.size() - 1; i += 2)
            {
                Point point = {numbers[i], numbers[i + 1]};
                points.push_back(point);
            }

            Color color = parse_color(child->Attribute("fill"));

            // get transform_origin point
            Point transform_origin = getTransformOrigin(child);
            // dynamically allocate new polygon
            Polygon *elem = new Polygon(points, color, transform_origin);
            // check and apply transforms
            applyTransform(child, elem);
            // check if child has an id and add to elements_with_id map
            if (child->Attribute("id") != NULL)
            {
                elements_with_id[child->Attribute("id")] = elem;
            }
            // push polygon into svg_elements vector
            svg_elements.push_back(elem);
        }

        // RECT
        if (std::string(child->Name()) == "rect")
        {

            // exemplo:
            // x="0"
            // y="0"
            // fill="blue"
            // width="400"
            // height="600"

            int x = child->IntAttribute("x"); // get x
            int y = child->IntAttribute("y"); // get y

            int width_rect = child->IntAttribute("width");   // get width
            int height_rect = child->IntAttribute("height"); // get height

            vector<Point> points;
            points.push_back({x, y});                                    // top-left corner
            points.push_back({x + width_rect - 1, y});                   // top-right corner
            points.push_back({x + width_rect - 1, y + height_rect - 1}); // bottom-right corner
            points.push_back({x, y + height_rect - 1});                  // bottom-left corner

            Color color = parse_color(child->Attribute("fill")); // get color

            // get transform_origin point
            Point transform_origin = getTransformOrigin(child);
            // dynamically allocate new polygon
            Polygon *elem = new Polygon(points, color, transform_origin);
            // check and apply transforms
            applyTransform(child, elem);
            // check if child has an id and add to elements_with_id map
            if (child->Attribute("id") != NULL)
            {
                elements_with_id[child->Attribute("id")] = elem;
            }
            // push polygon into svg_elements vector
            svg_elements.push_back(elem);
        }

        // GROUP
        if (std::string(child->Name()) == "g")
        {

            std::vector<SVGElement *> elements;
            for (XMLElement *group_child = child->FirstChildElement(); group_child != nullptr; group_child = group_child->NextSiblingElement())
            {
                getElement(group_child, elements, elements_with_id);
            }

            // get transform_origin point
            Point transform_origin = getTransformOrigin(child);
            // dynamically allocate new group
            Group *elem = new Group(elements, transform_origin);
            // check and apply transforms
            applyTransform(child, elem);
            // check if child has an id and add to elements_with_id map
            if (child->Attribute("id") != NULL)
            {
                elements_with_id[child->Attribute("id")] = elem;
            }
            // push group into svg_elements vector
            svg_elements.push_back(elem);
        }

        // USE
        if (std::string(child->Name()) == "use")
        {
            // get transform_origin point
            Point transform_origin = getTransformOrigin(child);

            // get href
            std::string href = child->Attribute("href");
            href = href.erase(0, 1); // erase '#'

            // copy corresponding element
            auto elem = elements_with_id.at(href)->clone(transform_origin);

            // check and apply transforms
            applyTransform(child, elem);
            // check if child has an id and add to elements_with_id map
            if (child->Attribute("id") != NULL)
            {
                elements_with_id[child->Attribute("id")] = elem;
            }
            // push polygon into svg_elements vector
            svg_elements.push_back(elem);
        }
    }

    void readSVG(const string &svg_file, Point &dimensions, vector<SVGElement *> &svg_elements)
    {
        XMLDocument doc;
        XMLError r = doc.LoadFile(svg_file.c_str());
        if (r != XML_SUCCESS)
        {
            throw runtime_error("Unable to load " + svg_file);
        }
        XMLElement *xml_elem = doc.RootElement();

        // get image dimensions
        dimensions.x = xml_elem->IntAttribute("width");
        dimensions.y = xml_elem->IntAttribute("height");

        // create map of ids and elements that have ids
        std::map<std::string, SVGElement *> elements_with_id;

        // loop over all child elements
        for (XMLElement *child = xml_elem->FirstChildElement(); child != nullptr; child = child->NextSiblingElement())
        {
            getElement(child, svg_elements, elements_with_id);
        }
    }
}

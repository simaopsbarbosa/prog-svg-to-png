#include <iostream>
#include <map> 
#include <sstream>
#include "SVGElements.hpp"
#include "external/tinyxml2/tinyxml2.h"
#include <string.h>

using namespace std;
using namespace tinyxml2;

namespace svg
{

    Point getTransformOrigin(XMLElement* child) {
        std::string transform_origin_str;
        Point res;
            if (child->Attribute("transform-origin") != NULL) {
                transform_origin_str = child->Attribute("transform-origin");
                for (char& c : transform_origin_str) {
                    if (c == ',') {
                        c = ' ';
                    }
                }
            } else {
                transform_origin_str = "0 0";
            }
            int torigin_x, torigin_y;
            stringstream originSStream(transform_origin_str);
            originSStream >> torigin_x >> torigin_y;
            res = {torigin_x, torigin_y};
        return res;
    }

    void applyTransform(XMLElement* child, SVGElement* elem) {
        std::string operation;
        if (child->Attribute("transform") != NULL) {
            
            std::string transform = child->Attribute("transform");
            for (char& c : transform) {
                if (c == '(' || c == ')' || c == ',') {
                    c = ' ';
                }
            }

            std::stringstream sstream(transform);
            sstream >> operation; // e.g. get "rotate"
            if (operation == "rotate") {
                int n;
                sstream >> n;
                elem->rotate(n);
            } else if (operation == "scale") {
                int n;
                sstream >> n;
                elem->scale(n);
            } else if (operation == "translate") {
                int n,m;
                sstream >> n;
                sstream >> m;
                elem->translate(n, m);
            }
        }
    }

    void readSVG(const string& svg_file, Point& dimensions, vector<SVGElement *>& svg_elements)
    {
        XMLDocument doc;
        XMLError r = doc.LoadFile(svg_file.c_str());
        if (r != XML_SUCCESS)
        {
            throw runtime_error("Unable to load " + svg_file);
        }
        XMLElement *xml_elem = doc.RootElement();

        dimensions.x = xml_elem->IntAttribute("width");
        dimensions.y = xml_elem->IntAttribute("height");
        
        // POPULATING SVG_ELEMENTS VECTOR

        for (XMLElement *child = xml_elem->FirstChildElement(); child != nullptr; child = child->NextSiblingElement())
        {
            // ELLIPSE
            if (strcmp(child->Name(), "ellipse") == 0) {

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
                // push ellipse into svg_elements vector
                svg_elements.push_back(elem);
            }

            // CIRCLE
            if (strcmp(child->Name(), "circle") == 0) {

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
                // push ellipse into svg_elements vector
                svg_elements.push_back(elem);
            }

            // LINE
            if (strcmp(child->Name(), "line") == 0) {

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
                // push line into svg_elements vector
                svg_elements.push_back(elem);
            }

            // POLYLINE
            if (strcmp(child->Name(), "polyline") == 0) {

                // exemplo:
                    // points="0,0 0,399 399,399, 399,199" 
                    // fill="red"

                std::string points_str = child->Attribute("points");

                // substituir virgulas com espaços
                for (char& c : points_str) {
                    if (c == ',') {
                        c = ' ';
                    }
                }
                // separar valores e push_back para numbers
                std::stringstream ss(points_str);
                int num;
                std::vector<int> numbers;
                while (ss >> num) {
                    numbers.push_back(num);
                }

                Color color = parse_color(child->Attribute("stroke"));

                for (long unsigned int i = 0; i < numbers.size() - 3; i+=2) {
                    Point start = {numbers[i], numbers[i+1]};
                    Point end = {numbers[i+2], numbers[i+3]};

                    // get transform_origin point
                    Point transform_origin = getTransformOrigin(child);
                    // dynamically allocate new line obejct
                    Line *elem = new Line(color, start, end, transform_origin);
                    // check and apply transforms
                    applyTransform(child, elem);
                    // push line into svg_elements vector
                    svg_elements.push_back(elem);
                }
            }

            // POLYGON
            if (strcmp(child->Name(), "polygon") == 0) {

                // exemplo:
                    // points="0,0 0,399 399,399, 399,199" 
                    // fill="red"

                std::string points_str = child->Attribute("points");

                // substituir virgulas com espaços
                for (char& c : points_str) {
                    if (c == ',') {
                        c = ' ';
                    }
                }

                // separar valores e push_back para numbers
                std::stringstream ss(points_str);
                int num;
                std::vector<int> numbers;
                while (ss >> num) {
                    numbers.push_back(num);
                }

                vector<Point> points;
                for (unsigned int i = 0; i < numbers.size() - 1; i+=2) {
                    Point point = {numbers[i], numbers[i+1]};
                    points.push_back(point);
                }

                Color color = parse_color(child->Attribute("fill"));

                // get transform_origin point
                Point transform_origin = getTransformOrigin(child);
                // dynamically allocate new polygon
                Polygon *elem = new Polygon(points, color, transform_origin);
                // check and apply transforms
                applyTransform(child, elem);
                // push polygon into svg_elements vector
                svg_elements.push_back(elem);
            }

            // RECT
            if (strcmp(child->Name(), "rect") == 0) {

                // exemplo:
                    // x="0" 
                    // y="0" 
                    // fill="blue" 
                    // width="400" 
                    // height="600"
                
                int x = child->IntAttribute("x"); // get x
                int y = child->IntAttribute("y"); // get y

                int width_rect = child->IntAttribute("width"); // get width
                int height_rect = child->IntAttribute("height"); // get height

                vector<Point> points;
                points.push_back({x,y}); // top-left corner
                points.push_back({x+width_rect-1,y}); // top-right corner
                points.push_back({x+width_rect-1,y+height_rect-1}); // bottom-right corner
                points.push_back({x,y+height_rect-1}); // bottom-left corner

                Color color = parse_color(child->Attribute("fill")); // get color

                // get transform_origin point
                Point transform_origin = getTransformOrigin(child);
                // dynamically allocate new line
                Polygon *elem = new Polygon(points, color, transform_origin);
                // check and apply transforms
                applyTransform(child, elem);
                // push polygon into svg_elements vector
                svg_elements.push_back(elem);
            }
        }
    }
}

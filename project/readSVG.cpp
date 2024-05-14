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
                    // 1: cx="100"
                    // 2: cy="100"
                    // 3: rx="95"
                    // 4: ry="20"
                    // 5: fill="red"

                Point center;
                center.x = child->IntAttribute("cx");
                center.y = child->IntAttribute("cy");

                Point radius;
                radius.x = child->IntAttribute("rx");
                radius.y = child->IntAttribute("ry");

                Color color = parse_color(child->Attribute("fill"));

                // dynamically allocate new ellipse
                Ellipse *elem = new Ellipse(color, center, radius);
                // push ellipse into svg_elements vector
                svg_elements.push_back(elem);
            }

            // CIRCLE
            if (strcmp(child->Name(), "circle") == 0) {

                // exemplo:
                    // 1: cx="100"
                    // 2: cy="100"
                    // 3: r="95"
                    // 5: fill="red"
                
                Point center;
                center.x = child->IntAttribute("cx");
                center.y = child->IntAttribute("cy");

                Point radius;
                radius.x = child->IntAttribute("r");
                radius.y = radius.x;

                Color color = parse_color(child->Attribute("fill"));

                // dynamically allocate new ellipse
                Ellipse *elem = new Ellipse(color, center, radius);
                // push ellipse into svg_elements vector
                svg_elements.push_back(elem);
            }

            // LINE
            if (strcmp(child->Name(), "line") == 0) {

                // exemplo:
                    // 1: x1="1"
                    // 2: y1="198"
                    // 3: x2="1"
                    // 4: y2="1"
                    // 5: stroke="red"

                Point start;
                start.x = child->IntAttribute("x1");
                start.y = child->IntAttribute("y1");

                Point end;
                end.x = child->IntAttribute("x2");
                end.y = child->IntAttribute("y2");

                Color color = parse_color(child->Attribute("stroke"));

                // dynamically allocate new line
                Line *elem = new Line(color, start, end);
                // push line into svg_elements vector
                svg_elements.push_back(elem);
            }

            // POLYLINE
            if (strcmp(child->Name(), "polyline") == 0) {

                // exemplo:
                    // 1: points="0,0 0,399 399,399, 399,199" 
                    // 2: fill="red"

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

                    // dynamically allocate new line
                    Line *elem = new Line(color, start, end);
                    // push line into svg_elements vector
                    svg_elements.push_back(elem);
                }
            }

            // POLYGON
            if (strcmp(child->Name(), "polygon") == 0) {

                // exemplo:
                    // 1: points="0,0 0,399 399,399, 399,199" 
                    // 2: fill="red"

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

                // dynamically allocate new polygon
                Polygon *elem = new Polygon(points, color);
                // push polygon into svg_elements vector
                svg_elements.push_back(elem);
            }

            // RECT
            if (strcmp(child->Name(), "rect") == 0) {

                // exemplo:
                    // 1: x="0" 
                    // 2: y="0" 
                    // 3: fill="blue" 
                    // 4: width="400" 
                    // 5: height="600"
                
                int x = child->IntAttribute("x"); // get x
                int y = child->IntAttribute("y"); // get y

                int width_rect = child->IntAttribute("width") -1; // get width
                int height_rect = child->IntAttribute("height") -1; // get height

                vector<Point> points;
                points.push_back({x,y}); // top-left corner
                points.push_back({x+width_rect,y}); // top-right corner
                points.push_back({x+width_rect,y+height_rect}); // bottom-right corner
                points.push_back({x,y+height_rect}); // bottom-left corner

                Color color = parse_color(child->Attribute("fill")); // get color

                // dynamically allocate new line
                Polygon *elem = new Polygon(points, color);
                // push polygon into svg_elements vector
                svg_elements.push_back(elem);
            }
        }
    }
}

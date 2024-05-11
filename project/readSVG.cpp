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
            // get attributes
            std::map<std::string, std::string> attributes;
            for (const XMLAttribute *attr = child->FirstAttribute(); attr != nullptr; attr = attr->Next()) {
                std::string attr_name = attr->Name();
                std::string attr_value = attr->Value();
                attributes[attr_name] = attr_value;
            }

            // ELLIPSE
            if (strcmp(child->Name(), "ellipse") == 0) {
                // 1: cx="100"
                // 2: cy="100"
                // 3: rx="95"
                // 4: ry="20"
                // 5: fill="red"
                
                std::string cx = attributes["cx"];
                int cx_int = stoi(cx);

                std::string cy = attributes["cy"];
                int cy_int = stoi(cy);

                Point center, radius;
                center.x = cx_int;
                center.y = cy_int;

                std::string rx = attributes["rx"];
                int rx_int = stoi(rx);

                std::string ry = attributes["ry"];
                int ry_int = stoi(ry);

                radius.x = rx_int;
                radius.y = ry_int;

                std::string color_str = attributes["fill"];
                Color color = parse_color(color_str);

                // dynamically allocate new ellipse
                Ellipse *elem = new Ellipse(color, center, radius);
                // push ellipse into svg_elements vector
                svg_elements.push_back(elem);
            }

            // CIRCLE
            if (strcmp(child->Name(), "circle") == 0) {
                // 1: cx="100"
                // 2: cy="100"
                // 3: r="95"
                // 5: fill="red"

                std::string cx = attributes["cx"];
                int cx_int = stoi(cx);

                std::string cy = attributes["cy"];
                int cy_int = stoi(cy);

                Point center;
                center.x = cx_int;
                center.y = cy_int;

                std::string radius_str = attributes["r"];
                int radius = stoi(radius_str);

                std::string color_str = attributes["fill"];
                Color color = parse_color(color_str);

                Circle *elem = new Circle(color, center, radius);
                svg_elements.push_back(elem);
            }

            // LINE
            if (strcmp(child->Name(), "line") == 0) {
                // 1: x1="1"
                // 2: y1="198"
                // 3: x2="1"
                // 4: y2="1"
                // 5: stroke="red"

                std::string x1 = attributes["x1"];
                int x1_int = stoi(x1);

                std::string y1 = attributes["y1"];
                int y1_int = stoi(y1);

                std::string x2 = attributes["x2"];
                int x2_int = stoi(x2);

                std::string y2 = attributes["y2"];
                int y2_int = stoi(y2);

                std::string color_str = attributes["stroke"];
                Color color = parse_color(color_str);

                Point start = {x1_int,y1_int};
                Point end = {x2_int,y2_int};

                Line *elem = new Line(color, start, end);
                svg_elements.push_back(elem);
            }

            // POLYLINE
            if (strcmp(child->Name(), "polyline") == 0) {
                // 1: points="0,0 0,399 399,399, 399,199" 
                // 2: fill="red"

                std::string points_str = attributes["points"];

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

                std::string color_str = attributes["stroke"];
                Color color = parse_color(color_str);

                for (long unsigned int i = 0; i < numbers.size() - 3; i+=2) {
                    Point start = {numbers[i], numbers[i+1]};
                    Point end = {numbers[i+2], numbers[i+3]};
                    Line *elem = new Line(color, start, end);
                    svg_elements.push_back(elem);
                }
            }

            // POLYGON
            if (strcmp(child->Name(), "polygon") == 0) {
                // 1: points="0,0 0,399 399,399, 399,199" 
                // 2: fill="red"

                std::string points_str = attributes["points"];

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

                std::string color_str = attributes["fill"];
                Color color = parse_color(color_str);

                Polygon *elem = new Polygon(points, color);
                svg_elements.push_back(elem);
            }

            // RECT
            if (strcmp(child->Name(), "rect") == 0) {
                // 1: x="0" 
                // 2: y="0" 
                // 3: fill="blue" 
                // 4: width="400" 
                // 5: height="600"

                std::string color_str = attributes["fill"]; // get color
                cout << "[DEBUG] color: " << color_str << '\n';
                Color color = parse_color(color_str);

                int x = stoi(attributes["x"]); // get x
                int y = stoi(attributes["y"]); // get y

                int width_rect = stoi(attributes["width"]) -1; // get width
                int height_rect = stoi(attributes["height"]) -1; // get height

                vector<Point> points;
                points.push_back({x,y});
                points.push_back({x+width_rect,y});
                points.push_back({x+width_rect,y+height_rect});
                points.push_back({x,y+height_rect});

                Polygon *elem = new Polygon(points, color);
                svg_elements.push_back(elem);
            }
        }
    }
}

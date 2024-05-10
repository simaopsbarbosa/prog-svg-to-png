#include <iostream>
#include <map>
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

            // provavelmente era muito melhor se fizesse algo deste genero, provavelmente vou mudar 
            // // get attributes
            // std::map<std::string, const XMLAttribute*> attributes;
            // for (const XMLAttribute *attr = child->FirstAttribute(); attr != nullptr; attr = attr->Next()) {
            //     attributes[attr->Name()] = attr;
            // }

            // ELLIPSE
            if (strcmp(child->Name(), "ellipse") == 0) {
                Color color;
                Point center, radius;

                // 1: cx="100"
                // 2: cy="100"
                // 3: rx="95"
                // 4: ry="20"
                // 5: fill="red"

                const XMLAttribute *attr = child->FirstAttribute(); // cx
                const char* cx = attr->Value();
                int cx_int = stoi(cx);

                attr = attr->Next(); // cy
                const char* cy = attr->Value();
                int cy_int = stoi(cy);

                center.x = cx_int;
                center.y = cy_int;

                attr = attr->Next(); // rx
                const char* rx = attr->Value();
                int rx_int = stoi(rx);

                attr = attr->Next(); // ry
                const char* ry = attr->Value();
                int ry_int = stoi(ry);

                radius.x = rx_int;
                radius.y = ry_int;

                attr = attr->Next(); // fill
                const char* color_str = attr->Value();
                color = parse_color(color_str);

                // isto funciona (amen)
                Ellipse *elem = new Ellipse(color, center, radius);
                svg_elements.push_back(elem);
            }

            // CIRCLE
            if (strcmp(child->Name(), "circle") == 0) {
                Color color;
                Point center;
                int radius;

                // for (const XMLAttribute *attr = child->FirstAttribute(); attr != nullptr; attr = attr->Next())

                // 1: cx="100"
                // 2: cy="100"
                // 3: r="95"
                // 5: fill="red"

                const XMLAttribute *attr = child->FirstAttribute(); // cx
                const char* cx = attr->Value();
                int cx_int = stoi(cx);

                attr = attr->Next(); // cy
                const char* cy = attr->Value();
                int cy_int = stoi(cy);

                center.x = cx_int;
                center.y = cy_int;

                attr = attr->Next(); // r
                const char* radius_str = attr->Value();
                radius = stoi(radius_str);

                attr = attr->Next(); // fill
                const char* color_str = attr->Value();
                color = parse_color(color_str);

                // isto funciona (amen)
                Circle *elem = new Circle(color, center, radius);
                svg_elements.push_back(elem);
            }

            // LINE
            if (strcmp(child->Name(), "line") == 0) {
                // <line x1="1" y1="198" x2="1" y2="1" stroke="red"/>
                Color color;

                // for (const XMLAttribute *attr = child->FirstAttribute(); attr != nullptr; attr = attr->Next())

                // 1: x1="1"
                // 2: y1="198"
                // 3: x2="1"
                // 4: y2="1"
                // 5: stroke="red"

                const XMLAttribute *attr = child->FirstAttribute(); // x1
                const char* x1 = attr->Value();
                int x1_int = stoi(x1);

                attr = attr->Next(); // y1
                const char* y1 = attr->Value();
                int y1_int = stoi(y1);

                attr = attr->Next(); // x2
                const char* x2 = attr->Value();
                int x2_int = stoi(x2);

                attr = attr->Next(); // y2
                const char* y2 = attr->Value();
                int y2_int = stoi(y2);

                attr = attr->Next(); // stroke
                const char* color_str = attr->Value();
                color = parse_color(color_str);

                Point start = {x1_int,y1_int};
                Point end = {x2_int,y2_int};

                // isto funciona (amen)
                Line *elem = new Line(color, start, end);
                svg_elements.push_back(elem);
            }
        }
    }
}

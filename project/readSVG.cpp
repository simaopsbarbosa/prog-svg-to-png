#include <iostream>
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
        
        // TODO complete code -->
        
        // POPULATING SVG_ELEMENTS VECTOR

        // vai ser algo do genero disto i guess

        for (XMLElement *child = xml_elem->FirstChildElement(); child != nullptr; child = child->NextSiblingElement())
        {
            if (strcmp(child->Name(), "ellipse") == 0) {
                std::cout << "found ellipse" << std::endl;

                Color color;
                Point center, radius;

                // for (const XMLAttribute *attr = child->FirstAttribute(); attr != nullptr; attr = attr->Next())

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

                // 1: cx="100"
                // 2: cy="100"
                // 3: rx="95"
                // 4: ry="20"
                // 5: fill="red"

                // isto funciona (amen)
                Ellipse *elem = new Ellipse(color, center, radius);
                svg_elements.push_back(elem);

            }
        }
    }
}

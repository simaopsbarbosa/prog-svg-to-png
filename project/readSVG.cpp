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
                Color cor;
                cor.blue = 244;
                cor.red = 12;
                cor.green = 156;

                Point centro;
                centro.x = 10;
                centro.y = 10;

                Point radius;
                radius.x = 5;
                radius.y = 3;

                // isto funciona (amen)
                Ellipse *elem = new Ellipse(cor, centro, radius);
                svg_elements.push_back(elem);

                // TODO get ellipse arguments
            }
        }
    }
}

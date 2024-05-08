
#include <iostream>
#include "SVGElements.hpp"
#include "external/tinyxml2/tinyxml2.h"

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
        // for (int i = 0; i < indentation; i++)
        //     std::cout << " ";
        //     std::cout << elem->Name() << " --> [";

        // for (const XMLAttribute *attr = elem->FirstAttribute(); attr != nullptr; attr = attr->Next())
        //     std::cout << " " << attr->Name() << "=\"" << attr->Value() << "\"";

        // std::cout << " ] " << std::endl;

        // for (XMLElement *child = elem->FirstChildElement(); child != nullptr; child = child->NextSiblingElement())
        // {
        //     dump(child, indentation + 2);
        // }
        
    }
}
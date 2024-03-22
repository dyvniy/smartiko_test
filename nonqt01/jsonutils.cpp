#include "jsonutils.h"
#include <sstream>
#include <iostream>

using boost::property_tree::ptree;

std::string JsonUtils::indent(int level)
{
    std::string s;
    for (int i = 0; i<level; i++) s += "  ";
    return s;
}

void JsonUtils::printTree(ptree &pt, int level)
{
    if (pt.empty())
    {
        std::cout << "\"" << pt.data() << "\"";
    }

    else
    {
        if (level) std::cout << std::endl;

        std::cout << indent(level) << "{" << std::endl;

        for (ptree::iterator pos = pt.begin(); pos != pt.end();)
        {
            std::cout << indent(level + 1) << "\"" << pos->first << "\": ";

            printTree(pos->second, level + 1);
            ++pos;
            if (pos != pt.end())
            {
                std::cout << ",";
            }
            std::cout << std::endl;
        }

        std::cout << indent(level) << "}";
    }
    //std::cout << std::endl;
    return;
}

std::string JsonUtils::toString(const ptree &pt)
{
    std::stringstream ss;
    if (pt.empty()) {
        ss << "\"" << pt.data() << "\"";
    }
    else
    {
        ss << "{";
        for (ptree::const_iterator pos = pt.begin(); pos != pt.end();)
        {
            ss << "\"" << pos->first << "\": ";

            ss << toString(pos->second);
            ++pos;
            if (pos != pt.end())
            {
                ss << ",";
            }
        }

        ss << "}";
    }
    return ss.str();
}

// #include <boost/property_tree/ptree.hpp>
// #include <boost/property_tree/json_parser.hpp>
ptree JsonUtils::parceJson(std::string json)
{
  std::stringstream ss;
  ss << json;

  boost::property_tree::ptree pt;
  boost::property_tree::read_json(ss, pt);
  //std::cout << pt.get<std::string>("foo") << std::endl;

  return pt;
}

ptree JsonUtils::simpleArray() {

    ptree pt;
    ptree children;
    ptree child1, child2, child3;

    child1.put("", 1);
    child2.put("", 2);
    child3.put("", 3);

    children.push_back(std::make_pair("", child1));
    children.push_back(std::make_pair("", child2));
    children.push_back(std::make_pair("", child3));

    pt.add_child("MyArray", children);

    //printTree(pt);
    return pt;
}

ptree JsonUtils::arrayOverObjects() {
    ptree pt;
    ptree children;
    ptree child1, child2, child3;


    child1.put("childkeyA", 1);
    child1.put("childkeyB", 2);

    child2.put("childkeyA", 3);
    child2.put("childkeyB", 4);

    child3.put("childkeyA", 5);
    child3.put("childkeyB", 6);

    children.push_back(std::make_pair("", child1));
    children.push_back(std::make_pair("", child2));
    children.push_back(std::make_pair("", child3));

    pt.put("testkey", "testvalue");
    pt.add_child("MyArray", children);

    //printTree(pt);
    return pt;
}

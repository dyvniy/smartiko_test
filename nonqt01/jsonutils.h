#ifndef JSONUTILS_H
#define JSONUTILS_H

#include <string>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

class JsonUtils
{
    static std::string indent(int level);

public:
    static void printTree(boost::property_tree::ptree &pt, int level = 0);
    static std::string toString(const boost::property_tree::ptree &pt);
    static boost::property_tree::ptree parseJson(std::string json);
    static boost::property_tree::ptree simpleArray();
    static boost::property_tree::ptree arrayOverObjects();
};

#endif // JSONUTILS_H

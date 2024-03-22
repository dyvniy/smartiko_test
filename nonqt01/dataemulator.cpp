#include "dataemulator.h"

#include <iostream>
#include <chrono>
#include <ctime>
#include <vector>
#include <sstream>

#include <boost/json.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include "jsonutils.h"

using boost::property_tree::ptree;

namespace DataEmulator_ns {

int chrono_time()
{
    auto start = std::chrono::system_clock::now();
    // Some computation here
    auto end = std::chrono::system_clock::now();

    std::chrono::duration<double> elapsed_seconds = end-start;
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);

    std::cout << "finished computation at " << std::ctime(&end_time)
              << "elapsed time: " << elapsed_seconds.count() << "s"
              << std::endl;
    return 0;
}

std::vector<std::string> date_time_format()
{
    std::time_t rawtime;
    std::tm* timeinfo;
    char dateBuffer [80], timeBuffer[80];
    std::vector<std::string> dt;

    std::time(&rawtime);  // int64
    timeinfo = std::localtime(&rawtime);

    std::strftime(dateBuffer,80,"%Y-%m-%d",timeinfo);
    std::strftime(timeBuffer,80,"%H:%M:%S",timeinfo);
    dt.push_back(dateBuffer);
    dt.push_back(timeBuffer);
    return dt;
}

} // DataEmulator_ns

DataEmulator::DataEmulator()
{
    DataEmulator_ns::chrono_time();

    if (false)
    {
        auto pt1 = JsonUtils::simpleArray();
        std::cout << JsonUtils::toString(pt1) << std::endl;
    }
    {
        auto pt2 = JsonUtils::arrayOverObjects();
        auto s2 = JsonUtils::toString(pt2);
        std::cout << s2 << std::endl;
        auto pt3 = JsonUtils::parceJson(s2);
        auto s3 = JsonUtils::toString(pt3);
        std::cout << s3 << std::endl;
    }
}

std::string DataEmulator::post()
{
    auto dt = DataEmulator_ns::date_time_format();
    std::stringstream ss;
    ss << "POST; 'val02', 89.90, '"
       << dt[0] << "', '" << dt[1]
       <<"', False";
    return ss.str();
}

std::string DataEmulator::get()
{
    return  "GET; name = 'val02'";
}

std::string DataEmulator::delete_()
{
    return "DELETE; name = 'valjhbgm n'";
}

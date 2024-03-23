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
        auto pt3 = JsonUtils::parseJson(s2);
        auto s3 = JsonUtils::toString(pt3);
        std::cout << s3 << std::endl;
    }
}

std::string DataEmulator::post(std::string args)
{
    // db fields "name, gpoup, acure_d, acure_t, graduated)"
    // db values "VALUES ('val02', 89.90, '2021/12/28', '16:24', False);";
    std::cout << "post_args: " << args << std::endl;

    auto dt = DataEmulator_ns::date_time_format();
    std::stringstream ss;
    ss << "POST; 'val02', 89.90, '"
       << dt[0] << "', '" << dt[1]
       <<"', True";
    return ss.str();
}

std::string DataEmulator::get(std::string args)
{
    std::cout << "get_args: " << args << std::endl;

    return  std::string("GET;") + args;
}

std::string DataEmulator::delete_(std::string args)
{
    std::cout << "delete_args: " << args << std::endl;

    return "DELETE; name = 'valjhbgm n'";
}

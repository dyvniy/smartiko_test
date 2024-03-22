#ifndef DBWORKER_H
#define DBWORKER_H

#include <string>
#include <memory>
#include <boost/property_tree/ptree.hpp>

class DbWorker
{
    struct Impl;
    std::shared_ptr<Impl> pImpl;

public:
    DbWorker();
    ~DbWorker();
    bool insert(std::string data);
    bool get(std::string data);
    bool delete_(std::string data);

    bool exec(boost::property_tree::ptree pt);
    bool insert(boost::property_tree::ptree pt);
    bool get(boost::property_tree::ptree pt);
    bool delete_(boost::property_tree::ptree pt);
};

#endif // DBWORKER_H

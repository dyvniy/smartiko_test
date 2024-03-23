#ifndef DATAEMULATOR_H
#define DATAEMULATOR_H

#include <string>

class DataEmulator
{
public:
    DataEmulator();

    std::string post(std::string args);
    std::string get(std::string args);
    std::string delete_(std::string args);
};

#endif // DATAEMULATOR_H

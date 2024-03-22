#ifndef DATAEMULATOR_H
#define DATAEMULATOR_H

#include <string>

class DataEmulator
{
public:
    DataEmulator();

    std::string post();
    std::string get();
    std::string delete_();
};

#endif // DATAEMULATOR_H

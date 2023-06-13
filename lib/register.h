#ifndef REGISTER_H
#define REGISTER_H

#include <string.h>
#include <unordered_map>
template <typename T>
class REGISTERS {
   public:
    std::unordered_map<std::string, T> REGISTERS;
    T& operator[](std::string index) { return REGISTERS[index]; }
    void ADD_REGISTER(std::string register_name, T initialization_value = 0) {
        REGISTERS[register_name] = initialization_value;
    }
};

#endif
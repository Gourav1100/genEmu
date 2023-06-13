// write an alu that does the following:
// store set on instructions inside an unordered_map and maps it to a function
// pointer
#ifndef INSTRUCTION_SET_H
#define INSTRUCTION_SET_H

#include <string>
#include <unordered_map>
#include "mmu.h"
#include "register.h"
template <typename T>
class INSTRUCTION_SET {
    typedef void (*OPCODE_FUNCTION)(REGISTERS<T>&, MMU<T>&);
    // opcode - void* function(void)
    std::unordered_map<std::string, OPCODE_FUNCTION> OPCODES;

   public:
    INSTRUCTION_SET() { OPCODES.clear(); }
    void insert_opcode(std::string opcode, OPCODE_FUNCTION function) {
        OPCODES[opcode] = function;
    }
    OPCODE_FUNCTION operator[](std::string OPCODE) { return OPCODES[OPCODE]; }
};

#endif
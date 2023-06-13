#include <iostream>
#include "./lib/instruction_set.h"
#include "./lib/mmu.h"
#include "./lib/register.h"
using namespace std;
#define BYTE 1
#define KILOBYTE 1024 * BYTE
#define MEGABYTE 1024 * KILOBYTE
#define GIGABYTE 1024 * MEGABYTE
#define MEMORY_SIZE
#define TYPE int16_t

void add(REGISTERS<TYPE>& registers, MMU<TYPE>& mmu) {
    registers["a"] = registers["b"] + registers["c"];
}
int main() {
    REGISTERS<TYPE> registers;
    MMU<TYPE> mmu(8 * KILOBYTE);
    INSTRUCTION_SET<TYPE> instruction_set;
    // add registers
    registers.ADD_REGISTER("a");
    registers.ADD_REGISTER("b");
    registers.ADD_REGISTER("c");
    registers.ADD_REGISTER("d");
    registers.ADD_REGISTER("e");
    registers.ADD_REGISTER("f");
    // add instruction set
    instruction_set.insert_opcode("addABC", add);
    // change value in registers B and C, and store the value into A
    registers["b"] = 10;
    registers["c"] = 20;
    instruction_set["addABC"](registers, mmu);
    int t = registers["a"];
    cout << registers["a"] << endl;

    return 0;
}
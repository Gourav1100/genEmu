#ifndef MMU_H
#define MMU_H

#include <iostream>
#include <unordered_map>
#include <vector>
template <typename T>
class MMU {
        class MEMORY {
            int MEMORY_SIZE, SIZE;
            T* MEMORY_STACK;
            std::vector<T*> DIRTY_POINTERS;
            std::unordered_map<T*, int> FLAGS;
            // 0 - clean, 1 - used, 2 - dirty
            public:
                MEMORY(int size_in_bytes) {
                    MEMORY_SIZE = size_in_bytes / sizeof(T);
                    MEMORY_STACK = (T*) malloc(MEMORY_SIZE * sizeof(T));
                    FLAGS.clear();
                    SIZE = 0;
                    DIRTY_POINTERS = std::vector<T*>();
                }
                T* push(T value) {
                    if(SIZE == MEMORY_SIZE) {
                        std::cerr << "Memory allocation failed! Buffer-overflow" << std::endl;
                        return nullptr;
                    }
                    if(DIRTY_POINTERS.size()) {
                        T* DIRTY_POINTER = DIRTY_POINTERS[DIRTY_POINTER.size() - 1];
                        *DIRTY_POINTER = value;
                        FLAGS[DIRTY_POINTER] = 1;
                        SIZE++;
                        DIRTY_POINTERS.pop_back();
                        return DIRTY_POINTER;
                    }
                    int index = SIZE;
                    MEMORY_STACK[index] = value;
                    FLAGS[&MEMORY_STACK[index]] = 1;
                    SIZE++;
                    return &MEMORY_STACK[index];
                }
                T pop(T* pointer) {
                    if(SIZE == 0) {
                        return 0;
                    }
                    T value = *pointer;
                    if(FLAGS[pointer] == 1) {
                        SIZE--;
                        FLAGS[pointer] = 2;
                        DIRTY_POINTERS.push_back(pointer);
                    }
                    return value;
                }
        };
        std::unordered_map<int, T*> RAM_TABLE;
        std::unordered_map<int, T*> PAGE_MEMORY_TABLE;
        MEMORY *RAM_MEMORY, *PAGE_MEMORY;
    public:
        MMU(int memory_size, int page_size = 0) {
            RAM_MEMORY = new MEMORY(memory_size);
            PAGE_MEMORY = new MEMORY(page_size);
        }
        void push(int virtualAddress, T value) {
            T* responsePointer = RAM_MEMORY->push(value);
            if(responsePointer == nullptr) {
                responsePointer = PAGE_MEMORY->push(value);
                PAGE_MEMORY_TABLE[virtualAddress] = responsePointer;
            } else {
                RAM_TABLE[virtualAddress] = responsePointer;
            }
        }
        T find(int virtualAddress) {
            if(RAM_TABLE.find(virtualAddress) != RAM_TABLE.end()) {
                return *RAM_TABLE[virtualAddress];
            }
            if(PAGE_MEMORY_TABLE.find(virtualAddress) != PAGE_MEMORY_TABLE.end()) {
                return *PAGE_MEMORY_TABLE[virtualAddress];
            }
            std::cerr << "Unable to access virtualAddress: " << virtualAddress << std::endl;
            return -1;
        }
        T pop(int virtualAddress) {
            if(RAM_TABLE.find(virtualAddress) != RAM_TABLE.end()) {
                return RAM_MEMORY->pop(RAM_TABLE[virtualAddress]);
            }
            if(PAGE_MEMORY_TABLE.find(virtualAddress) != PAGE_MEMORY_TABLE.end()) {
                return PAGE_MEMORY->pop(PAGE_MEMORY_TABLE[virtualAddress]);
            }
            std::cerr << "Unable to access virtualAddress: " << virtualAddress << std::endl;
            return -1;
        }

};

#endif
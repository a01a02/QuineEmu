//
// Created by Aaron H on 7/22/24.
//
#include "vm.hpp"
#include <algorithm>
#include <iostream>

// Constructor definition
VM::VM(size_t memory_size) : memory(memory_size, 0), registers{}, eip(0), eflags(0), halted(false) {
    init_memory_segments(memory_size);

}

void:: VM::init_memory_segments(size_t memory_size) {
    // init memory segments
}

void VM::load_program(const std::vector<uint8_t>& program) {
    // load the program into memory
}

void VM::execute() {
    while(!halted) {
        decode_and_execute();
    }
}

uint8_t VM::fetch() {
    // fetch from memory based on eip and increment eip
    return 0;
}

void VM::decode_and_execute() {
    uint8_t opcode = fetch();
    // assuming opcode are the keys to opcode_handlers map
    auto it = opcode_handlers.find(opcode);

    if (it == opcode_handlers.end()) {
        throw std::runtime_error("Invalid opcode.");
    }

    OpcodeHandler handler = it->second;
    (this->*handler)();
}

void VM::execute_mov() {
    // implement the MOV operation
}

void VM::execute_add() {
    // implement the ADD operation
}

void VM::execute_sub() {
    // implement the SUB operation
}

void VM::execute_mul() {
    // implement the MUL operation
}

void VM::execute_div() {
    // implement the DIV operation
}

void VM::execute_mod() {
    // implement the MOD operation
}

void VM::execute_jmp() {
    // implement the JMP operation
}

void VM::execute_jz() {
    // implement the JZ operation
}

void VM::execute_jnz() {
    // implement the JNZ operation
}

void VM::execute_call() {
    // implement the CALL operation
}

void VM::execute_ret() {
    // implement the RET operation
}

void VM::execute_push() {
    // implement the PUSH operation
}

void VM::execute_pop() {
    // implement the POP operation
}

void VM::load_segment(uint32_t base, uint32_t limit, VM::Segment &segment) {
    segment.base = base;
    segment.limit = limit;

    // For simplicity, we'll just fill this memory segment with zeros for now.
    std::fill(memory.begin() + base, memory.begin() + base + limit, 0);
}

uint32_t VM::get_physical_address(const VM::Segment &segment, uint32_t offset) const {
    if (offset > segment.limit) {
        throw MemoryAccessViolationException ("Offset is out of segment bounds");
    }
    return segment.base + offset;
}


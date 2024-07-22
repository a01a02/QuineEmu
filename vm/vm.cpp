#include "vm.hpp"
#include <algorithm>
#include <iostream>

// Constructor definition
VM::VM(size_t memory_size) : memory(memory_size, 0), registers{}, eip(0), eflags(0), halted(false) {
    opcode_handlers = {
            {0x01, &VM::execute_mov},
            {0x02, &VM::execute_add},
            {0x03, &VM::execute_sub},
            {0x04, &VM::execute_mul},
            // Include other opcodes and their handlers as and when defined.
    };
    init_memory_segments(memory_size);
}

void VM::init_memory_segments(size_t memory_size) {
    load_segment(0, memory_size / 2, data_segment);
    load_segment(memory_size / 2, memory_size / 2, stack_segment);
    // Initializes the stack pointer to the start of the stack segment.
    registers[SP] = stack_segment.base;
}

void VM::load_program(const std::vector<uint8_t>& program) {
    if(program.size() > data_segment.limit){
        throw std::runtime_error("Program size is greater than data segment capacity.");
    }
    std::copy(program.begin(), program.end(), memory.begin() + data_segment.base);
    eip = data_segment.base;  // Set the instruction pointer to the start of the program.
}

void VM::execute() {
    while(!halted) {
        decode_and_execute();
    }
}

uint8_t VM::fetch() {
    uint8_t opcode = memory[eip++];
    return opcode;
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
    uint8_t reg_index_1 = fetch();
    uint8_t reg_index_2 = fetch();

    if (reg_index_1< NUM_REGISTERS && reg_index_2 < NUM_REGISTERS) {
        registers[reg_index_1] = registers[reg_index_2]; // Copy the value from one register to another
    }
}

void VM::execute_add() {
    uint8_t reg_index_1 = fetch();
    uint8_t reg_index_2 = fetch();

    if (reg_index_1 < NUM_REGISTERS && reg_index_2 < NUM_REGISTERS) {
        uint32_t result = registers[reg_index_1] + registers[reg_index_2];
        registers[reg_index_1] = result;
    }
}

void VM::execute_sub() {
    uint8_t reg_index_1 = fetch();
    uint8_t reg_index_2 = fetch();

    if (reg_index_1 < NUM_REGISTERS && reg_index_2 < NUM_REGISTERS) {
        uint32_t result = registers[reg_index_1] - registers[reg_index_2];
        registers[reg_index_1] = result;
    }
}

void VM::execute_mul() {
    uint8_t reg_index_1 = fetch();
    uint8_t reg_index_2 = fetch();

    if (reg_index_1 < NUM_REGISTERS && reg_index_2 < NUM_REGISTERS) {
        uint32_t result = registers[reg_index_1] * registers[reg_index_2];
        registers[reg_index_1] = result;
    }
}

void VM::execute_div() {
    uint8_t reg_index_1 = fetch();
    uint8_t reg_index_2 = fetch();

    if (reg_index_1 < NUM_REGISTERS && reg_index_2 < NUM_REGISTERS) {
        if (registers[reg_index_2] == 0) {
            throw std::runtime_error("Divide by zero error");
        }
        uint32_t result = registers[reg_index_1] / registers[reg_index_2];
        registers[reg_index_1] = result;
    }
}

void VM::execute_mod() {
    uint8_t reg_index_1 = fetch();
    uint8_t reg_index_2 = fetch();

    if (reg_index_1 < NUM_REGISTERS && reg_index_2 < NUM_REGISTERS) {
        uint32_t result = registers[reg_index_1] % registers[reg_index_2];
        registers[reg_index_1] = result;
    }
}

void VM::execute_jmp() {
    uint8_t reg_index = fetch();

    if (reg_index < NUM_REGISTERS) {
        eip = registers[reg_index];
    }
}

void VM::execute_jz() {
    uint8_t reg_index = fetch();

    if (reg_index < NUM_REGISTERS) {
        if (eflags == 0) {
            eip = registers[reg_index];
        }
    }
}

void VM::execute_jnz() {
    uint8_t reg_index = fetch();

    if (reg_index < NUM_REGISTERS) {
        if (eflags != 0) {
            eip = registers[reg_index];
        }
    }
}

void VM::execute_call() {
    uint8_t reg_index = fetch();

    if (reg_index < NUM_REGISTERS) {
        // Pushes the return address onto the stack.
        memory[registers[SP]++] = eip;
        eip = registers[reg_index];
    }
}

void VM::execute_ret() {
    if (registers[SP] > 0) {
        // Pops the return address from the stack.
        eip = memory[--registers[SP]];
    }
}

void VM::execute_push() {
    uint8_t reg_index = fetch();

    if (registers[SP] >= stack_segment.limit) {
        throw std::runtime_error("Stack overflow.");
    }

    if (reg_index < NUM_REGISTERS) {
        memory[registers[SP]++] = registers[reg_index];
    }
}

void VM::execute_pop() {
    if (registers[SP] <= 0) {
        throw std::runtime_error("Stack underflow.");
    }

    uint8_t reg_index = fetch();

    if (reg_index < NUM_REGISTERS) {
        registers[reg_index] = memory[--registers[SP]];
    }
}

void VM::load_segment(uint32_t base, uint32_t limit, VM::Segment &segment) {
    segment.base = base;
    segment.limit = limit;

    // Fills this memory segment with zeros.
    std::fill(memory.begin() + base, memory.begin() + base + limit, 0);
}

uint32_t VM::get_physical_address(const VM::Segment &segment, uint32_t offset) const {
    if (offset > segment.limit) {
        throw MemoryAccessViolationException("Offset is out of segment bounds");
    }
    return segment.base + offset;
}
#include <vector>
#include <array>
#include <cstdint>
#include <iostream>

class VM {
public:
    VM(size_t memory_size);
    void load_program(const std::vector<uint8_t>)& program;
    void execute();

private:
    std::vector<uint8_t> memory;
    std::array<uint32_t, 8> registers; // EAX, EBX, ECX, EDX, ESI, EDI, EBP, ESP
    uint32_t eip; // Instruction Pointer
    uint32_t eflags; // Flags Register
    bool halted;

    struct Segment {
        uint32_t base;
        uint32_t limit;
    };

    Segment code_segment;
    Segment data_segment;
    Segment stack_segment;
    Segment extra_segment;
    Segment heap_segment;

    uint8_t fetch();
    void decode_and_execute(uint8_t opcode);

    void execute_mov();
    void execute_add();
    void execute_sub();
    void execute_jmp();
    void execute_call();
    void execute_ret();
    void execute_push();
    void execute_pop();
    // Add more methods for other instructions

    void init_memory_segments(size_t memory_size);
    uint32_t get_physical_address(Segment& segment, uint32_t offset);
};
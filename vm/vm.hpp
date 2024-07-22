#include <vector>
#include <array>
#include <cstdint>
#include <stdexcept>
#include <map>
#include <functional>

// Number of registers (or however many you need)
constexpr size_t NUM_REGISTERS = 8;
// Stack pointer index
constexpr uint8_t SP = 8;
// Enumeration representing each register
enum class Register {
    EAX,
    EBX,
    ECX,
    EDX,
    ESI,
    EDI,
    EBP,
    ESP,
    NUM_REGISTERS = ::NUM_REGISTERS // Total number of registers
};

class VM {
public:
    // Constructor that initializes the virtual machine with given memory size
    VM(size_t memory_size);

    // Load program into VM's memory
    // program: the binary code of the program as a byte vector
    void load_program(const std::vector<uint8_t>& program);

    // Start executing loaded program
    void execute();

private:
    // Structure representing a memory segment (code, data, stack, extra, heap)
    struct Segment {
        uint32_t base;
        uint32_t limit;
    };

    // Function pointer type for handling specific opcodes
    using OpcodeHandler = void (VM::*)();

    // VM's main memory
    std::vector<uint8_t> memory;
    // Array of CPU registers
    std::array<uint32_t, NUM_REGISTERS> registers;
    uint32_t eip = 0; // Instruction Pointer
    uint32_t eflags = 0; // Flags Register
    // Halt flag - VM stops execution when this is set
    bool halted = false;

    // Memory segment definitions
    Segment code_segment;
    Segment data_segment;
    Segment stack_segment;
    Segment extra_segment;
    Segment heap_segment;

    // Map of opcode handlers
    std::map<uint8_t, OpcodeHandler> opcode_handlers;

    // Fetch the instruction's opcode
    uint8_t fetch();
    // Decode and execute the instruction
    void decode_and_execute();

    // Handler functions for each instruction opcode
    void execute_mov();
    void execute_add();
    void execute_sub();
    void execute_mul();
    void execute_div();
    void execute_mod();
    void execute_jmp();
    void execute_jz();
    void execute_jnz();
    void execute_call();
    void execute_ret();
    void execute_push();
    void execute_pop();
    // ... Other opcode handlers may be needed.
    void execute_and();
    void execute_or();
    void execute_not();
    void execute_xor();
    void execute_shl();
    void execute_shr();


    // Load a memory segment
    void load_segment(uint32_t base, uint32_t limit, Segment& segment);
    // Initialize memory segments based on memory size
    void init_memory_segments(size_t memory_size);
    // Calculate the physical address based on a segment and an offset
    uint32_t get_physical_address(const Segment& segment, uint32_t offset) const;

    // Exception class for runtime memory access violations
    class MemoryAccessViolationException : public std::runtime_error {
        public:
            // Constructor that initializes the exception with a message
            MemoryAccessViolationException(const std::string& msg) : std::runtime_error(msg) {}
    };
};
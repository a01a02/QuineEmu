# QuineISA
An experiment to see how far I can into Custom Computing without being filtered. ISA -> VM -> Compilation -> Network Execution Layer

# Project Structure
vm/: VM implementation in C++23.

assembler/: Assembler to convert assembly to machine code.

compiler/: Custom compiler from high-level language to assembly.

examples/: Example programs written in your custom language.

# Project Flow
1. Define the Architecture:
   - Decide on the instruction set architecture (ISA) for our VM.
   - Specify any registers, memory layout, and special hardware our VM will emulate.
2. Instruction Set Design:
   - Design a set of instructions that our VM will support.
   - Create an assembly language for our custom machine.
3. Implement the VM:
   - Implement VM in C++23. This involves needed to create a interpreter or JIT compiler for our ISA.
   - Implement the necessary components such as I/O, memory, and CPU handling.
4. Build the Assembler:
   - Create an assembler that converts our custom assembly language into machine code for our VM.
5. Develop the Custom Compiler:
   - Design a high-level language similar to C++.
   - Implement a compiler that translates this high-level language into our custom assembly language.
6. Networking and Servers:
   - Implement networking capabilities within our VM.
   - Provide libraries or frameworks in our custom language for network pramming and server management.

# Steps in Detail
1. Define the Architecture
   Let's start by Defining the specifications of our virtual machine.
   - Registers: Define the number and type of registers (e.g., general-purpose, special-purpose).
   - Memory: Decide on the memory model, including stack, heap, and memory-mapped I/O.
   - Instructions: Specify the format and types of instruction (e.g. arithmetic, control flow, I/O). 

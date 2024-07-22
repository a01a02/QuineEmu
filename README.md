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

# Testing
Testing:
Testing will be of crucial importance given the intricacy and precision required for this project.
Here's a plan on how we might go about it:

Unit Tests: Create unit tests for each function or method in your system. Ensure that every piece of your system is performing as expected in isolation.

Integration Tests: Once your units are tested independently, ensure that they work correctly when combined. Test your interfaces and interaction between modules.

End-to-end Tests: Once every component of the system has been tested and integrated, test the entire system from start to finish. This should include testing:

Instruction Set:  Verify that all instructions are executed correctly by running extensive assembly language programs.

VM: Run extensive test suites to verify that the VM correctly handles a variety of programs.

Compiler: Create a suite of programs in your high-level language, compile them, and run them on your VM to ensure that every aspect of your language is being correctly translated to assembly and executed on the VM.

Networking Layer: Verify that the VM is capable of correctly sending and receiving network packets through unit tests and by running server programs within the VM.

This rigorous approach to testing will ensure that every component of the system is working correctly individually and when combined into the larger system. Regular execution of these tests throughout the development process can catch bugs early and facilitate easier debugging.

# Steps in Detail
1. Define the Architecture
   Let's start by Defining the specifications of our virtual machine.
   - Registers: Define the number and type of registers (e.g., general-purpose, special-purpose).
   - Memory: Decide on the memory model, including stack, heap, and memory-mapped I/O.
   - Instructions: Specify the format and types of instruction (e.g. arithmetic, control flow, I/O). 

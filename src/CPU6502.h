#pragma once
#include <array>
#include <memory>
#include <cstdint>

constexpr int32_t MEMORY_SIZE = 65536;

class CPU6502 {
    public:
        CPU6502(std::shared_ptr<std::array<uint8_t, MEMORY_SIZE>> memory) : _memory{memory} {};
        bool execute_instruction();
        uint8_t A() { return _A; };
        uint8_t X() { return _X; };
        uint8_t Y() { return _Y; };
        uint8_t P() { return _P; };
        uint16_t PC() { return _PC.PC; };
        uint8_t PCL() { return _PC.PCX[0]; };
        uint8_t PCH() { return _PC.PCX[1]; };
        uint8_t S() { return _S; };
    private:
        // Memory 
        std::shared_ptr<std::array<uint8_t, MEMORY_SIZE>> _memory;
        // Registers
        uint8_t _A = 0; // Accumulator
        uint8_t _X = 0; // Index register X
        uint8_t _Y = 0; // Index register Y
        uint8_t _P = 0; // CPU Status register
        union {
            uint8_t PCX[2];
            uint16_t PC;
        } _PC = {0}; // Program Counter
        uint8_t _S = 0; // Stack Pointer Register 
        // Addressing Modes
        uint8_t imediate();
        uint8_t absolute();
        uint8_t absolute_X();
        uint8_t absolute_Y();
        uint8_t zeropage();
        uint8_t zeropage_X();
        uint8_t zeropage_Y();
        uint8_t zeropage_X_ptr();
        uint8_t zeropage_ptr_Y();
        // Opcodes
        void BRK();

};

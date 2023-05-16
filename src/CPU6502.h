#pragma once
#include <array>
#include <memory>
#include <cstdint>
#include <sys/types.h>

constexpr int32_t MEMORY_SIZE = 65536;

class CPU6502 {
    public:
        CPU6502(std::shared_ptr<std::array<uint8_t, MEMORY_SIZE>> memory, uint16_t entry_point) : 
            _memory{memory} 
        {
            _PC.PC = entry_point;
        };
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
        uint8_t _S = 0x00; // Stack Pointer Register 
        // Addressing Modes
        uint8_t imediate();
        uint16_t imediate_16();
        uint8_t& absolute();
        uint16_t absolute_16();
        uint8_t& absolute_X();
        uint8_t& absolute_Y();
        uint8_t& zeropage();
        uint8_t& zeropage_X();
        uint8_t& zeropage_Y();
        uint8_t& zeropage_X_ptr();
        uint8_t& zeropage_ptr_Y();
        // Flag Manipulation
        void set_flags(uint8_t value, uint8_t mask);
        // Opcodes
        void ADC(uint8_t value);
        void AND(uint8_t value);
        void ASL(uint8_t& value);
        void BIT(uint8_t value);
        void BPL(uint8_t value);
        void BMI(uint8_t value);
        void BVC(uint8_t value);
        void BVS(uint8_t value);
        void BCC(uint8_t value);
        void BCS(uint8_t value);
        void BNE(uint8_t value);
        void BEQ(uint8_t value);
        void BRK();
        void CMP(uint8_t value);
        void CPX(uint8_t value);
        void CPY(uint8_t value);
        void DEC(uint8_t& value);
        void EOR(uint8_t value);
        void CLC();
        void SEC();
        void CLI();
        void SEI();
        void CLV();
        void CLD();
        void SED();
        void INC(uint8_t& value);
        void JMP(uint16_t value);
        void JSR(uint16_t value);
        void LDA(uint8_t value);
        void LDX(uint8_t value);
        void LDY(uint8_t value);
        void LSR(uint8_t& value);
        void NOP();
        void ORA(uint8_t value);
        void TAX();
        void TXA();
        void DEX();
        void INX();
        void TAY();
        void TYA();
        void DEY();
        void INY();
        void ROL(uint8_t& value);
        void ROR(uint8_t& value);
        void RTI();
        void RTS();
        void SBC(uint8_t value);
        void STA(uint8_t& value);
        void STX(uint8_t& value);
        void STY(uint8_t& value);
        void TXS();
        void TSX();
        void PHA();
        void PLA();
        void PHP();
        void PLP();
};

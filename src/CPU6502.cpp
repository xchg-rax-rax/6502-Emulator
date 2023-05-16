#include "CPU6502.h"
#include <cstdint>
#include <cstdio>
#include <iostream>

constexpr uint8_t N_FLAG = 0x80; // Negative Flag
constexpr uint8_t V_FLAG = 0x40; // Overflow Flag
constexpr uint8_t U_FLAG = 0x20; // Unused 
constexpr uint8_t B_FLAG = 0x10; // Break Flag
constexpr uint8_t D_FLAG = 0x08; // Decimal Flag (use BCD for arithmetic)
constexpr uint8_t I_FLAG = 0x04; // Interrupt Flag (IRQ disable)
constexpr uint8_t Z_FLAG = 0x02; // Zero Flag
constexpr uint8_t C_FLAG = 0x01; // Carry

constexpr uint16_t STACK_OFFSET = 0x100;
constexpr uint16_t NMI_VECTOR_OFFSET = 0xFFFA;
constexpr uint16_t RES_VECTOR_OFFSET = 0xFFFC;
constexpr uint16_t IRQ_VECTOR_OFFSET = 0xFFFE;

bool CPU6502::execute_instruction() {
    uint8_t opcode = (*_memory)[_PC.PC];
    _PC.PC++;
    switch (opcode) {
        case 0x00:
            BRK();
            break;
        case 0x01:
            ORA(zeropage_X_ptr());
            break;
        case 0x05:
            ORA(zeropage());
            break;
        case 0x06:
            ASL(zeropage());
            break;
        case 0x08:
            PHP();
            break;
        case 0x09:
            ORA(imediate());
            break;
        case 0x0A:
            ASL(_A);
            break;
        case 0x0D:
            ORA(absolute());
            break;
        case 0x0E:
            ASL(absolute());
            break;
        case 0x10:
            BPL(imediate());
            break;
        case 0x11:
            ORA(zeropage_ptr_Y());
            break;
        case 0x15:
            ORA(zeropage_X());
            break;
        case 0x16:
            ASL(zeropage_X());
            break;
        case 0x18:
            CLC();
            break;
        case 0x19:
            ORA(absolute_Y());
            break;
        case 0x1D:
            ORA(absolute_X());
            break;
        case 0x1E:
            ASL(absolute_X());
            break;
        case 0x20:
            JSR(imediate_16());
            break;
        case 0x21:
            AND(zeropage_X_ptr());
            break;
        case 0x24:
            BIT(zeropage());
            break;
        case 0x25:
            AND(zeropage());
            break;
        case 0x26:
            ROL(zeropage());
            break;
        case 0x28:
            PLP();
            break;
        case 0x29:
            AND(imediate());
            break;
        case 0x2A:
            ROL(_A);
            break;
        case 0x2C:
            BIT(absolute());
            break;
        case 0x2D:
            AND(absolute());
            break;
        case 0x2E:
            ROL(absolute());
            break;
        case 0x30:
            BMI(imediate());
            break;
        case 0x31:
            AND(zeropage_ptr_Y());
            break;
        case 0x35:
            AND(zeropage_X());
            break;
        case 0x36:
            ROL(zeropage_X());
            break;
        case 0x38:
            SEC();
            break;
        case 0x39:
            AND(absolute_Y());
            break;
        case 0x3E:
            ROL(absolute_X());
            break;
        case 0x3D:
            AND(absolute_X());
            break;
        case 0x40:
            RTI();
            break;
        case 0x41:
            EOR(zeropage_X_ptr());
            break;
        case 0x45:
            EOR(zeropage());
            break;
        case 0x46:
            LSR(zeropage());
            break;
        case 0x48:
            PHA();
            break;
        case 0x4A:
            LSR(_A);
            break;
        case 0x4C:
            JMP(imediate_16());
            break;
        case 0x4D:
            EOR(absolute());
            break;
        case 0x4E:
            LSR(absolute());
            break;
        case 0x49:
            EOR(imediate());
            break;
        case 0x50:
            BVC(imediate());
            break;
        case 0x51:
            EOR(zeropage_ptr_Y());
            break;
        case 0x55:
            EOR(zeropage_X());
            break;
        case 0x56:
            LSR(zeropage_X());
            break;
        case 0x58:
            CLI();
            break;
        case 0x59:
            EOR(absolute_Y());
            break;
        case 0x5D:
            EOR(absolute_X());
            break;
        case 0x5E:
            LSR(absolute_X());
            break;
        case 0x60:
            RTS();
            break;
        case 0x61:
            ADC(zeropage_X_ptr());
            break;
        case 0x65:
            ADC(zeropage());
            break;
        case 0x66:
            ROR(zeropage());
            break;
        case 0x68:
            PLA();
            break;
        case 0x69:
            ADC(imediate());
            break;
        case 0x6A:
            ROR(_A);
            break;
        case 0x6C:
            JMP(absolute_16());
            break;
        case 0x6D:
            ADC(absolute());
            break;
        case 0x6E:
            ROR(absolute());
            break;
        case 0x70:
            BVS(imediate());
            break;
        case 0x71:
            ADC(zeropage_ptr_Y());
            break;
        case 0x75:
            ADC(zeropage_X());
            break;
        case 0x76:
            ROR(zeropage_X());
            break;
        case 0x78:
            SEI();
            break;
        case 0x79:
            ADC(absolute_Y());
            break;
        case 0x7D:
            ADC(absolute_X());
            break;
        case 0x7E:
            ROR(absolute_X());
            break;
        case 0x81:
            STA(zeropage_X_ptr());
            break;
        case 0x84:
            STY(zeropage());
            break;
        case 0x85:
            STA(zeropage());
            break;
        case 0x86:
            STX(zeropage());
            break;
        case 0x88:
            DEY();
            break;
        case 0x8A:
            TXA();
            break;
        case 0x8C:
            STY(absolute());
            break;
        case 0x8D:
            STA(absolute());
            break;
        case 0x8E:
            STX(absolute());
            break;
        case 0x90:
            BCC(imediate());
            break;
        case 0x91:
            STA(zeropage_ptr_Y());
            break;
        case 0x94:
            STY(zeropage_X());
            break;
        case 0x95:
            STA(zeropage_X());
            break;
        case 0x96:
            STX(zeropage_Y());
            break;
        case 0x98:
            TYA();
            break;
        case 0x99:
            STA(absolute_Y());
            break;
        case 0x9A:
            TXS();
            break;
        case 0x9D:
            STA(absolute_X());
            break;
        case 0xA0:
            LDY(imediate());
            break;
        case 0xA1:
            LDA(zeropage_X_ptr());
            break;
        case 0xA2:
            LDX(imediate());
            break;
        case 0xA4:
            LDY(zeropage());
            break;
        case 0xAA:
            TAX();
            break;
        case 0xAD:
            LDA(absolute());
            break;
        case 0xA5:
            LDA(zeropage());
            break;
        case 0xA6:
            LDX(zeropage());
            break;
        case 0xA8:
            TAY();
            break;
        case 0xA9:
            LDA(imediate());
            break;
        case 0xAC:
            LDY(absolute());
            break;
        case 0xAE:
            LDX(absolute());
            break;
        case 0xB0:
            BCS(imediate());
            break;
        case 0xB1:
            LDA(zeropage_ptr_Y());
            break;
        case 0xB4:
            LDY(zeropage_X());
            break;
        case 0xB8:
            CLV();
            break;
        case 0xBA:
            TSX();
            break;
        case 0xBC:
            LDY(absolute_X());
            break;
        case 0xBD:
            LDA(absolute_X());
            break;
        case 0xB5:
            LDA(zeropage_X());
            break;
        case 0xB6:
            LDX(zeropage_Y());
            break;
        case 0xB9:
            LDA(absolute_Y());
            break;
        case 0xBE:
            LDX(absolute_Y());
            break;
        case 0xC0:
            CPY(imediate());
            break;
        case 0xC1:
            CMP(zeropage_X_ptr());
            break;
        case 0xC4:
            CPY(zeropage());
            break;
        case 0xC5:
            CMP(zeropage());
            break;
        case 0xC6:
            DEC(zeropage());
            break;
        case 0xC8:
            INY();
            break;
        case 0xCA:
            DEX();
            break;
        case 0xCC:
            CPY(absolute());
            break;
        case 0xCD:
            CMP(absolute());
            break;
        case 0xCE:
            DEC(absolute());
            break;
        case 0xC9:
            CMP(imediate());
            break;
        case 0xD0:
            BNE(imediate());
            break;
        case 0xD1:
            CMP(zeropage_ptr_Y());
            break;
        case 0xD5:
            CMP(zeropage_X());
            break;
        case 0xD6:
            DEC(zeropage_X());
            break;
        case 0xD8:
            CLD();
            break;
        case 0xD9:
            CMP(absolute_Y());
            break;
        case 0xDD:
            CMP(absolute_X());
            break;
        case 0xDE:
            DEC(absolute_X());
            break;
        case 0xE0:
            CPX(imediate());
            break;
        case 0xE1:
            SBC(zeropage_X_ptr());
            break;
        case 0xE4:
            CPX(zeropage());
            break;
        case 0xE5:
            SBC(zeropage());
            break;
        case 0xE6:
            INC(zeropage());
            break;
        case 0xE8:
            INX();
            break;
        case 0xE9:
            SBC(imediate());
            break;
        case 0xEA:
            NOP();
            break;
        case 0xEC:
            CPX(absolute());
            break;
        case 0xED:
            SBC(absolute());
            break;
        case 0xEE:
            INC(absolute());
            break;
        case 0xF0:
            BEQ(imediate());
            break;
        case 0xF1:
            SBC(zeropage_ptr_Y());
            break;
        case 0xF5:
            SBC(zeropage_X());
            break;
        case 0xF6:
            INC(zeropage_X());
            break;
        case 0xF8:
            SED();
            break;
        case 0xF9:
            SBC(absolute_Y());
            break;
        case 0xFD:
            SBC(absolute_X());
            break;
        case 0xFE:
            INC(absolute_X());
            break;
        default:
            printf("Invalid Opcode 0x%02x\n", opcode);
            return false;
    }
    return true;
}

// Addressing Modes

uint8_t CPU6502::imediate() {
    uint8_t value = (*_memory)[_PC.PC];
    _PC.PC++;
    return value;
}

uint16_t CPU6502::imediate_16() {
    uint8_t value_l = (*_memory)[_PC.PC];
    _PC.PC++;
    uint8_t value_u = (*_memory)[_PC.PC];
    _PC.PC++;
    uint16_t value = (value_u << 8) + value_l;
    return value;
}

uint8_t& CPU6502::absolute() {
    uint8_t addr_l = (*_memory)[_PC.PC];
    _PC.PC++;
    uint8_t addr_u = (*_memory)[_PC.PC];
    _PC.PC++;
    uint16_t addr = (addr_u << 8) + addr_l;
    return (*_memory)[addr];
}

uint16_t CPU6502::absolute_16() {
    uint8_t addr_l = (*_memory)[_PC.PC];
    _PC.PC++;
    uint8_t addr_u = (*_memory)[_PC.PC];
    _PC.PC++;
    uint16_t addr = (addr_u << 8) + addr_l;
    uint8_t value_l = (*_memory)[addr];
    uint8_t value_h = (*_memory)[addr+1];
    uint16_t value = (value_h << 8) + value_l;
    return value;
}

uint8_t& CPU6502::absolute_X() {
    uint8_t addr_l = (*_memory)[_PC.PC];
    _PC.PC++;
    uint8_t addr_u = (*_memory)[_PC.PC];
    _PC.PC++;
    uint16_t addr = (addr_u << 8) + addr_l;
    return (*_memory)[addr+_X];
}

uint8_t& CPU6502::absolute_Y() {
    uint8_t addr_l = (*_memory)[_PC.PC];
    _PC.PC++;
    uint8_t addr_u = (*_memory)[_PC.PC];
    _PC.PC++;
    uint16_t addr = (addr_u << 8) + addr_l;
    return (*_memory)[addr+_Y];
}

uint8_t& CPU6502::zeropage() {
    uint16_t addr = (*_memory)[_PC.PC];
    _PC.PC++;
    return (*_memory)[addr];
}

uint8_t& CPU6502::zeropage_X() {
    uint8_t addr = ((*_memory)[_PC.PC]+_X) & 0xFF;
    _PC.PC++;
    return (*_memory)[addr];
}

uint8_t& CPU6502::zeropage_Y() {
    uint8_t addr = ((*_memory)[_PC.PC]+_Y) & 0xFF;
    _PC.PC++;
    return (*_memory)[addr];
}

uint8_t& CPU6502::zeropage_X_ptr() {
    uint8_t ptr = ((*_memory)[_PC.PC]+_X) & 0xFF;
    _PC.PC++;
    uint8_t addr_l = (*_memory)[ptr];
    uint8_t addr_u = (*_memory)[ptr+1];
    uint16_t addr = (addr_u << 8) + addr_l;
    return (*_memory)[addr];
}

uint8_t& CPU6502::zeropage_ptr_Y() {
    uint8_t ptr = (*_memory)[_PC.PC]; 
    _PC.PC++;
    uint8_t addr_l = (*_memory)[ptr];
    uint8_t addr_u = (*_memory)[ptr+1];
    uint16_t addr = (addr_u << 8) + addr_l + _Y;
    return (*_memory)[addr];
}

// Flag Manipulation
//
void CPU6502::set_flags(uint8_t value, uint8_t mask) {
    if ((mask & N_FLAG)) {
        _P = (_P & ~N_FLAG) | ((value & 0x80) ? N_FLAG : 0);
    }
    if ((mask & Z_FLAG)) {
        _P = (_P & ~Z_FLAG) | ((value == 0) ? Z_FLAG : 0);
    }
}

// Instructions

void CPU6502::ADC(uint8_t value) {
    //printf("A = %02x, M = %02x, C = %02x\n", _A, value, _P & C_FLAG);
    uint16_t result = _A + value + ((_P & C_FLAG) ? 1 : 0);
    bool byte_overflowed = (result > 0xFF);
    _P = (_P & ~C_FLAG) | (byte_overflowed ? C_FLAG : 0);
    bool sign_changed = !((_A ^ value) & 0x80) && ((_A ^ (uint8_t)result) & 0x80);
    //printf("Sign Changed %d\n", sign_changed);
    _P = (_P & ~V_FLAG) | (sign_changed ? V_FLAG : 0);
    _A = result;
    set_flags(_A, N_FLAG | Z_FLAG);
}

void CPU6502::AND(uint8_t value) {
    _A &= value;
    set_flags(_A, N_FLAG | Z_FLAG);
}

void CPU6502::ASL(uint8_t& value) {
    _P = (0x80 & value) ? _P|C_FLAG : _P & ~C_FLAG;
    value <<= 1;
    set_flags(value, N_FLAG | Z_FLAG);
}

void CPU6502::BCC(uint8_t value) {
    if (!(_P & C_FLAG)) {
        _PC.PC += (int8_t) value;
    }
}

void CPU6502::BCS(uint8_t value) {
    if (_P & C_FLAG) {
        _PC.PC += (int8_t) value;
    }
}

void CPU6502::BEQ(uint8_t value) {
    if (_P & Z_FLAG) {
        _PC.PC += (int8_t) value;
    }
}

void CPU6502::BIT(uint8_t value) {
    uint8_t mask = (N_FLAG | V_FLAG);
    _P = (_P & ~mask) | (value & mask);
    set_flags(_A & value, Z_FLAG);
}

void CPU6502::BMI(uint8_t value) {
    if (_P & N_FLAG) {
        _PC.PC += (int8_t) value;
    }
}

void CPU6502::BNE(uint8_t value) {
    if (!(_P & Z_FLAG)) {
        _PC.PC += (int8_t) value;
    }
}

void CPU6502::BPL(uint8_t value) {
    if (!(_P & N_FLAG)) {
        _PC.PC += (int8_t) value;
    }
}

// this instruction is fubar
void CPU6502::BRK() {
    _PC.PC++; // BRK is a two byte instructions, no matter what they say
    (*_memory)[STACK_OFFSET + _S] = _PC.PCX[0];
    _S--;
    (*_memory)[STACK_OFFSET + _S] = _PC.PCX[1];
    _S--;
    (*_memory)[STACK_OFFSET + _S] = _P | B_FLAG;
    _S--;
    _PC.PCX[0] = (*_memory)[NMI_VECTOR_OFFSET]; // I know it's a NMI, don't ask
    _PC.PCX[1] = (*_memory)[NMI_VECTOR_OFFSET+1]; // I know it's a NMI, don't ask
    _P |= I_FLAG;
}

void CPU6502::BVC(uint8_t value) {
    if (!(_P & V_FLAG)) {
        _PC.PC += (int8_t) value;
    }
}

void CPU6502::BVS(uint8_t value) {
    if (_P & V_FLAG) {
        _PC.PC += (int8_t) value;
    }
}

void CPU6502::CLC() {
    _P &= ~(C_FLAG);
}

void CPU6502::CLD() {
    _P &= ~(D_FLAG);
}

void CPU6502::CLI() {
    _P &= ~(I_FLAG);
}

void CPU6502::CLV() {
    _P &= ~(V_FLAG);
}

void CPU6502::CMP(uint8_t value) {
    uint8_t result = _A - value;
    _P = (_P & ~C_FLAG) | (_A >= value ? 1 : 0);
    set_flags(result, N_FLAG | Z_FLAG);
}

void CPU6502::CPX(uint8_t value) {
    uint8_t result = _X - value;
    _P = (_P & ~C_FLAG) | (_X >= value ? 1 : 0);
    set_flags(result, N_FLAG | Z_FLAG);
}

void CPU6502::CPY(uint8_t value) {
    uint8_t result = _Y - value;
    _P = (_P & ~C_FLAG) | (_Y >= value ? 1 : 0);
    set_flags(result, N_FLAG | Z_FLAG);
}

void CPU6502::DEC(uint8_t& value) {
    value--;
    set_flags(value, N_FLAG | Z_FLAG);
}

void CPU6502::DEX() {
    _X--;
    set_flags(_X, N_FLAG | Z_FLAG);
}

void CPU6502::DEY() {
    _Y--;
    set_flags(_Y, N_FLAG | Z_FLAG);
}

void CPU6502::EOR(uint8_t value) {
    _A ^= value;
    set_flags(_A, N_FLAG | Z_FLAG);
}

void CPU6502::INC(uint8_t& value) {
    value = (int8_t) value + 1;
    set_flags(value, N_FLAG | Z_FLAG);
}

void CPU6502::INX() {
    _X = (int8_t) _X +1;
    set_flags(_X, N_FLAG | Z_FLAG);
}

void CPU6502::INY() {
    _Y = (int8_t) _Y +1;
    set_flags(_Y, N_FLAG | Z_FLAG);
}

void CPU6502::JMP(uint16_t value) {
    _PC.PC = value;
}

void CPU6502::JSR(uint16_t value) {
    (*_memory)[STACK_OFFSET + _S] = _PC.PCX[1];
    _S--;
    (*_memory)[STACK_OFFSET + _S] = _PC.PCX[0]-1;
    _S--;
    _PC.PC = value;
}

void CPU6502::LDA(uint8_t value) {
    _A = value;
    set_flags(_A, N_FLAG | Z_FLAG);
}

void CPU6502::LDX(uint8_t value) {
    _X = value;
    set_flags(_X, N_FLAG | Z_FLAG);
}

void CPU6502::LDY(uint8_t value) {
    _Y = value;
    set_flags(_Y, N_FLAG | Z_FLAG);
}

void CPU6502::LSR(uint8_t& value) {
    _P = (0x1 & value) ? _P|C_FLAG : _P & ~C_FLAG;
    value = (value >> 1);
    set_flags(value, N_FLAG | Z_FLAG);
}

void CPU6502::NOP() {
    // nope
}

void CPU6502::ORA(uint8_t value) {
    _A |= value;
    set_flags(_A, N_FLAG | Z_FLAG);
}

void CPU6502::PHA() {
    (*_memory)[STACK_OFFSET + _S] = _A;
    _S--;
}

void CPU6502::PHP() {
    (*_memory)[STACK_OFFSET + _S] = (_P | B_FLAG | U_FLAG);
    _S--;
}

void CPU6502::PLA() {
    _S++;
    _A = (*_memory)[STACK_OFFSET + _S];
    set_flags(_A, N_FLAG | Z_FLAG);
}

void CPU6502::PLP() {
    _S++;
    _P = (*_memory)[STACK_OFFSET + _S];// & ~(B_FLAG | U_FLAG);
}

void CPU6502::ROL(uint8_t& value) {
    bool C_old = _P & C_FLAG; 
    _P = (0x80 & value) ? (_P | C_FLAG) : (_P & ~C_FLAG);
    value = (value << 1) + (C_old ? 1 : 0);
    set_flags(value, N_FLAG | Z_FLAG);
}

void CPU6502::ROR(uint8_t& value) {
    bool C_old = _P & C_FLAG; 
    _P = (0x1 & value) ? _P|C_FLAG : _P & ~C_FLAG;
    value = (value >> 1) + (C_old ? 0x80 : 0);
    set_flags(value, N_FLAG | Z_FLAG);
}

void CPU6502::RTI() {
    _S++;
    _P = (*_memory)[STACK_OFFSET + _S] & ~(B_FLAG | U_FLAG);
    _S++;
    uint8_t addr_l = (*_memory)[STACK_OFFSET + _S];
    _S++;
    uint8_t addr_u = (*_memory)[STACK_OFFSET + _S];
    uint16_t addr = (addr_u << 8) + addr_l;
    _PC.PC = addr;
}

void CPU6502::RTS() {
    _S++;
    uint8_t addr_l = (*_memory)[STACK_OFFSET + _S];
    _S++;
    uint8_t addr_u = (*_memory)[STACK_OFFSET + _S];
    uint16_t addr = (addr_u << 8) + addr_l;
    _PC.PC = addr + 1;
}

void CPU6502::SBC(uint8_t value) {
    //printf("A = %02x, M = %02x, C = %02x\n", _A, value, _P & C_FLAG);
    uint16_t result = (uint16_t) (_A & 0xFF) - (value & 0xFF) - ((_P & C_FLAG) ? 0  : 1);
    //printf("result = %02x\n", result);
    // Flag setting Mostly copy and pasted form ADC, probably also mostly wrong...
    bool byte_overflowed = result < 0x100;
    //printf("Byte Overflowed %d\n", byte_overflowed);
    _P = (_P & ~C_FLAG) | (byte_overflowed ? C_FLAG : 0);
    bool sign_changed = ((_A ^ value) & 0x80) && ((_A ^ (uint8_t)result) & 0x80);
    //printf("Sign Changed %d\n", sign_changed);
    _P = (_P & ~V_FLAG) | (sign_changed ? V_FLAG : 0);
    set_flags(result, N_FLAG | Z_FLAG);
    _A = result;
}

void CPU6502::SEC() {
    _P |= C_FLAG;
}

void CPU6502::SED() {
    _P |= D_FLAG;
}

void CPU6502::SEI() {
    _P |= I_FLAG;
}

void CPU6502::STA(uint8_t& value) {
    value = _A;
}

void CPU6502::STX(uint8_t& value) {
    value = _X;
}

void CPU6502::STY(uint8_t& value) {
    value = _Y;
}

void CPU6502::TAX() {
    _X = _A;
    set_flags(_X, N_FLAG | Z_FLAG);
}

void CPU6502::TAY() {
    _Y = _A;
    set_flags(_Y, N_FLAG | Z_FLAG);
}

void CPU6502::TSX() {
    _X = _S;
    set_flags(_X, N_FLAG | Z_FLAG);
}

void CPU6502::TXA() {
    _A = _X;
    set_flags(_A, N_FLAG | Z_FLAG);
}

void CPU6502::TXS() {
    _S = _X;
}

void CPU6502::TYA() {
    _A = _Y;
    set_flags(_A, N_FLAG | Z_FLAG);
}


#include "CPU6502.h"
#include <cstdint>

bool CPU6502::execute_instruction() {
    uint8_t opcode = (*_memory)[_PC.PC];
    _PC.PC++;
    switch (opcode) {
        case 0x00:
            BRK();
            break;
        default:
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

uint8_t CPU6502::absolute() {
    uint8_t addr_l = (*_memory)[_PC.PC];
    _PC.PC++;
    uint8_t addr_u = (*_memory)[_PC.PC];
    _PC.PC++;
    uint16_t addr = (addr_u << 8) + addr_l;
    return (*_memory)[addr];
}

uint8_t CPU6502::absolute_X() {
    uint8_t addr_l = (*_memory)[_PC.PC];
    _PC.PC++;
    uint8_t addr_u = (*_memory)[_PC.PC];
    _PC.PC++;
    uint16_t addr = (addr_u << 8) + addr_l;
    return (*_memory)[addr+_X];
}

uint8_t CPU6502::absolute_Y() {
    uint8_t addr_l = (*_memory)[_PC.PC];
    _PC.PC++;
    uint8_t addr_u = (*_memory)[_PC.PC];
    _PC.PC++;
    uint16_t addr = (addr_u << 8) + addr_l;
    return (*_memory)[addr+_Y];
}

uint8_t CPU6502::zeropage() {
    uint16_t addr = (*_memory)[_PC.PC];
    _PC.PC++;
    return (*_memory)[addr];
}

uint8_t CPU6502::zeropage_X() {
    uint8_t addr = ((*_memory)[_PC.PC]+_X) & 0xFF;
    _PC.PC++;
    return (*_memory)[addr];
}

uint8_t CPU6502::zeropage_Y() {
    uint8_t addr = ((*_memory)[_PC.PC]+_Y) & 0xFF;
    _PC.PC++;
    return (*_memory)[addr];
}

uint8_t CPU6502::zeropage_X_ptr() {
    uint8_t ptr = ((*_memory)[_PC.PC]+_X) & 0xFF;
    _PC.PC++;
    uint8_t addr_l = (*_memory)[ptr];
    uint8_t addr_u = (*_memory)[ptr+1];
    uint16_t addr = (addr_u << 8) + addr_l;
    return (*_memory)[addr];
}

uint8_t CPU6502::zeropage_ptr_Y() {
    uint8_t ptr = (*_memory)[_PC.PC]; 
    _PC.PC++;
    uint8_t addr_l = (*_memory)[ptr];
    uint8_t addr_u = (*_memory)[ptr+1];
    uint16_t addr = (addr_u << 8) + addr_l + _Y;
    return (*_memory)[addr];
}



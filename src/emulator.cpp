#include <array>
#include <vector>
#include <chrono>
#include <thread>
#include <memory>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <iterator>

#include <stdio.h>

#include "CPU6502.h"

void dump_memory_page(std::shared_ptr<std::array<uint8_t, MEMORY_SIZE>> memory, uint16_t offset) {
    for (int i = 0; i < 0x100; i++) {
        printf("%02x ", (*memory)[offset + i]);
        if (i % 0x10 == 0xF) {
            puts("");
        }
    }
}

int main(int argc, char**argv) {
    std::cout << "6502 Emulator" << std::endl;
    if (argc != 2) {
        std::cout << "Usage : " << argv[0] << " <path to rom>" << std::endl;
        exit(1);
    }
    std::ifstream file(argv[1], std::ios::in | std::ios::binary);
    if (!file) {
        std::cout << "Could not open ROM file: " << argv[1] << std::endl;
        exit(1);
    }
    auto memory = std::make_shared<std::array<uint8_t, MEMORY_SIZE>>();
    file.read(reinterpret_cast<char*>(memory->data()+0xa), MEMORY_SIZE);
    auto cpu = CPU6502(memory, 0x400);
    dump_memory_page(memory, 0x400);
    printf("A:%02x X:%02x Y:%02x P:%02x SP:%02x PC:%04x OP:%02x\n", cpu.A(), cpu.X(), cpu.Y(), cpu.P(), cpu.S(), cpu.PC(), (*memory)[cpu.PC()]);
    auto old_PC = cpu.PC();
    while(cpu.execute_instruction()) {
        if (cpu.PC() == old_PC) {
            printf("A:%02x X:%02x Y:%02x P:%02x SP:%02x PC:%04x OP:%02x rLSR + X :%02x fLSR + X:%02x\n", cpu.A(), cpu.X(), cpu.Y(), cpu.P(), cpu.S(), cpu.PC(), (*memory)[cpu.PC()], (*memory)[0x022d + cpu.X()], (*memory)[0x0245+ cpu.X()]);
            dump_memory_page(memory, 0x0000);
            dump_memory_page(memory, 0x0100);
            break;
        }
        // When it comes time we can tweak this so we get a reasonable clock speed
        // for now it can run arbitrarily fast
        // std::this_thread::sleep_for(std::chrono::milliseconds(1));
        old_PC = cpu.PC();
    }
    return 0;
}

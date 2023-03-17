#include <array>
#include <chrono>
#include <thread>
#include <memory>
#include <cstdint>
#include <iostream>

#include "CPU6502.h"

int main(int argc, char**argv) {
    std::cout << "6502 Emulator" << std::endl;
    auto memory = std::make_shared<std::array<uint8_t, MEMORY_SIZE>>();
    auto cpu = CPU6502(memory);
    while(cpu.execute_instruction()) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
    return 0;
}

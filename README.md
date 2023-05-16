# 6502-Emulator
A working emulator of the classic MOS Technology 6502 CPU implemented in C++.
Currently only the non BCD portion of the instruction set has been implemented as my goal with this project is to eventually create a fully operational NES emulator which does not require this portion of the instruction set.  

# Building the Emulator

To build the enumator run the following:

```bash
git clone https://github.com/xchg-rax-rax/6502-Emulator.git
cd 6502-Emulator
./scripts/configure.sh
./scripts/build.sh
```

Note: You will need `clang` and `cmake` installed in order to build the project successfully.

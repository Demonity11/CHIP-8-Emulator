#include "chip8.h"

namespace Masks
{
	std::uint16_t nnn{ 0x0FFF }; // extracts the lower 12 bits
	std::uint16_t n{ 0x000F }; // extracts the lower 4 bits
	std::uint16_t x{ 0x0F00 }; // extracts the lower byte of the highbyte
	std::uint16_t y{ 0x00F0 }; // extracts the higher byte of the lowbyte
	std::uint16_t kk{0x00FF}; // extracts the lower 8 bits
}

void op_00E0(Chip8& cpu, std::uint16_t opcode)
{
    std::cout << "0x00E0: CLS: Clear the display." << "\n";
}

void op_00EE(Chip8& cpu, std::uint16_t opcode)
{
    std::cout << "0x00EE: The interpreter sets the program counter to the address at the top of the stack, then subtracts 1 from the stack pointer." << "\n";
}

void op_Annn(Chip8& cpu, std::uint16_t opcode)
{
    cpu.I = opcode & Masks::nnn;
    std::cout << "I = " << cpu.I << "\n";
}
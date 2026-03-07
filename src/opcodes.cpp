#include "../include/chip8.h"

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
    std::cout << "0x00EE: The interpreter sets the program counter to the address at the top of the stack, "
			  << "then subtracts 1 from the stack pointer." << "\n";
	cpu.pc = cpu.stack[cpu.sp--];
}

void op_Annn(Chip8& cpu, std::uint16_t opcode)
{
    cpu.I = opcode & Masks::nnn;
    std::cout << "I = " << cpu.I << "\n";
}

void op_1nnn(Chip8& cpu, std::uint16_t opcode)
{
	cpu.pc = opcode & Masks::nnn;
	std::cout << "0x" << std::hex << std::uppercase << cpu.pc << "\n";
}

void op_2nnn(Chip8& cpu, std::uint16_t opcode)
{
	cpu.stack[cpu.sp++] = cpu.pc;
	cpu.pc = opcode & Masks::nnn;
}

void op_3xkk(Chip8& cpu, std::uint16_t opcode)
{
	std::uint16_t x  = (opcode & Masks::x) >> 8;
	std::uint16_t kk = opcode & Masks::kk;

	if (cpu.V[x] == kk)
		cpu.pc += 2;
}

void op_4xkk(Chip8& cpu, std::uint16_t opcode)
{
	std::uint16_t x  = (opcode & Masks::x) >> 8;
	std::uint16_t kk = opcode & Masks::kk;

	if (cpu.V[x] != kk)
		cpu.pc += 2;
}

void op_5xy0(Chip8& cpu, std::uint16_t opcode)
{
	std::uint16_t x = (opcode & Masks::x) >> 8;
	std::uint16_t y = (opcode & Masks::y) >> 4;

	// std::cout << "x = 0x" << std::hex << std::uppercase << x << "\n";
	// std::cout << "y = 0x" << std::hex << std::uppercase << y << "\n";

	if (cpu.V[x] == cpu.V[y])
		cpu.pc += 2;
}

void op_6xkk(Chip8& cpu, std::uint16_t opcode)
{
	std::uint16_t x  = (opcode & Masks::x) >> 8;
	std::uint16_t kk = opcode & Masks::kk;

	cpu.V[x] = static_cast<std::uint8_t>(kk);

	// std::cout does not print a std::uint8_t without converting to an int
	// std::cout << "V[x] = 0x" << std::hex << std::uppercase << static_cast<int>(cpu.V[x]) << "\n";
}

void op_7xkk(Chip8& cpu, std::uint16_t opcode)
{
	std::uint16_t x  = (opcode & Masks::x) >> 8;
	std::uint16_t kk = opcode & Masks::kk;

	// std::cout << "V[x] = 0x" << std::hex << std::uppercase << static_cast<int>(cpu.V[x]) << " + 0x" << kk << "\n";

	cpu.V[x] += static_cast<std::uint8_t>(kk);

	// std::cout << "V[x] = 0x" << std::hex << std::uppercase << static_cast<int>(cpu.V[x]) << "\n";
}

void op_8xy0(Chip8& cpu, std::uint16_t opcode)
{
	std::uint16_t x = (opcode & Masks::x) >> 8;
	std::uint16_t y = (opcode & Masks::y) >> 4;

	cpu.V[x] = cpu.V[y];
}

void op_8xy1(Chip8& cpu, std::uint16_t opcode)
{
	std::uint16_t x = (opcode & Masks::x) >> 8;
	std::uint16_t y = (opcode & Masks::y) >> 4;

	cpu.V[x] = cpu.V[x] | cpu.V[y];
}

void op_8xy2(Chip8& cpu, std::uint16_t opcode)
{
	std::uint16_t x = (opcode & Masks::x) >> 8;
	std::uint16_t y = (opcode & Masks::y) >> 4;

	cpu.V[x] = cpu.V[x] & cpu.V[y];
}
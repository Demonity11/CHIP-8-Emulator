#ifndef CHIP8_H
#define CHIP8_H

#include <cstdint>
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>

struct Chip8
{
	std::uint8_t memory[4096]{}; // most programs starts at 0x200 (512)
	std::uint8_t V[16]{}; // general purpose 8-bit registers
	std::uint16_t I{};
	std::uint16_t pc{0x200}; // program counter (pc): holds the memory address being executed
	std::uint16_t stack[16]{}; // used to hold the value of the address to get back to
	std::uint8_t sp{};

	std::uint8_t delayTimer{};
	std::uint8_t soundTimer{};

	std::uint8_t display[64 * 32]{};
	std::uint8_t keypad[16]{};
};

// forward declarations for "chip8.cpp"
void decode(Chip8& cpu, std::uint16_t opcode);
std::uint16_t fetch(Chip8& cpu);
int loadROM(Chip8& cpu, const std::string& filename);
void printROM(const Chip8& cpu, const std::string& filename, int fileSize);

// forward declarations for "opcodes.cpp"
void op_00E0(Chip8& cpu, std::uint16_t opcode);
void op_00EE(Chip8& cpu, std::uint16_t opcode);
void op_Annn(Chip8& cpu, std::uint16_t opcode);

#endif

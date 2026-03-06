#ifndef CHIP8_H
#define CHIP8_H

#include <cstdint>

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

#endif

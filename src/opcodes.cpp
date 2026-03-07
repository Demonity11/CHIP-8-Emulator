#include "../include/chip8.h"
#include "../include/Random.h"

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

void op_8xy3(Chip8& cpu, std::uint16_t opcode)
{
	std::uint16_t x = (opcode & Masks::x) >> 8;
	std::uint16_t y = (opcode & Masks::y) >> 4;

	cpu.V[x] = cpu.V[x] ^ cpu.V[y];
}

void op_8xy4(Chip8& cpu, std::uint16_t opcode)
{
	std::uint16_t x = (opcode & Masks::x) >> 8;
	std::uint16_t y = (opcode & Masks::y) >> 4;

	std::uint16_t sum = cpu.V[x] + cpu.V[y];
	// std::cout << "sum = 0x" << std::hex << std::uppercase << sum << "\n";

	if (sum > 0xFF)
	{
		cpu.V[x] = static_cast<std::uint8_t>(sum & 0xFF);
		cpu.V[0xF] = 1; 
		// std::cout << "Vx = 0x" << std::hex << std::uppercase << static_cast<int>(cpu.V[x]) << "\n";

		return;
	}

	cpu.V[x] = cpu.V[x] + cpu.V[y];
	cpu.V[0xF] = 0;
}

void op_8xy5(Chip8& cpu, std::uint16_t opcode)
{
	std::uint16_t x = (opcode & Masks::x) >> 8;
	std::uint16_t y = (opcode & Masks::y) >> 4;

	if (cpu.V[x] >= cpu.V[y])
		cpu.V[0xF] = 1;
	else
		cpu.V[0xF] = 0;

	cpu.V[x] = cpu.V[x] - cpu.V[y];
}

void op_8xy6(Chip8& cpu, std::uint16_t opcode) // this instruction can cause undefined behavior since the community implement this in two different ways
{
	std::uint16_t x = (opcode & Masks::x) >> 8;
	std::uint16_t y = (opcode & Masks::y) >> 4;

	std::uint8_t leastBit = cpu.V[y] & 0x01;

	cpu.V[x] = cpu.V[y] >> 1;
	cpu.V[0xF] = leastBit;
}

void op_8xy7(Chip8& cpu, std::uint16_t opcode)
{
	std::uint16_t x = (opcode & Masks::x) >> 8;
	std::uint16_t y = (opcode & Masks::y) >> 4;

	if (cpu.V[y] >= cpu.V[x])
		cpu.V[0xF] = 1;
	else
		cpu.V[0xF] = 0;

	cpu.V[x] = cpu.V[y] - cpu.V[x];
}

void op_8xyE(Chip8& cpu, std::uint16_t opcode)
{
	std::uint16_t x = (opcode & Masks::x) >> 8;
	std::uint16_t y = (opcode & Masks::y) >> 4;

	if (static_cast<bool>(cpu.V[x] & 0x80))
		cpu.V[0xF] = 1;
	else
		cpu.V[0xF] = 0;

	cpu.V[x] = cpu.V[x] << 1;
}

void op_9xy0(Chip8& cpu, std::uint16_t opcode)
{
	std::uint16_t x = (opcode & Masks::x) >> 8;
	std::uint16_t y = (opcode & Masks::y) >> 4;

	if (cpu.V[x] != cpu.V[y])
		cpu.pc += 2;
}

void op_Bnnn(Chip8& cpu, std::uint16_t opcode)
{
	std::uint16_t nnn = opcode & Masks::nnn;

	cpu.pc = nnn + cpu.V[0x0];
}

void op_Cxkk(Chip8& cpu, std::uint16_t opcode)
{
	std::uint8_t randomNumber = Random::get(0, 255);
	std::uint16_t x = (opcode & Masks::x) >> 8;
	std::uint16_t kk = opcode & Masks::kk;
	
	cpu.V[x] = randomNumber & kk;
}

// void op_8xy2(Chip8& cpu, std::uint16_t opcode)
// {
	
// }
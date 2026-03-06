#include <fstream>
#include <iostream>
#include "chip8.h"
#include <iomanip>
#include <string>

std::uint16_t fetch(Chip8& cpu)
{
    std::uint16_t highByte = cpu.pc;
    std::uint16_t lowByte = cpu.pc + 1;
    
    std::uint16_t opcode = (cpu.memory[highByte] << 8) | cpu.memory[lowByte];

    cpu.pc += 2;

    return opcode;
}

void loadROM(Chip8& cpu, const std::string& filename)
{
    std::ifstream file(filename, std::ios::binary | std::ios::ate);

    if (file.is_open()) {
        std::streampos fileSize = file.tellg();
        file.seekg(0, std::ios::beg);

        if (fileSize > (4096 - 512)) {
            std::cerr << "Error. ROM's size is bigger than the available space.\n";
        }

        file.read(reinterpret_cast<char*>(&cpu.memory[0x200]), fileSize);

        file.close();
    }
}

int getFileSize(const std::string& filename)
{
    std::ifstream file(filename, std::ios::binary | std::ios::ate);

    return static_cast<int>(file.tellg());
}

void printROM(const Chip8& cpu, const std::string& filename)
{
    for (int i{ 0x200 }; i <= 0x200 + getFileSize(filename); i += 2)
    {
        std::cout << "Opcode: 0x" << std::hex << std::uppercase << std::setw(4) 
                  << std::setfill('0') << static_cast<std::uint16_t>((cpu.memory[i] << 8) | cpu.memory[i + 1]) << "\n";
    }
}

int main()
{
	Chip8 cpu{};
    std::string filename{ "IBM Logo.ch8" };

	loadROM(cpu, filename);

    printROM(cpu, filename);

	return 0;
}
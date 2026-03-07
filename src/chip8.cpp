#include "../include/chip8.h"

void decode(Chip8& cpu, std::uint16_t opcode)
{
    std::uint16_t firstNibble = (opcode >> 12) & 0x000F;

    std::cout << "opcode = 0x" << std::hex << std::uppercase << std::setw(4) << std::setfill('0') << opcode << "\n";

    std::cout << "first nibble = 0x" << std::hex << firstNibble << "\n\n";

    switch (firstNibble)
    {
    case 0x0:
        if (opcode == 0x00E0)
            op_00E0(cpu, opcode);

        if (opcode == 0x00EE)
            op_00EE(cpu, opcode);

        break;

    case 0xA:
        op_Annn(cpu, opcode);
        break;

    case 0x1:
        op_1nnn(cpu, opcode);
        break;
    }
}

std::uint16_t fetch(Chip8& cpu)
{
    std::uint16_t highByte = (cpu.memory[cpu.pc] << 8);
    std::uint16_t lowByte = cpu.memory[cpu.pc + 1];
    
    std::uint16_t opcode = highByte | lowByte;

    cpu.pc += 2;

    return opcode;
}

int loadROM(Chip8& cpu, const std::string& filename) 
{
    std::ifstream file("../roms/" + filename, std::ios::binary | std::ios::ate);

    if (file.is_open()) {
        std::streampos fileSize = file.tellg();
        file.seekg(0, std::ios::beg);

        if (fileSize > (4096 - 512)) {
            std::cerr << "Error. ROM's size is bigger than the available space.\n";
        }

        file.read(reinterpret_cast<char*>(&cpu.memory[0x200]), fileSize);

        file.close();

        return fileSize; // returns the file size
    }

    return 1;
}

void printROM(const Chip8& cpu, const std::string& filename, int fileSize)
{
    for (int i{ 0x200 }; i < 0x200 + fileSize; i += 2)
    {
        std::cout << "Opcode: 0x" << std::hex << std::uppercase << std::setw(4) 
                  << std::setfill('0') << static_cast<std::uint16_t>((cpu.memory[i] << 8) | cpu.memory[i + 1]) << "\n";
    }
}

int main()
{
	Chip8 cpu{};
    std::string filename{ "IBM Logo.ch8" };

	int fileSize { loadROM(cpu, filename) };

    std::uint16_t opcode{ fetch(cpu) };

    decode(cpu, opcode);

    opcode = fetch(cpu);

    decode(cpu, opcode);

	return 0;
}
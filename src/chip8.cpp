#include "../include/chip8.h"

void decode(Chip8& cpu, std::uint16_t opcode)
{
    std::uint16_t firstNibble = (opcode >> 12) & 0x000F;
    std::uint16_t lastNibble = opcode & 0x000F;

    std::cout << "opcode = 0x" << std::hex << std::uppercase << std::setw(4) << std::setfill('0') << opcode << "\n";

    std::cout << "first nibble = 0x" << std::hex << firstNibble << "\n\n";
    std::cout << "last nibble = 0x" << std::hex << lastNibble << "\n\n";

    switch (firstNibble)
    {
    case 0x0:
        if (opcode == 0x00E0) op_00E0(cpu, opcode);

        if (opcode == 0x00EE) op_00EE(cpu, opcode);

        break;

    case 0xA: op_Annn(cpu, opcode); break;

    case 0x1: op_1nnn(cpu, opcode); break;

    case 0x2: op_2nnn(cpu, opcode); break;

    case 0x3: op_3xkk(cpu, opcode); break;

    case 0x4: op_4xkk(cpu, opcode); break;
    
    case 0x5: op_5xy0(cpu, opcode); break;

    case 0x6: op_6xkk(cpu, opcode); break;

    case 0x7: op_7xkk(cpu, opcode); break;
    
    case 0x8:
        switch (lastNibble)
        {
        case 0x0: op_8xy0(cpu, opcode); break;

        case 0x1: op_8xy1(cpu, opcode); break;
        
        case 0x2: op_8xy2(cpu, opcode); break;
            
        case 0x3: op_8xy3(cpu, opcode); break;

        case 0x4: op_8xy4(cpu, opcode); break;

        case 0x5: op_8xy5(cpu, opcode); break;

        case 0x6: op_8xy6(cpu, opcode); break;

        case 0x7: op_8xy7(cpu, opcode); break;

        case 0xE: op_8xyE(cpu, opcode); break;
        }
        break;

    case 0x9: op_9xy0(cpu, opcode); break;

    case 0xB: op_Bnnn(cpu, opcode); break;

    case 0xC: op_Cxkk(cpu, opcode); break;

    // case 0xD: op_Dxyn(cpu, opcode); break;
    
    case 0xE:
        if (lastNibble == 0xE) op_Ex9E(cpu, opcode);
        if (lastNibble == 0x1) op_ExA1(cpu, opcode);
        
        break;

    case 0xF:
        switch (opcode & 0x00FF)
        {
        case 0x07: op_Fx07(cpu, opcode); break;

        case 0x0A: op_Fx0A(cpu, opcode); break;

        case 0x15: op_Fx15(cpu, opcode); break;
        case 0x55: op_Fx55(cpu, opcode); break;
        case 0x65: op_Fx65(cpu, opcode); break;

        case 0x18: op_Fx18(cpu, opcode); break;

        case 0x1E: op_Fx1E(cpu, opcode); break;

        case 0x29: op_Fx29(cpu, opcode); break;

        case 0x33: op_Fx33(cpu, opcode); break;
        }
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

	int fileSize{ loadROM(cpu, filename) };

    // printROM(cpu, filename, fileSize);

    // std::uint16_t opcode{ fetch(cpu) };

    // decode(cpu, opcode);

    // opcode = fetch(cpu);

    // decode(cpu, opcode);

    op_Dxyn(cpu, 0xD225);

	return 0;
}
# CHIP-8 Virtual Machine & Emulator

A high-performance CHIP-8 emulator written in **Modern C++** and rendered with **Modern OpenGL**. This project was developed to explore low-level systems programming, virtual machine architecture, and computer graphics.

## 🚀 Technical Highlights

* **Instruction Pipeline:** Implemented a complete Fetch-Decode-Execute cycle for all 35 opcodes.
* **Memory Management:** Manual memory mapping of a 4KB RAM layout, including font sets and program memory.
* **Bitwise Manipulation:** Heavy use of bitwise operators (`&`, `|`, `^`, `<<`, `>>`) for opcode decoding and pixel extraction.
* **Modern OpenGL Rendering:** Utilizing Shaders (GLSL) and Textures to upscale the original 64x32 resolution to modern displays.
* **Platform Abstraction:** Decoupled CPU logic from the graphics API, allowing for modularity and portability.

## 🛠️ Architecture

### The Core (C++)
The emulator core mimics the original COSMAC VIP hardware. It manages:
- **16 General Purpose Registers (V0-VF)**
- **4KB of RAM**
- **16-level Stack** for subroutines
- **60Hz Timers** for delay and sound

### The Display (OpenGL + Math)
Instead of simple pixel drawing, I applied **Linear Algebra** concepts to handle coordinate mapping and screen scaling, ensuring an authentic pixel-art aesthetic without CPU-bound overhead.

## 📂 Project Structure
(Aqui você insere uma versão resumida da estrutura de pastas explicada acima)

## 📖 Lessons Learned
- Deep understanding of **Pointers and Memory Addresses** in C++.
- How a CPU interprets binary data as instructions.
- Synchronization between CPU clock cycles and Display Refresh rates (Vertical Sync).

## 🔧 How to Build
```bash
mkdir build && cd build
cmake ..
make
./CHIP8_Emulator ../roms/pong.ch8

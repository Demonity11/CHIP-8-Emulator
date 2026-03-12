#include "../include/chip8.h"
#include <chrono>
#include <thread>

using namespace std::literals::chrono_literals;

int main()
{
    Chip8 cpu{ init("IBM Logo.ch8") };
    
    using Milliseconds = std::chrono::duration<double, std::milli>;

    constexpr Milliseconds timePerCycle{ 1000.0 / 500.0 }; // 500 Hz
    constexpr Milliseconds timePerTimer{ 1000.0 / 60.0 }; // 60 Hz

    auto lastTime = std::chrono::steady_clock::now();

    double timerAccumulator{ 0.0 };
    double cycleAccumulator{ 0.0 };

    while (true)
    {
        auto currentTime{ std::chrono::steady_clock::now() };
        Milliseconds dt{ currentTime - lastTime }; // gets the time elapsed
        lastTime = currentTime; // currentTime is now in the past, so lastTime = currentTime

        timerAccumulator += dt.count(); // increments the elapsed time per loop
        cycleAccumulator += dt.count(); 

        while (cycleAccumulator >= timePerCycle.count()) // fetch-decode-execute cycle at 500 Hz
        {
            std::uint16_t opcode = fetch(cpu);
            decode(cpu, opcode);
            cycleAccumulator -= timePerCycle.count();
        }

        while (timerAccumulator >= timePerTimer.count()) // decrement timers and update screen at 60 Hz
        {
            if (cpu.delayTimer > 0) cpu.delayTimer--;
            if (cpu.soundTimer > 0) {
                cpu.soundTimer--;
                // bips in the future
            }

            printDisplay(cpu);
        
            timerAccumulator -= timePerTimer.count();
        }

        std::this_thread::sleep_for(1ms);
    }

    return 0;
}

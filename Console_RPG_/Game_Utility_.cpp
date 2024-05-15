#include "Game_Utility_.h"

void writeStringWithDelay(const std::string& str, int delayMilliseconds)
{
    for (char c : str) {
        std::cout << c << std::flush;  // Flush the output buffer to ensure immediate display
        std::this_thread::sleep_for(std::chrono::milliseconds(delayMilliseconds));
    }
    std::cout << std::endl;
}

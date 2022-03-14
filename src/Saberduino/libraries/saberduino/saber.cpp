#include "saber.hpp"

#ifdef SABERDUINO_DESKTOP_COMPUTER
#include <SFML/Graphics.hpp>
#endif

void Saber::init() {}

Position Saber::position()
{
#ifdef SABERDUINO_DESKTOP_COMPUTER
    return {1, 1};
#else
    char res = 254;
    while (Serial2.available())
    {
        res = Serial2.read(); // Keep only the last data
    }
    switch (res)
    {
        case '0': return prev = {0, 0};
        case '1': return prev = {1, 0};
        case '2': return prev = {2, 0};
        case '3': return prev = {0, 1};
        case '4': return prev = {1, 1};
        case '5': return prev = {2, 1};
        case '6': return prev = {0, 2};
        case '7': return prev = {1, 2};
        case '8': return prev = {2, 2};
    }
    return prev;
#endif
}

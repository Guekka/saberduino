#ifndef SABERDUINO_SABER
#define SABERDUINO_SABER

#include "base_defines.hpp"

enum Direction : uint8_t
{
    Left,
    Right,
    Top,
    Bottom,
};

class Saber
{
public:
    void init();
    Position position();
    Direction direction();

private:
    Position prev = {1, 1};
};

#endif

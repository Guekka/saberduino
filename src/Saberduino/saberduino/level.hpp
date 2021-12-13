#ifndef SABERDUINO_LEVEL
#define SABERDUINO_LEVEL

#include "base_defines.hpp"

struct Block {
    Position pos;
    uint16_t depth;
};

class Level {
   public:
    void init();
    void load(const char* filename);
    void start();
    void update(Position pos);

   private:
    Block blocks_[10];
    uint16_t cur_time_{};
};
#endif

#ifndef SABERDUINO_LEVEL
#define SABERDUINO_LEVEL

#include "base_defines.hpp"

struct Block {
    Position pos;
    uint16_t time;
    static constexpr uint8_t radius = 6;
};

class Display;

class Level {
   public:
    void init();
    void load(const char* filename);
    void load(const Block blocks[10]);
    void start();
    void update(Display& display, Position pos);

   private:
    Block blocks_[10];
    uint16_t cur_time_{};

    void destroy_block(Display& display, Block& block);
    void display_block(Display& display, Block block, uint16_t dt);
    bool pos_approx(Position a, Position b);
};
#endif

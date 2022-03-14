#ifndef SABERDUINO_LEVEL
#define SABERDUINO_LEVEL

#include "base_defines.hpp"

enum class BlockFlags : uint8_t
{
    none         = 0,
    is_bomb      = 1 << 0,
    is_destroyed = 1 << 1
};

struct Block
{
    BlockFlags flags = BlockFlags::is_destroyed;
    Position pos;
    uint16_t time;
    static constexpr uint8_t radius = 6;
};

class Display;

class Level
{
public:
    Level(const uint8_t *source, uint16_t len);

    void start();
    void update(Display &display, Position pos);

private:
    CircularBuffer<Block, 20> blocks_;
    uint16_t start_time_{};

    const uint8_t *source_{};
    uint16_t bits_left_{};
    uint8_t bits_offset_{};

    uint16_t elapsed_time();

    void destroy_block(Display &display, Block &block);
    void display_block(Display &display, Block block, uint16_t dt);
    bool pos_approx(Position a, Position b);

    void display_saber(Display &display, Position pos);

    bool has_next_block();
    Block load_next_block();
};
#endif

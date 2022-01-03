#include "level.hpp"
#include "display.hpp"
#include "printer.hpp"

constexpr Color kRed = {255, 0, 0};
constexpr Color kBlue = {0, 255, 0};

void Level::init() {
    printer.println("init level");
}

void Level::load(const char* filename) {
    printer.println("load level");
}

void Level::load(const Block blocks[]) {
    memcpy(blocks_, blocks, 10 * sizeof(Block));
}

void Level::start() {
    printer.println("start level");
}

void Level::update(Display& display, Position pos) {
    cur_time_ = milli_scaled();
    for (auto block : blocks_) {
        if (block.time < cur_time_) {
            block = {};  // Mark block as available
            continue;
        }
        if (pos_approx(block.pos, pos))
            destroy_block(display, block);

        const auto diff = block.time - cur_time_;
        if (diff < to_millis_scaled(200))
            display_block(display, block, diff);
    }
}

void Level::destroy_block(Display& display, Block& block) {
    display.draw_square(block.pos, kBlue, 3);
    const auto start = Position{static_cast<uint8_t>(block.pos.x - 1),
                                static_cast<uint8_t>(block.pos.y - 1)};
    const auto end = Position{static_cast<uint8_t>(block.pos.x + 1),
                              static_cast<uint8_t>(block.pos.y + 1)};
    display.draw_line(start, end, kRed);
    block = {};
}

void Level::display_block(Display& display, Block block, uint64_t dt) {
    display.draw_square(block.pos, kBlue, 3);
}

bool Level::pos_approx(Position a, Position b) {
    return a.x - b.x < Block::radius && a.y - b.y < Block::radius;
}

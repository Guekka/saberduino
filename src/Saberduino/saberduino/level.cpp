#include "level.hpp"
#include "display.hpp"
#include "printer.hpp"

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
        const auto diff = block.time - cur_time_;
        if (diff > 0 && diff < to_millis_scaled(200))
            display_block(display, block, diff);
    }
}

void Level::display_block(Display& display, Block block, uint16_t dt) {
    display.draw_pix(block.pos, 50, 100, 150);
}
